#ifndef other
#define other
#include "common include.hpp"
    inline bool belong(const std::string sub,std::string& mainstr)
    {
        if (sub.length() > mainstr.length()) return false;
        for (int i=0;i<mainstr.length()-sub.length();i++)
        {
            if (sub == mainstr.substr(i,sub.length())) return true;
        }
        return false;
    }
#endif