#ifndef io_utils
#define io_utils
#include "common include.hpp"
namespace utils
{
    inline bool const_belong(const std::string& sub,const std::string& mainstr)
    {
        if (sub.length() > mainstr.length()) return false;
        for (int i=0;i<mainstr.length()-sub.length();i++)
        {
            if (sub == mainstr.substr(i,sub.length())) return true;
        }
        return false;
    }
    inline bool belong(std::string& sub,std::string& mainstr)
    {
        if (sub.length() > mainstr.length()) return false;
        for (int i=0;i<mainstr.length()-sub.length();i++)
        {
            if (sub == mainstr.substr(i,sub.length())) return true;
        }
        return false;
    }
    inline bool belong_const_f(const std::string& sub,std::string& mainstr)
    {
        if (sub.length() > mainstr.length()) return false;
        for (int i=0;i<mainstr.length()-sub.length();i++)
        {
            if (sub == mainstr.substr(i,sub.length())) return true;
        }
        return false;
    }
    inline bool belong_const_a(std::string& sub,const std::string& mainstr)
    {
        if (sub.length() > mainstr.length()) return false;
        for (int i=0;i<mainstr.length()-sub.length();i++)
        {
            if (sub == mainstr.substr(i,sub.length())) return true;
        }
        return false;
    }
}
#endif