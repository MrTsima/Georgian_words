//
// Created by tsima on 2/18/24.
//

#ifndef GEORGIAN_WORDS_MAINCLASS_H
#define GEORGIAN_WORDS_MAINCLASS_H

#include "sources.h"
#include "txtSrapper.h"
#include "KGrams.h"


class mainClass {
public:
    static void initialize_txts();

    static void print_exact_matchings(std::vector<std::wstring> &all_words, std::wstring &word);

    static void find_vowel_matchings(std::vector<std::wstring> &all_words, std::wstring &word, int how_more);

    static void preprocessing_parsing_files(std::vector<std::wstring> &vector1, std::unordered_map<std::wstring, bool> &unorderedMap, bool is_new_file = true);

    static void find_matchings(std::vector<std::wstring> &all_words, std::wstring &word, bool only_vowels, int how_more);

    static int consonant_points(const std::wstring &fir, std::wstring &sec);

    static std::unique_ptr<KGrams> generate_n_grams(const std::vector<std::wstring>& all_words, int N);

    static void safe_get_line(std::wistream &is, std::wstring &str, size_t maxLen);

    static std::vector<std::wstring> split_into_words(const std::wstring &str);
};


#endif //GEORGIAN_WORDS_MAINCLASS_H
