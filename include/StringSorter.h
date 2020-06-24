#ifndef STRINGSORTER_H
#define STRINGSORTER_H
#include <vector>
#include <iostream>



class StringSorter
{
    public:
        StringSorter();
        virtual ~StringSorter();
        std::vector<std::string> sortByLambdaSavingSource(std::vector<std::string> input, bool lambda(std::string first, std::string second));
        void sortByLambda(std::vector<std::string> input, bool lambda(std::string first, std::string second));
    protected:

    private:

};

#endif // STRINGSORTER_H
