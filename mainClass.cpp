//
// Created by tsima on 2/18/24.
//

#include "mainClass.h"


void saveWordsToFile(const std::vector<std::wstring>& words, const std::string& filename) {
    std::wofstream outFile(filename, std::ios::binary);
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    outFile.imbue(loc);

    for (const auto& word : words) {
        outFile << word << std::endl;
    }
}
void loadWordsFromFile(std::vector<std::wstring>& words, const std::string& filename) {
    std::wifstream inFile(filename, std::ios::binary);
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    inFile.imbue(loc);

    std::wstring word;
    while (std::getline(inFile, word)) {
        words.push_back(word);
    }
}

/*
 * This function extracts all words from the txts and stores them in a vector called all_words and in an
 * unordered map called word_exist. The all_words vector is used to find matching words, and the
 * word_exist unordered map is used to keep track of whether a word has already been added to the
 * all_words vector.
 */
void mainClass::preprocessing(vector<wstring>& all_words,unordered_map<wstring ,bool >&word_exist, bool is_new_file) {
    if (!is_new_file) {
        loadWordsFromFile(all_words, "uniqueWords.txt");
        return ;
    }
    vector<vector<wstring> >all_pages;
    for(const string& txt : list_of_txts_to_read) {
        vector<vector<wstring> > pages=txtSrapper::scrap(txt);
        for(const vector<wstring>& i: pages){
            for(const wstring& j: i){
                if(word_exist[j]){
                    continue;
                }
                all_words.push_back(j);
                word_exist[j]=true;
            }
        }
    }
    saveWordsToFile(all_words, "uniqueWords.txt");
}


/*
 * This function and print_vowel_matchings() function both call the find_matchings() function to
 * find and print matching words. The find_matchings() function takes a vector of all the words
 * to be analyzed, a word to be matched, and a boolean value indicating whether only vowel matching
 * is required or not. It then finds all the words that rhyme with the given word and prints them.
 * The function first reverses the order of the input word and all the words in the all_words
 * vector and then compares them character by character until it finds a mismatch. The function
 * then counts the number of matching characters and sorts the words by the number of matching characters.
 */

void mainClass::print_vowel_matchings(vector<wstring>& all_words,wstring& word) {
    mainClass::find_matchings(all_words,word, true);
}

// This function takes a vector of words, a single word, and a boolean flag as input.
// The function finds all words in the vector that match the given word in reverse,
// considering only the vowels if the flag is set to true. It then prints the
// top matching words to a text file.
void mainClass::find_matchings(vector<wstring>& all_words,wstring& word, bool only_vowels){
    // Create an empty string to store the reverse of the given word
    wstring reversed_word=L"";
    // Create a vector to store the matching words and their corresponding match count
    vector<pair< pair<int, int>,wstring> >matchings;
    // Loop through each character in the given word
    for(wchar_t i: word) {

        // If the only_vowels flag is false, or if the current character is a vowel,
        // add it to the reversed_word string
        if(!only_vowels || sources::is_vowel(i)) {
            reversed_word += i;
        }
    }

    // Reverse the reversed_word string so that it is in the correct order
    reverse(reversed_word.begin(),reversed_word.end());

    // Loop through each word in the all_words vector
    for(const wstring& cur_word: all_words) {

        // Create an empty string to store the reverse of the current word
        wstring reversed_cur_word = L"";

        // Create a counter variable to keep track of how many matching characters the words share
        int counter = 0;

        // Loop through each character in the current word
        for(wchar_t i: cur_word) {

            // If the only_vowels flag is false, or if the current character is a vowel,
            // add it to the reversed_cur_word string
            if(!only_vowels || sources::is_vowel(i)) {
                reversed_cur_word += i;
            }
        }

        // Reverse the reversed_cur_word string so that it is in the correct order
        reverse(reversed_cur_word.begin(),reversed_cur_word.end());

        // If the reversed_cur_word string is empty, skip to the next word in the all_words vector
        if(reversed_cur_word.empty()){
            continue;
        }

        // Loop through each character in the reversed_cur_word and reversed_word strings
        // and increment the counter variable each time a matching character is found
        for(int cur_i=0; cur_i<min(reversed_cur_word.size(),reversed_word.size()); cur_i++) {
            if(reversed_cur_word[cur_i] != reversed_word[cur_i]) {
                break;
            }
            counter++;
        }

        // If the counter variable is not zero, add the current word and its corresponding match count to the matchings vector
        if(counter != 0) {
            int consonant_point = mainClass::consonant_points(cur_word, word);
            matchings.push_back({{counter, consonant_point}, cur_word});
        }
    }

    // Sort the matchings vector in descending order based on the match count
    sort(matchings.rbegin(), matchings.rend());

    // Ask the user how many matching words they want to print
    printf("How much maximum words to you want to print?\n");
    wstring how_more;
    wcin >> how_more;

    // Convert the user's input to a string so that it can be used with stoi()
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    string how_many_more = converter.to_bytes(how_more);

    // Convert the user's input string to an integer and store it in the more_words variable
    int more_words=stoi(how_many_more);

    // initialize a vector called ans to store the matched words
    vector<wstring>ans;

    // loop iterates over the matchings vector, and adds the second element (which is the matched word)
    // of each pair to ans. The maximum number of words to add is determined by the minimum value
    // of matchings.size() and either more_words or a predefined constant MAX_MATCHING_WORDS_NEEDED.
    for(int i=0;i<min((int)matchings.size(),max(more_words,MAX_MATCHING_WORDS_NEEDED));i++){
        ans.push_back(matchings[i].second);
    }

    // printing result in output.txt
    ofstream fout("output.txt"); /*it will create the output.txt file in the current working directory of the executable when the program is run.
 * The current working directory is usually the directory from which the program is launched, unless changed by the program or the environment.*/
    fout.is_open();
    for (const auto &word: ans) {
        fout << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(word) << std::endl;
        cout << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(word) << std::endl;

    }
    fout.close();
}

void mainClass::print_exact_matchings(vector<wstring>& all_words,wstring& word) {
    mainClass::find_matchings(all_words, word, false);
}

int mainClass::consonant_points(const wstring &fir, wstring &sec){
    map<wchar_t, int> fir_consonant;
    map<wchar_t, int> sec_consonant;
    int ans = 0;
    for (auto i: fir){
        fir_consonant[i]++;
    }
    for (auto i: sec){
        sec_consonant[i]++;
    }
    for (wchar_t i = L'ა'; i <= L'ჰ'; i++){
        ans += min(fir_consonant[i], sec_consonant[i]) * 2;
    }
    int dif = (int)sec.size() - (int)fir.size();
    if (dif < 0)
    {
        dif *= -1;
    }
    ans -= dif;
    return ans;
}
