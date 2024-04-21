#include "textgen.h"

std::map<prefix, std::vector<std::string>> statetab; // префикс-суффиксы

std::vector<std::string> mySplit(std::string str, char separator) {
    std::vector<std::string> result;
    int first = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == separator) {
            result.push_back(str.substr(first, i - first));
            first = i + 1;
        }
    }
    if (first < str.length()) {
        result.push_back(str.substr(first, str.length() - first));
    }
    return result;
}

std::string gen(std::string text) {
    gen_tab(text, NPREF);

    return gen_text(MAXGEN);
}

prefix gen_pre(std::vector<std::string> words, int pos, int npref){
    prefix pre;
    for (int i = pos - npref; i < pos; i++) {
        pre.push_back(words[i]);
    }
    return pre;
}

void gen_tab(std::string text, int npref) {
    std::vector<std::string> words = mySplit(text, ' ');
    prefix pre;
    for (int i = npref; i < words.size(); i++) {
        pre = gen_pre(words, i, npref);
        statetab[pre].push_back(words[i]);
    }
}

std::string prefixToString(prefix pre) {
    std::string s = "";
    for (int i = 0; i < NPREF; i++) {
        s += pre.at(i) + " ";
    }
    return s;
}

std::string pick_next(prefix cur) {
    return statetab[cur][rand() % (statetab[cur].size())];
}

std::string gen_text(int size) {
    std::string result = "";
    prefix current;
    srand(static_cast<int> (time(0)));
    int first = rand() % (statetab.size());
    int ind = 0;
    for (const auto& el : statetab) {
        ind++;
        if (ind == first) {
            current = el.first;
            result += prefixToString(current);
            break;
        }
    }
    int genSize = 3;
    std::vector <std::string> suff;
    std::string pick;
    while (genSize < size) {
        if (statetab[current].size() == 0) 
            break;
        pick = pick_next(current);
        result += pick + " ";
        current.push_back(pick);
        current.pop_front();
        genSize++;
    }
    return result;
}