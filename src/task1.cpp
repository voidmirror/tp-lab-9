#include "task1.h"

std::vector<std::string> sort(std::vector<std::string> var, bool comp(const std::string& a, const std::string& b))
{
    for (size_t i = 0; i < var.size()-1; i++)
    {
        for (size_t j = 0; j < var.size()-i-1; j++)
        {
            if (comp(var[j], var[j+1]))
            {
                std::swap(var[j], var[j+1]);
            }
        }
    }
    return var;
}

std::vector<std::string> sortByAscendingLength(std::vector<std::string> var)
{
    return sort(var, [](const std::string& a, const std::string& b){ return a.length() > b.length();});
}

std::vector<std::string> sortByDescendingLength(std::vector<std::string> var)
{
    return sort(var, [](const std::string& a, const std::string& b){ return a.length() < b.length();});
}

std::vector<std::string> sortByAscending(std::vector<std::string> var)
{
    return sort(var, [](const std::string& a, const std::string& b){ return a > b;});
}

std::vector<std::string> sortByDescending(std::vector<std::string> var)
{
    return sort(var, [](const std::string& a, const std::string& b){ return a < b;});
}

std::vector<std::string> sortByAscendingLastCharacters(std::vector<std::string> var)
{
    return sort(var, [](const std::string& a, const std::string& b){ return a[a.size()-1] > b[b.size()-1];});
}

std::vector<std::string> sortByDescendingLastCharacters(std::vector<std::string> var)
{
    return sort(var, [](const std::string& a, const std::string& b){ return a[a.size()-1] < b[b.size()-1];});
}