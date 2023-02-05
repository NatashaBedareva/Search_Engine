#pragma once
#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#endif //SEARCH_ENGINE_SEARCHSERVER_H
#include <algorithm>
#include <vector>
#include <iostream>
#include "InvertedIndex.h"
#include "SearchServer.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
};

std::vector<RelativeIndex> bubbleSort(std::vector<RelativeIndex> list, int listLength)
{

    while(listLength--)
    {

        bool swapped = false;

        for(int i = 0; i < listLength; i++)
        {
            //std::cout<<list[i].rank << list[i + 1].rank<<std::endl;
            if(list[i].rank < list[i + 1].rank)
            {
                std::swap(list[i], list[i + 1]);
                swapped = true;
            }
        }

        if(swapped == false)
            break;
    }
    return list;
}




class SearchServer {
public:

    void setFreqDictionari(std::map<std::string, std::vector<Entry>> _freq_dictionary){
        freq_dictionary=_freq_dictionary;
    };

    std::vector<std::vector<RelativeIndex>> Search(std::vector<std::string> queries_input, std::vector<std::string> text_documents){
        std::vector<RelativeIndex> relative_index_vector;
        std::vector<int> sum_poisk;
        for (int g=0;g<text_documents.size();g++){

            int summ=0;
            for (auto [first, second] : freq_dictionary)
            {

                for(int i=0;i<second.size();i++){
                    if(second[i].doc_id==g) {
                        summ += second[i].count;
                    }
                }

            }

            sum_poisk.push_back(summ);


        }

        int k=*max_element(sum_poisk.begin(), sum_poisk.end());

        for(int i=0;i<sum_poisk.size();i++){
            RelativeIndex relative_index;
            relative_index.doc_id=i;
            relative_index.rank=(float)sum_poisk[i]/k;
            relative_index_vector.push_back(relative_index);

        }

        std::vector<std::vector<RelativeIndex>> search_vector;


        for (int g=0;g<queries_input.size();g++){
            std::vector<RelativeIndex> relative_index_this_doc;
            for (auto [first, second] : freq_dictionary)
            {

                if(queries_input[g]==first){

                    for(int i=0;i<second.size();i++){
                        relative_index_this_doc.push_back(relative_index_vector[second[i].doc_id]);
                    }
                    break;
                }


            }
            search_vector.push_back(relative_index_this_doc);
        }


        for(int i=0;i<search_vector.size();i++){
            search_vector[i]=bubbleSort(search_vector[i],search_vector[i].size());
        }

        return search_vector;
    };


private:

    std::map<std::string, std::vector<Entry>> freq_dictionary;
};