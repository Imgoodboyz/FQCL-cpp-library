#ifndef sub_hpp
#define sub_hpp
#include "include.hpp"
inline bool internal_requied(std::ifstream& f,std::vector<std::fpos<mbstate_t>>& vec,std::fpos<mbstate_t>& pos,std::string& str)
{
        pos = f.tellg();
        if (!std::getline(f,str)) return false;
        return true;
}
#endif