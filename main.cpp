#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include "mainClass.h"



int main() {

    std::locale::global(std::locale("ka_GE.UTF-8")); // set the locale to support UTF-8 encoding
    // Seed the random number generator with the current time
    srand(time(nullptr));
    // Call a function to initialize the list of text files to read
    sources::initialize_source_file_names();
    // Print a message to inform the user about the available text files
    printf("I analyzed this txt's words and I can list words that rhymes to your word!\n");
    for(const std::string& txt : list_of_txts_to_read) {
        printf("%s \n", txt.c_str());
    }
    std::vector<std::wstring> all_words;
    std::unordered_map<std::wstring ,bool >word_exist;
    mainClass::preprocessing_parsing_files(all_words, word_exist, false); // set true, if you added file in sources.txt
    std::wstring first_line;
    mainClass::safe_get_line(std::wcin, first_line, 8 * 15);
    std::vector<std::wstring> words = mainClass::split_into_words(first_line);
    std::wstring last_word = words.back();

    // Ask the user how many matching words they want to print
    printf("How much maximum words to you want to print?\n");
    std::wstring how_more;
    std::wcin >> how_more;
    // Convert the user's input to a string so that it can be used with stoi()
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string how_many_more = converter.to_bytes(how_more);

    // Convert the user's input string to an integer and store it in the more_words variable
    int more_words=stoi(how_many_more);

    // If the user wants to do exact matching, call a function to print the matching words
    //    if(type==L'ზ'){
    //        mainClass::print_exact_matchings(all_words,word);
    //    }

    // If the user wants to do vowel matching, call a function to print the matching words
    mainClass::find_vowel_matchings(all_words, last_word, more_words);


//    for (int N = 2; N <= 2; ++N) {
//        auto n_grams = mainClass::generate_n_grams(all_words, N);
//        std::vector<std::wstring> version = n_grams->generate_text_for_poem(words, words.size() * 10);
//        for (auto i: version){
//            std:: cout << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(i) << std:: endl;
//        }
//    }

    return 0;

}




