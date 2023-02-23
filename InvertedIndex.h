
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <thread>



struct Entry {
    size_t doc_id;
    int count;
};

class InvertedIndex {
public:

    std::string MakeCurrentWay(std::string way);
    std::vector<std::string> IsStringVector(std::string text);
    void UpdateDocumentBase(std::vector<std::string> input_docs);
    void GetWordCount(std::string word);
    std::vector<std::string> GetDocs();
    std::map<std::string, std::vector<Entry>> GetFreq_dictionary();


private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
};
