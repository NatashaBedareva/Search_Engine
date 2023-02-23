#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cassert>
#pragma once

#include "SearchServer.h"
#include <string>

class ThePathIsNotSpecifiedCorrectly:public std::exception{
    const char* what() const noexcept override{
        return "The path is not specified correctly";
    }
};
class jsonFileNotCorrect:public std::exception{
    const char* what() const noexcept override{
        return "JSON file not correct";
    }
};

class ConverterJSON {
public:


    std::vector<std::string> GetTextDocuments(){

        std::ifstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\config.json");
        nlohmann::json dict;
        std::vector<std::string> vector;
        try{
            if(!file){
                throw ThePathIsNotSpecifiedCorrectly();
            }

            file>>dict;
            try{
                if(dict.count("files")!=1 or dict.size()==0){
                    throw jsonFileNotCorrect();
                }
                for(int i=0;i<5;i++){
                    vector.push_back(dict["files"][i]);
                }
                return vector;
            }
            catch (const std::exception& x){
                std::cout<<"Caught exception: "<<x.what()<<std::endl;
            }

        }
        catch (const std::exception& x){
            std::cout<<"Caught exception: "<<x.what()<<std::endl;

        }

    };

    int GetResponsesLimit(){

        std::ifstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\config.json");
        nlohmann::json dict;
        try {
            if(!file){
                throw ThePathIsNotSpecifiedCorrectly();
            }
            file >> dict;
            return dict["config"]["max_responses"];
        }
        catch (const std::exception& x){
            std::cout<<"Caught exception: "<<x.what()<<std::endl;

        }
    };


    std::vector<std::string> GetRequests(){
        std::ifstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\requests.json");
        nlohmann::json dict;
        try {
            if(!file){
                throw ThePathIsNotSpecifiedCorrectly();
            }
            file >> dict;
            std::vector<std::string> vector;
            try{
                if(dict.count("requests")!=1 or dict.size()==0){
                    throw jsonFileNotCorrect();
                }
                for (int i = 0; i < 4; i++) {
                    vector.push_back(dict["requests"][i]);
                }
                return vector;
            }
            catch (const std::exception& x){
                std::cout<<"Caught exception: "<<x.what()<<std::endl;

            }


        }
        catch (const std::exception& x){
            std::cout<<"Caught exception: "<<x.what()<<std::endl;

        }
    };



    void putAnswers(std::vector<std::vector<RelativeIndex>> answers){
        std::ofstream file("C:\\Users\\Bedareva\\Documents\\search_engine\\answers.json");
        try {
            if(!file){
                throw ThePathIsNotSpecifiedCorrectly();
            }
            file << "{\"answers\":{\n";
            for (int i = 0; i < 4; i++) {
                file << "\"request" << std::to_string(i + 1) << "\":{\n \"result\": ";
                if (answers[i].size() == 0) {
                    if (i == 3)file << "\"false\"}";
                    else file << "\"false\"},";
                } else {
                    file << "\"true\",\n";
                    file << "\"relevance\": {\n";
                    if (i != 3) {
                        for (int j = 0; j < answers[i].size() - 1; j++) {
                            file << "\"docid\": " << answers[i][j].doc_id << ", \"rank\" : " << answers[i][j].rank
                                 << "," << '\n';
                        }
                    }

                    if (i == 3)
                        file << "\"docid\": " << answers[i][answers[i].size() - 1].doc_id << ", \"rank\" : "
                             << answers[i][answers[i].size() - 1].rank << "" << '\n' << '}' << '\n' << "}\n";
                    else
                        file << "\"docid\": " << answers[i][answers[i].size() - 1].doc_id << ", \"rank\" : "
                             << answers[i][answers[i].size() - 1].rank << "" << '\n' << '}' << '\n' << "},\n";
                }
            }
            file << '}' << '\n';
            file << '}';
            file.close();
        }
        catch (const std::exception& x){
            std::cout<<"Caught exception: "<<x.what()<<std::endl;

        }
    };


};