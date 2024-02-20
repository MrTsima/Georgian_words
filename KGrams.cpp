//
// Created by tsima on 2/20/24.
//

#include "KGrams.h"

std::vector<std::vector<std::pair<int,int>>> KGrams::adj;
int KGrams::cur_idx, KGrams::start_idx;
std::vector<int> KGrams::idx;
std::vector<int> KGrams::low_link;
std::vector<int> KGrams::longest_path;
std::vector<int> KGrams::next_vertex;
std::vector<bool> KGrams::on_stack;
std::stack<int> KGrams::S;
int KGrams::n;
int KGrams::k;

std::deque<int> KGrams::window;
std::unordered_map<std::wstring, int> KGrams::word_id;
std::vector<std::wstring> KGrams::id_word;
std::map<std::vector<int>, int> KGrams::kgram_id;
std::vector<std::vector<int>> KGrams::id_kgram;
std::vector<std::map<int,int>> KGrams::adj_map;

std::vector<int> KGrams::weights;
std::vector<std::vector<int>> KGrams::longest_path_by_weight;
std::vector<std::vector<int>> KGrams::next_vertex_by_weight;
std::vector<std::vector<int>> KGrams::pos_by_weight;
std::list<int> KGrams::rem;

KGrams::KGrams(int vertices, int n_in_ngram) {
    idx.resize(vertices, -1);
    low_link.resize(vertices);
    longest_path.resize(vertices);
    next_vertex.resize(vertices);
    on_stack.resize(vertices);
    n = vertices;
    k = n_in_ngram;
}

void KGrams::calculate_k_grams(const std::vector<std::wstring> &all_words) {
    int last_kgram = -1;
    for (int i = 0; i < n; i++) {
        std::wstring s;
        s = all_words[i];
        if (word_id.find(s) == word_id.end()) {
            word_id.insert(make_pair(s, word_id.size()));
            id_word.push_back(s);
        }
        int t = word_id[s];
        window.push_back(t);
        if ((int)window.size() > k) {
            window.pop_front();
        }
        if ((int)window.size() == k) {
            std::vector<int> kgram_vector(window.begin(), window.end());
            if (kgram_id.find(kgram_vector) == kgram_id.end()) {
                kgram_id.insert(make_pair(kgram_vector, kgram_id.size()));
                id_kgram.push_back(kgram_vector);
                adj_map.push_back(std::map<int,int>());
            }
            int kgram = kgram_id[kgram_vector];
            if (last_kgram != -1) {
                adj_map[last_kgram][kgram]++;
            }
            last_kgram = kgram;
        }
    }
    std::set<int> weight_set;
    for (auto entry : adj_map) {
        adj.emplace_back(entry.begin(), entry.end());
        for (auto edge : entry) {
            weight_set.insert(edge.second);
        }
    }
    weights.insert(weights.end(), weight_set.begin(), weight_set.end());
    pos_by_weight.resize(((int)adj.size()));
    for (int i = 0; i < (int)adj.size(); i++) {
        rem.push_back(i);
    }
    cur_idx = 0;
    for (int i = 0; i < (int)weights.size(); i++) {
        for (auto it = rem.begin(); it != rem.end(); ) {
            for (int j = 0; j < (int)adj[*it].size(); ) {
                if (adj[*it][j].second < weights[i]) {
                    swap(adj[*it][j], adj[*it].back());
                    adj[*it].pop_back();
                } else {
                    j++;
                }
            }
            if (adj[*it].empty()) {
                auto cur = it;
                ++it;
                rem.erase(cur);
            } else {
                ++it;
            }
        }
        start_idx = cur_idx;
        for (auto v : rem) {
            if (idx[v] < start_idx) {
                dfs(v);
            }
        }
        std::vector<int> cur_longest_path, cur_next_vertex;
        int at = 0;
        for (auto v : rem) {
            cur_longest_path.push_back(longest_path[v]);
            cur_next_vertex.push_back(next_vertex[v]);
            pos_by_weight[v].push_back(at);
            at++;
        }
        longest_path_by_weight.push_back(cur_longest_path);
        next_vertex_by_weight.push_back(cur_next_vertex);
    }
}

void KGrams::dfs(int v) {
    idx[v] = cur_idx;
    low_link[v] = cur_idx;
    cur_idx++;
    longest_path[v] = 0;
    next_vertex[v] = -1;
    S.push(v);
    on_stack[v] = true;

    for (auto edge : adj[v]) {
        int w = edge.first;
        if (idx[w] < start_idx) {
            dfs(w);
            low_link[v] = std::min(low_link[v], low_link[w]);
            if (low_link[w] <= idx[v]) {
                longest_path[v] = INF;
                next_vertex[v] = w;
            } else if (1 + longest_path[w] > longest_path[v]) {
                longest_path[v] = 1 + longest_path[w];
                next_vertex[v] = w;
            }
        } else if (on_stack[w]) {
            low_link[v] = std::min(low_link[v], idx[w]);
            longest_path[v] = INF;
            next_vertex[v] = w;
        } else {
            if (1 + longest_path[w] > longest_path[v]) {
                longest_path[v] = 1 + longest_path[w];
                next_vertex[v] = w;
            }
        }
    }

    if (low_link[v] == idx[v]) {
        while (true) {
            int w = S.top();
            S.pop();
            on_stack[w] = false;
            if (w == v) {
                break;
            }
        }
    }
}
std::vector<std::wstring> KGrams::generate_text_for_poem(std::vector<std::wstring> words, int number_of_words){
    std::vector<int> kgram_vec;
    for (int i = 0; i < k; i++) {
        kgram_vec.push_back(word_id[words[i]]);
    }
    std::vector<std::wstring> answer;
    if (kgram_id.find(kgram_vec) == kgram_id.end()) {
        for (int i = 0; i < number_of_words; i++) {
            answer.push_back(id_word[0]);
        }
    } else {
        int kgram = kgram_id[kgram_vec];
        int lo = 0,
                hi = (int)pos_by_weight[kgram].size() - 1,
                res = -1;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            if (longest_path_by_weight[mid][pos_by_weight[kgram][mid]] >= number_of_words) {
                res = mid;
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
        if (res == -1) {
            for (int i = 0; i < number_of_words; i++) {
                answer.push_back(id_word[0]);
            }
        } else {
            int at = kgram;
            for (int i = 0; i < number_of_words; i++) {
                int cur = next_vertex_by_weight[res][pos_by_weight[at][res]];
                answer.push_back(id_word[*id_kgram[cur].rbegin()]);
                at = cur;
            }
        }
    }
    return answer;
}
