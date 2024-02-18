//
// Created by mrtsima on 4/21/23.
//

#ifndef GEORGIAN_WORDS_SOURCES_H
#define GEORGIAN_WORDS_SOURCES_H
#include<bits/stdc++.h>
using namespace std;

extern const wchar_t consonants[];
extern const wchar_t vowels[];
extern vector<string> list_of_txts_to_read;
extern const int MAX_MATCHING_WORDS_NEEDED;
class sources {

    static bool is_consonants(wchar_t c);

public:
    static void add_resource(const string& s);

    static bool is_vowel(wchar_t c);

    static void initialize_source_file_names();
};


#endif //GEORGIAN_WORDS_SOURCES_H
