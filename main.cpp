#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include "mainClass.h"

using namespace std;


int main() {

    std::locale::global(std::locale("ka_GE.UTF-8")); // set the locale to support UTF-8 encoding
    // Seed the random number generator with the current time
    srand(time(nullptr));
    // Call a function to initialize the list of text files to read
    sources::initialize_source_file_names();
    // Print a message to inform the user about the available text files
    printf("I analyzed this txt's words and I can list words that rhymes to your word!\n");
    for(const string& txt : list_of_txts_to_read) {
        printf("%s \n", txt.c_str());
    }

    printf("Choose what you want, exact matching (then write 'ზ'), only vowel matching (write 'ხ'):\n");
    try_read_type:
        wchar_t type;
        wcin>>type;
        vector<wstring> all_words;
        unordered_map<wstring ,bool >word_exist;
        wstring word;

        // If the user wants to do exact or vowel matching, get the word to find rhymes for
        // and preprocess the text files
        if(type==L'ზ'||type==L'ხ'){
            wcin>>word;
            mainClass::preprocessing(all_words, word_exist, false); // set true, if you added file.
        }

        // If the user wants to do exact matching, call a function to print the matching words
        if(type==L'ზ'){
            mainClass::print_exact_matchings(all_words,word);
        }
        // If the user wants to do vowel matching, call a function to print the matching words
        else if(type==L'ხ'){
            mainClass::print_vowel_matchings(all_words,word);
        }
        // If the user entered an invalid type, prompt them again
        else {
            printf("please write only 'ზ' or only 'ხ' and click enter\n");
            goto try_read_type;
        }

    return 0;

}




