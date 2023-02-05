#include <iostream>
#include <string>
#include "SearchServer.h"
#include <omp.h>

#include "InvertedIndex.h"
#include "ConverterJSON.h"

int main() {
    ConverterJSON converter;

    InvertedIndex inverted_index;
    inverted_index.UpdateDocumentBase(converter.GetTextDocuments());
    std::vector<std::string> requests=converter.GetRequests();


    for(int j=0;j<requests.size();j++){
        inverted_index.GetWordCount(requests[j]);
    }

    std::map<std::string, std::vector<Entry>> freq_dictionary;
    freq_dictionary=inverted_index.GetFreq_dictionary();

    for (auto [first, second] : freq_dictionary)
    {
        std::cout << first << " ";
        for(int i=0;i<second.size();i++){
            std::cout <<'{' <<second[i].doc_id << ":"<<second[i].count<<"}";
        }
        std::cout<<std::endl;

    }

    SearchServer search_server;
    search_server.setFreqDictionari(inverted_index.GetFreq_dictionary());


    converter.putAnswers(search_server.Search(converter.GetRequests(),converter.GetTextDocuments()));

}
