//
// Created by Bedareva on 08.01.2023.
//
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <thread>

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#endif //SEARCH_ENGINE_INVERTEDINDEX_H

std::string MakeCurrentWay(std::string way){
    std::string current_way="";

    for(int i = 0;i<way.size();i++){
        current_way=current_way+way[i];
        if(way[i]=='\\') current_way=current_way+"\\";
    }

    return current_way;
};

std::vector<std::string> IsStringVector(std::string text){
    std::vector<std::string> slova;
    std::string str;
    for (int i=0;i<text.size();i++){
        if(text[i]==' '){

            slova.push_back(str);
            str="";
        }else str+=text[i];
    }
    return slova;
}


struct Entry {
    size_t doc_id;
    int count;
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> input_docs){

        for(int i=0;i<input_docs.size();i++){
            std::string text;
            char line;

            std::ifstream file(MakeCurrentWay(input_docs[i]));

            if (file.is_open())
            {
                while (file.get(line))
                {
                    text=text+line;

                }
            }else std::cout<<"ERROR"<<std::endl;
            file.close();
            docs.push_back(text);
        }

    };

    void GetWordCount(std::string word){

        std::vector<Entry> frequency;
        for(int i=0;i<docs.size();i++)
        {
            Entry t;
            int c=0;
            std::vector<std::string> set = IsStringVector(docs[i]);

            for (int j=0;j<set.size();j++){
                if(set[j]==word){
                    c=c+1;
                }
            }
            if(c>0){
                t.doc_id=i;
                t.count=c;
                frequency.push_back(t);
            }
        }
        if(!frequency.empty()){
            freq_dictionary[word]=frequency;
        }

    };

    std::vector<std::string> GetDocs(){
        return docs;
    }

    std::map<std::string, std::vector<Entry>> GetFreq_dictionary(){
        return freq_dictionary;
    }


private:
    std::vector<std::string> docs;// список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотны словарь
};
