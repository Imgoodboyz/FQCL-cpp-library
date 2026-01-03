#include "include.hpp"
class Empty
{
    public:
    Empty() {}
    Empty(std::ifstream& in) {}
    Empty(std::ifstream& in,const std::string kw) {}
    Empty(std::ifstream& f,int rg) {}
};
enum MainMode{Offset,Text,Full,Lent};
enum SubMode{Norm,Keyw,SKeyw,EKeyw,SLent,ELent};
    struct Fidx
    {
	std::streampos pos;
	std::string data;
    };
template<class T>
class size_base
{
    std::vector<std::fpos<mbstate_t>> vec = static_cast<T>(*this)->vec;
};