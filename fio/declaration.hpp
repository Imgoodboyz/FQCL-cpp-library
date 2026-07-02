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
    Empty(std::ifstream& f,const std::string& str,size_t range) {}
};
enum MainMode{Offset,Text,Both,Lent};
enum SubMode{Norm,SKeyw,EKeyw,SLent,ELent,SKSL,SKEL,EKSL,EKEL,SRange,ERange};
    struct Fidx
    {
	std::streampos pos;
	std::string data;
    };
#endif
