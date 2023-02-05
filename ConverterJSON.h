#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#pragma once
#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
#endif //SEARCH_ENGINE_CONVERTERJSON_H
#include <string>
class ConverterJSON {
public:

    std::vector<std::string> GetTextDocuments(){

        std::ifstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\config.json");
        nlohmann::json dict;
        file>>dict;

        std::vector<std::string> vector;

        for(int i=0;i<5;i++){
            vector.push_back(dict["files"][i]);
        }
        return vector;
    };

    int GetResponsesLimit(){

        std::ifstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\config.json");
        nlohmann::json dict;
        file>>dict;
        return dict["config"]["max_responses"];
    };


    std::vector<std::string> GetRequests(){
        std::ifstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\requests.json");
        nlohmann::json dict;
        file>>dict;

        std::vector<std::string> vector;

        for(int i=0;i<4;i++){
            vector.push_back(dict["requests"][i]);
        }
        return vector;
    };

   struct Request{
       bool result;
       std::vector<RelativeIndex> relevance;

   };

    void putAnswers(std::vector<std::vector<RelativeIndex>> answers){
        std::ofstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\answers.json");

        file<<"{\"answers\":{\n";
        for (int i=0;i<4;i++){
            file<<"\"request"<<std::to_string(i+1)<<"\":{\n \"result\": ";
            if(answers[i].size()==0){
                if(i==3)file<<"\"false\"}";
                else file<<"\"false\"},";
            }else{
                file<<"\"true\",\n";
                file<<"\"relevance\": {\n";
                if(i!=3){
                    for(int j=0;j<answers[i].size()-1;j++){
                        file<<"\"docid\": "<<answers[i][j].doc_id<<", \"rank\" : "<<answers[i][j].rank<<","<<'\n';
                    }
                }

                if(i==3) file<<"\"docid\": "<<answers[i][answers[i].size()-1].doc_id<<", \"rank\" : "<<answers[i][answers[i].size()-1].rank<<""<<'\n'<<'}'<<'\n'<<"}\n";
                else file<<"\"docid\": "<<answers[i][answers[i].size()-1].doc_id<<", \"rank\" : "<<answers[i][answers[i].size()-1].rank<<""<<'\n'<<'}'<<'\n'<<"},\n";
            }
        }
        file<<'}'<<'\n';
        file<<'}';
        file.close();
    };


};