#include <fstream>
#include <string>
#include "declaration.hpp"
#include "../fult/io_utils.hpp"

namespace experimental
{
template<MainMode m,SubMode s>
class takeline {};

#define Norm_mode \
x(Offset,std::streampos,pos) \
x(Text,std::string,str) \
x(Both,Fidx,Fidx({pos,str})) \
x(Lent,size_t,str.length())

#define Fidxall Fidx({pos,str})
#define tc (str.length()!=len)
#define fc (str.length()==len)
#define Near_generic \
fk(Offset,SKeyw,std::streampos,!utils::belong(kw,str),pos) \
fk(Offset,EKeyw,std::streampos,utils::belong(kw,str),pos) \
fk(Text,SKeyw,std::string,!utils::belong(kw,str),str) \
fk(Text,EKeyw,std::string,utils::belong(kw,str),str) \
fk(Both,SKeyw,Fidx,!utils::belong(kw,str),Fidx({pos,str})) \
fk(Both,EKeyw,Fidx,utils::belong(kw,str),Fidx({pos,str})) \
fk(Lent,SKeyw,size_t,!utils::belong(kw,str),str.length()) \
fk(Lent,EKeyw,size_t,utils::belong(kw,str),str.length())

#define LMode \
k(Offset,SLent,std::streampos,fc,pos) \
k(Offset,ELent,std::streampos,tc,pos) \
k(Text,SLent,std::streampos,fc,pos) \
k(Text,ELent,std::streampos,tc,pos) \
k(Lent,SLent,size_t,fc,str.length())\
k(Lent,ELent,size_t,tc,str.length())\
k(Both,SLent,Fidx,fc,Fidxall) \
k(Both,ELent,Fidx,tc,Fidxall)

#define range len
#define sksl (!utils::belong(kw,str)&&str.length()!=range)
#define skel (!utils::belong(kw,str)&&str.length()==range)
#define eksl (utils::belong(kw,str)&&str.length()!=range)
#define ekel (utils::belong(kw,str)&&str.length()==range)
#define DMode \
d(Offset,SKSL,std::streampos,sksl,pos) \
d(Offset,SKEL,std::streampos,skel,pos) \
d(Offset,EKSL,std::streampos,eksl,pos) \
d(Offset,EKEL,std::streampos,ekel,pos) \
d(Text,SKSL,std::string,sksl,str) \
d(Text,SKEL,std::string,skel,str) \
d(Text,EKSL,std::string,eksl,str) \
d(Text,EKEL,std::string,ekel,str) \
d(Both,SKSL,Fidx,sksl,Fidxall) \
d(Both,SKEL,Fidx,skel,Fidxall) \
d(Both,EKSL,Fidx,eksl,Fidxall) \
d(Both,EKEL,Fidx,ekel,Fidxall) \
d(Lent,SKSL,size_t,sksl,str.length()) \
d(Lent,SKEL,size_t,skel,str.length()) \
d(Lent,EKEL,size_t,ekel,str.length()) \
d(Lent,EKSL,size_t,eksl,str.length())

#define d(_mm,_sm,_tp,_cond,_ob) \
template<> \
class takeline<_mm,_sm> : public Empty \
{ \
	private: \
		std::vector<_tp> vec; \
	public: \
		takeline(std::fstream& f,std::string& kw,size_t len) \
		{ \
			std::string str; \
			std::streampos pos; \
			while(true) \
			{ \
				pos = f.tellg(); \
				if (std::getline(f,str) && _cond ) \
				{ \
					vec.push_back(_ob); \
					continue; \
				} \
				break; \
			} \
		} \
};
#define x(mode,tp,ob) \
template<> \
class takeline<mode,Norm> :public Empty \
{ \
private: \
    std::vector<tp> vec; \
public: \
    takeline(std::ifstream& f) : Empty(f) \
    { \
        std::string str; \
        std::streampos pos; \
        while(true) \
        { \
            pos = f.tellg(); \
            if(std::getline(f,str)) vec.push_back(ob); \
        } \
    } \
};
#define fk(_mm,_sm,_tp,_func,_ob) \
template<> \
class takeline<_mm,_sm> : public Empty \
{ \
    private: \
        std::vector<_tp> vec; \
    public: \
        takeline(std::ifstream& f,std::string kw) : Empty(f,kw) \
        { \
            std::string str; \
            std::streampos pos; \
            while (true) \
            { \
                pos = f.tellg(); \
                if (!std::getline(f,str) && _func) break; \
                vec.push_back(_ob); \
            } \
        } \
};
#define k(_mm,_sm,_tp,_cond,_ob) \
template<> \
class takeline<_mm,_sm> : public  Empty \
{ \
    private:\
        std::vector<_tp> vec;\
    public:\
        takeline(std::ifstream& f,size_t len) : Empty(f,len)\
        {\
            std::string str;\
            std::streampos pos;\
            while(true)\
            {\
                pos = f.tellg();\
                if (std::getline(f,str) && _cond)\
                {\
                    vec.push_back(_ob);\
                    continue;\
                }\
                break;\
            }\
        }\
};
LMode
#undef LMode
Near_generic
#undef Near_generic
Norm_mode
#undef Norm_mode
DMode
#undef DMode
}
