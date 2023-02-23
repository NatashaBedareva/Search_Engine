#include "InvertedIndex.h"

std::string InvertedIndex::MakeCurrentWay(std::string way){
    std::string current_way="";

    for(int i = 0;i<way.size();i++){
        current_way=current_way+way[i];
        if(way[i]=='\\') current_way=current_way+"\\";
    }

    return current_way;
}

std::vector<std::string> InvertedIndex::IsStringVector(std::string text){
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

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){
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
}

void InvertedIndex::GetWordCount(std::string word){
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

}

std::vector<std::string> InvertedIndex::GetDocs(){
    return docs;
}

std::map<std::string, std::vector<Entry>> InvertedIndex::GetFreq_dictionary(){
    return freq_dictionary;
}