//
// Created by mrtsima on 4/21/23.
//

#include "sources.h"

// This code defines a set of Georgian consonants and vowels, as well as a list of text files to read.
// It also provides two functions to check whether a given character is a vowel or a consonant, respectively,
// and a function to add a text file to the list.

// Georgian consonants and vowels
const wchar_t consonants[] = {
        L'ბ', L'გ', L'დ', L'ვ', L'ზ', L'თ', L'კ', L'ლ', L'მ', L'ნ',
        L'პ', L'ჟ', L'რ', L'ს', L'ტ', L'ფ', L'ქ', L'ღ', L'ყ', L'შ', L'ჩ', L'ც', L'ძ', L'წ', L'ჭ', L'ხ', L'ჰ'};

const wchar_t vowels[] = {L'ა', L'ე', L'ი', L'ო', L'უ'};

// List of text files to read
std::vector<std::string> list_of_txts_to_read;

// Maximum number of matching words to display
const int MAX_MATCHING_WORDS_NEEDED = 10;

// Function to check whether a character is a vowel
bool sources::is_vowel(wchar_t c) {
    for(wchar_t vowel : vowels){
        if(c==vowel){
            return true;
        }
    }
    return false;
}

// Function to check whether a character is a consonant
bool sources::is_consonants(wchar_t c){
    for(wchar_t consonant : consonants){
        if(c==consonant){
            return true;
        }
    }
    return false;
}

// Function to add a text file to the list
void sources::add_resource(const std::string& s){
    list_of_txts_to_read.push_back(s);
}

void sources::initialize_source_file_names() {
    // TODO: before run project
    /* change the paths with your own path in sources.txt*/
    std::string filePath = "/home/tsima/CLionProjects/Georgian_words/sources.txt";
    std::ifstream file(filePath);
    std::vector<std::string> addresses;

    if (file) {
        std::string line;
        // Assuming all addresses are on a single line
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string address;
            while (std::getline(ss, address, ',')) {
                // Trim whitespace if necessary
                address.erase(address.find_last_not_of(" \n\r\t")+1);
                if (!address.empty()) {
                    addresses.push_back(address);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }

    for (const auto& addr : addresses) {
    //  std::cout << addr << std::endl;
        sources::add_resource(addr);
    }
}
