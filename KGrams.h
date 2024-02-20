//
// Created by tsima on 2/20/24.
//

#ifndef GEORGIAN_WORDS_KGRAMS_H
#define GEORGIAN_WORDS_KGRAMS_H

#include <bits/stdc++.h>

class KGrams {
    public:
        KGrams(int vertices, int n_in_ngram = 1);
        static void calculate_k_grams(const std::vector<std::wstring>& all_words);
        static std::vector<std::wstring> generate_text_for_poem(std::vector<std::wstring> words, int number_of_words);
    private:
        static void dfs(int v);
        static const int INF = 1000000000;
        static std::vector< std::vector <std::pair<int, int>> > adj;
        static int cur_idx, start_idx;
        static std::vector<int> idx;
        static std::vector<int> low_link;
        static std::vector<int> longest_path;
        static std::vector<int> next_vertex;
        static std::vector<bool> on_stack;
        static std::stack<int> S;
        static int n;
        static int k;

        static std::deque<int> window;
        static std::unordered_map<std::wstring, int> word_id;
        static std::vector<std::wstring> id_word;
        static std::map<std::vector<int>, int> kgram_id;
        static std::vector<std::vector<int>> id_kgram;
        static std::vector<std::map<int,int>> adj_map;

        static std::vector<int> weights;
        static std::vector<std::vector<int>> longest_path_by_weight;
        static std::vector<std::vector<int>> next_vertex_by_weight;
        static std::vector<std::vector<int>> pos_by_weight;
        static std::list<int> rem;
};


#endif //GEORGIAN_WORDS_KGRAMS_H
