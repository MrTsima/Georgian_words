//
// Created by mrtsima on 4/21/23.
//

#include "txtSrapper.h"
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <iostream>
#include <locale>
#include <codecvt>

using namespace std;

// Set the locale to support UTF-8 encoding
vector<vector<wstring>> txtSrapper::scrap(const string& filename) {
    setlocale(LC_ALL, "ka_GE.UTF-8");
    vector<vector<wstring> >pages;
    wifstream file(filename);

    if (file.is_open()) {
        while(true){
            wstring line;
            if (getline(file, line)) {
                // Extract Georgian words from the text
                wstring word = L"";
                vector<wstring> words;
                for (wchar_t c: line) {
                    if (iswspace(c) || iswpunct(c)) {
                        if (!word.empty()) {
                            // Only consider Georgian words consisting entirely of Georgian letters
                            if (all_of(word.begin(), word.end(), [](wchar_t c) { return (c >= L'ა' && c <= L'ჰ'); })) {
                                words.push_back(word);
                            }
                            word = L"";
                        }
                    } else if (iswalpha(c)) {
                        word += c;
                    }
                }
                if (!word.empty()) {
                    // Only consider Georgian words consisting entirely of Georgian letters
                    if (all_of(word.begin(), word.end(), [](wchar_t c) { return (c >= L'ა' && c <= L'ჰ'); })) {
                        words.push_back(word);
                    }
                }
                pages.push_back(words);
            }else{
                break;
            }
        }
    }
    return pages;
}
