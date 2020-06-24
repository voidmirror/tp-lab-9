#include "StringSorter.h"

StringSorter::StringSorter()
{
    //ctor
}

StringSorter::~StringSorter()
{
    //dtor
}

std::vector<std::string> StringSorter::sortByLambdaSavingSource(std::vector<std::string> input, bool lambda(std::string first, std::string second)){
    std::vector<std::string> res = input;
    this->sortByLambda(res, lambda);
    return res;
}

void StringSorter::sortByLambda(std::vector<std::string> input, bool lambda(std::string first, std::string second)){
    for(int i = 0; i < input.size() - 1; i++){
        for(int o = 0; o < input.size() - (i + 1); o++){
            if(lambda(input[o], input[o + 1])){
                std::swap(input[o], input[o + 1]);
            }
        }
    }
}
