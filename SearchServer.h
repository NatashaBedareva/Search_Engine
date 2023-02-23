#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include "InvertedIndex.h"



struct RelativeIndex{
    size_t doc_id;
    float rank;
};

class SearchServer {
public:

    std::vector<RelativeIndex> bubbleSort(std::vector<RelativeIndex> list, int listLength);
    void setFreqDictionari(std::map<std::string, std::vector<Entry>> _freq_dictionary);
    std::vector<std::vector<RelativeIndex>> Search(std::vector<std::string> queries_input, std::vector<std::string> text_documents);

private:
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};