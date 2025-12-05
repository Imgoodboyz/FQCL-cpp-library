#ifndef facs_hpp
#define facs_hpp
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
enum Mode {Text,Offset,Full};
typedef std::fpos<mbstate_t> fpos;
   #define facs_version "v0.0.16 future view"
class Facs : public std::fstream
 {
    public:
    Facs(const std::string& filename,const std::ios::openmode mode) : std::fstream(filename,mode)
    {
        if (!is_open()) throw std::runtime_error("no such file or dirrectory!");
    }
    struct Fidx
    {
	std::streampos pos;
	std::string data;
    };
    using std::fstream::clear;
    using std::fstream::seekg;
    using std::fstream::seekp;
    using std::fstream::tellg;
    inline void rol(std::fpos<mbstate_t> pos,std::string& outs)
    {
    this->clear();
    seekg(pos);
    std::getline(*this,outs);
    }
    template<Mode M>
    struct takeline;
    template<>
    struct takeline<Mode::Offset>
    {
        inline static void index(std::istream& in,std::vector<std::streampos>& vec)
	{
	    in.clear();
	    std::streampos pos = 0;
	    std::string str;
	    while (true)
	    {
		pos = in.tellg();
		if(!std::getline(in,str)) return;
		vec.push_back(pos);
	    }
	}
    };
    template<>
    struct takeline<Mode::Text>
    {
	inline static void index(std::istream& in,std::vector<std::string>& vec)
	{
	    in.clear();
	    std::string str;
	    while (true)
	    {
		if (!std::getline(in,str)) return;
		vec.push_back(str);
	    }
	}
    };
    template<>
    struct takeline<Mode::Full>
    {
        inline static void index(std::istream& in,std::vector<Fidx>& vec)
	{
	    in.clear();
	    std::streampos pos = 0;
	    std::string str;
	    while (true)
	    {
		pos = in.tellg();
		if (!std::getline(in,str)) return;
		vec.push_back({pos,str});
	    }
        }
    };
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
    inline bool writeable()
    {
        write("");;
        return good();
    }
    inline std::string write(const std::string data)
    {
        if (!is_open()) return "cant_open";
        *this << data << std::endl;
        return data;
    }
    ~Facs() {close();};
};
namespace ultils
{
    inline std::vector<std::string> reverse_vector(std::vector<std::string> vec)
    {
        std::vector<std::string> new_vec;
        for (int len=vec.size();len >= 0;--len)
        {
             new_vec.push_back(vec[len]);
        }
        return new_vec;
    }
}
#endif
