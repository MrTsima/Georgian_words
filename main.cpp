#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <QApplication>
#include <QPushButton>
#include "sources.h"
#include "txtSrapper.h"
using namespace std;


void initialize_txts();

void print_exact_matchings(vector<wstring>& all_words,wstring& word);

void print_vowel_matchings(vector<wstring>& all_words,wstring& word);

void find_matchings(vector<wstring>& all_words,wstring& word,bool only_vowels);

void preprocessing(vector<wstring>& vector1, unordered_map<wstring, bool>& unorderedMap);

int main() {

    std::locale::global(std::locale("ka_GE.UTF-8")); // set the locale to support UTF-8 encoding
    // Seed the random number generator with the current time
    srand(time(nullptr));
// Call a function to initialize the list of text files to read
    initialize_txts();
// Print a message to inform the user about the available text files
    printf("I analyzed this txt's words and I can list words that rhymes to your word!\n");
    for(const string& txt : list_of_txts_to_read) {
        printf("%s \n", txt.c_str());
    }

// Ask the user what type of matching to perform and what word to find rhymes for
    ask_about_type:
    printf("Choose what you want, exact matching (then write 'ზ'), only vowel matching (write 'ხ'), "
           "if you want to add your own txt write 'დ':\n");
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
        preprocessing(all_words, word_exist);
    }

// If the user wants to do exact matching, call a function to print the matching words
    if(type==L'ზ'){
        print_exact_matchings(all_words,word);
    }
// If the user wants to do vowel matching, call a function to print the matching words
    else if(type==L'ხ'){
        print_vowel_matchings(all_words,word);
    }
// If the user wants to add their own text file, prompt them for the file name, add it to the
// list of text files, and go back to asking about the type of matching
    else if(type==L'დ') {
        printf("put for example:  good_book.txt\n");
        wstring s;
        wcin>>s;
        // Convert the file name to a string and add the current directory to it
        wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
        string narrow_input = converter.to_bytes(s);
        char buffer[FILENAME_MAX];
        getcwd(buffer, FILENAME_MAX);
        string current_dir(buffer);
        narrow_input = current_dir + "/" + narrow_input;
        cout<<narrow_input<<endl;
        sources::add_pdf(narrow_input);
        goto ask_about_type;
    }
// If the user entered an invalid type, prompt them again
    else {
        printf("please write only 'ზ' or only 'ხ' and click enter\n");
        goto try_read_type;
    }

    return 0;

}
/*
 * This function extracts all words from the txts and stores them in a vector called all_words and in an
 * unordered map called word_exist. The all_words vector is used to find matching words, and the
 * word_exist unordered map is used to keep track of whether a word has already been added to the
 * all_words vector.
 */
void preprocessing(vector<wstring>& all_words,unordered_map<wstring ,bool >&word_exist) {
    vector<vector<wstring> >all_pages;
    for(const string& txt : list_of_txts_to_read) {
        vector<vector<wstring> > pages=txtSrapper::scrap(txt);
     //   cout<<"PIZDEC"<<endl;
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

void print_vowel_matchings(vector<wstring>& all_words,wstring& word) {
    find_matchings(all_words,word, true);
}

// This function takes a vector of words, a single word, and a boolean flag as input.
// The function finds all words in the vector that match the given word in reverse,
// considering only the vowels if the flag is set to true. It then prints the
// top matching words to a text file.
void find_matchings(vector<wstring>& all_words,wstring& word, bool only_vowels){
    // Create an empty string to store the reverse of the given word
    wstring reversed_word=L"";
    // Create a vector to store the matching words and their corresponding match count
    vector<pair<int,wstring> >matchings;
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
            matchings.emplace_back(counter, cur_word);
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
    ofstream fout("/home/mrtsima/CLionProjects/Georgian_words/output.txt");
    fout.is_open();
    for (const auto &word: ans) {
        fout << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(word) << std::endl;
        cout << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(word) << std::endl;

    }
    fout.close();
}

void print_exact_matchings(vector<wstring>& all_words,wstring& word) {
    find_matchings(all_words, word, false);
}



void initialize_txts() {
    sources::add_pdf("/home/mrtsima/CLionProjects/Georgian_words/sources_for_words/jayo.txt");
    sources::add_pdf("/home/mrtsima/CLionProjects/Georgian_words/sources_for_words/qartuli_wigni.txt");
    sources::add_pdf("/home/mrtsima/CLionProjects/Georgian_words/sources_for_words/akakis_leqsebi.txt");
    sources::add_pdf("/home/mrtsima/CLionProjects/Georgian_words/sources_for_words/ra.txt");
}


