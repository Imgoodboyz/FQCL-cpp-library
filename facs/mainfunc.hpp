#ifndef mainfunc
#define mainfunc
#include "include.hpp"

class Facs : public std::ifstream
 {
    public:
    Facs(const std::string& filename,const std::ios::openmode mode) : std::ifstream(filename,mode)
    {
        if (!is_open()) throw "can't open file";
    }
    using std::ifstream::clear;
    using std::ifstream::seekg;
    using std::ifstream::tellg;
    inline void rol(std::fpos<mbstate_t> pos,std::string& outs)
    {
    this->clear();
    seekg(pos);
    std::getline(*this,outs);
    }
    inline bool exist()
    {
        return is_open() || good();
    }
    inline bool readable()
    {
        char ch;
        get(ch);
        return good();
    }
    ~Facs() {close();};
};
#endif