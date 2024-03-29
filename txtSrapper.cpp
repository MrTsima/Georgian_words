//
// Created by mrtsima on 4/21/23.
//

#include "txtSrapper.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <fstream>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>



std::vector<std::vector<std::wstring>> txtSrapper::scrap(const std::string& filename) {
    // Set the locale to support UTF-8 encoding
    setlocale(LC_ALL, "ka_GE.UTF-8");

    // Determine file type and call the appropriate method
    if (filename.substr(filename.find_last_of(".") + 1) == "pdf") {
        return txtSrapper::scrapPdf(filename);
    } else {
        return txtSrapper::scrapTxt(filename);
    }
}

std::vector<std::vector<std::wstring>> txtSrapper::scrapPdf(const std::string& filename) {
    std::vector<std::vector<std::wstring>> pages;
    auto doc = poppler::document::load_from_file(filename);
    if (!doc) {
        std::cerr << "Failed to open PDF file." << std::endl;
        return pages; // Return empty if failed to open
    }

    for (int i = 0; i < doc->pages(); ++i) {
        auto pg = doc->create_page(i);
        auto utf8Text = pg->text().to_utf8();
        std::string text(utf8Text.begin(), utf8Text.end());
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        std::wstring wtext = conv.from_bytes(text);

        // Process text (now in std::wstring format) to extract Georgian words
        std::vector<std::wstring> words;
        std::wstring word = L"";
        for (wchar_t c: wtext) {
            if (iswspace(c) || iswpunct(c)||(c < L'ა' || c > L'ჰ')) {
                if (!word.empty()) {
                   // cout << std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(word) << std::endl;
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
    }
    return pages;
}

std::vector<std::vector<std::wstring>> txtSrapper::scrapTxt(const std::string& filename) {
    std::vector<std::vector<std::wstring>> pages;
    std::wifstream file(filename);

    if (file.is_open()) {
        while (true) {
            std::wstring line;
            if (getline(file, line)) {
                std::vector<std::wstring> words = processLine(line);
                if (!words.empty()) {
                    pages.push_back(words);
                }
            } else {
                break;
            }
        }
    }
    return pages;
}

std::vector<std::wstring> txtSrapper::processLine(const std::wstring& line) {
    // Extract Georgian words from the text
    std::vector<std::wstring> words;
    std::wstring word = L"";
    for (wchar_t c: line) {
        if (iswspace(c) || iswpunct(c) || (c < L'ა' || c > L'ჰ')) {
            if (!word.empty()) {
                words.push_back(word);
                word = L"";
            }
        } else if (iswalpha(c)) {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

