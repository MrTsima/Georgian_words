//
// Created by mrtsima on 4/21/23.
//

#ifndef GEORGIAN_WORDS_txtSRAPPER_H
#define GEORGIAN_WORDS_txtSRAPPER_H

#include <bits/stdc++.h>
using namespace std;

class txtSrapper {


public:
    static vector<vector<wstring> >  scrap(const string& filename);

    static vector<vector<wstring>> scrapPdf(const string &filename);

    static vector<vector<wstring>> scrapTxt(const string &filename);

    static vector<wstring> processLine(const wstring &line);
};


#endif //GEORGIAN_WORDS_txtSRAPPER_H
