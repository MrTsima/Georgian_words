//
// Created by mrtsima on 4/21/23.
//

#ifndef GEORGIAN_WORDS_txtSRAPPER_H
#define GEORGIAN_WORDS_txtSRAPPER_H

#include <bits/stdc++.h>

class txtSrapper {


public:
    static std::vector<std::vector<std::wstring> >  scrap(const std::string& filename);

    static std::vector<std::vector<std::wstring>> scrapPdf(const std::string &filename);

    static std::vector<std::vector<std::wstring>> scrapTxt(const std::string &filename);

    static std::vector<std::wstring> processLine(const std::wstring &line);
};


#endif //GEORGIAN_WORDS_txtSRAPPER_H
