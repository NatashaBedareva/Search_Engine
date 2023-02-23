#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cassert>
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


    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);


};