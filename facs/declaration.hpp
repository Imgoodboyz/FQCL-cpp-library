#ifndef declare
#define declare
#include "include.hpp"
class Empty
{
    public:
    Empty() {}
    Empty(std::ifstream& in) {}
    Empty(std::ifstream& in,const std::string& kw) {}
    Empty(std::ifstream& f,int rg) {}
    Empty(std::ifstream& f,const std::string& str,int range) {}
    Empty(std::ifstream& f,const std::string& str,int range) {}
};
enum MainMode{Offset,Text,Full,Lent};
enum SubMode{Norm,Keyw,SKeyw,EKeyw,SLent,ELent,SKSL,SKEL,EKSL,EKEL};
    struct Fidx
    {
	std::streampos pos;
	std::string data;
    };

#endif