//
// Created by tsima on 2/18/24.
//

#ifndef GEORGIAN_WORDS_MAINCLASS_H
#define GEORGIAN_WORDS_MAINCLASS_H

#include "sources.h"
#include "txtSrapper.h"


class mainClass {
public:
    static void initialize_txts();

    static void print_exact_matchings(vector<wstring> &all_words, wstring &word);

    static void print_vowel_matchings(vector<wstring> &all_words, wstring &word);

    static void preprocessing(vector<wstring> &vector1, unordered_map<wstring, bool> &unorderedMap, bool is_new_file = true);

    static void find_matchings(vector<wstring> &all_words, wstring &word, bool only_vowels);

    static int consonant_points(const wstring &fir, wstring &sec);
};


#endif //GEORGIAN_WORDS_MAINCLASS_H
