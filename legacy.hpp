#ifndef header
#define header
#define version "0.0.19-beta"
#define minimum "c++ 98"
#define last_update "16/11/2025"
#define authorizer "imgoodboy"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
namespace fclc
{
    inline double sum(std::vector<double>num)
    {
       int i = num.size();
       double total = 0;
       for (int x=0;x<i;x++)
       {
          total += num[x];
       }
       return total;
    }
    inline double avg(std::vector<double>num)
    {
       int i = num.size();
       double total = 0;
       int length = 0;
       for (int x = 0;x<i;x++)
       {
          total += num[x];
          length += 1;
       }
       return total/length;
    }
    inline int log(int g)
    {
        if (g == 1) return g;
        return g*log(g-1);
    }
}
namespace facs
{
    inline void takeline(std::string filename,std::vector<std::fpos<mbstate_t> >& vec)
    {
         std::ifstream f(filename);
         std::string str;
         char ch;
         std::fpos<mbstate_t> pos = 0;
         while (true)
         {
               f.seekg(pos);
               std::getline(f,str);
               if (!std::getline(f,str)) return;
               pos = f.tellg();
               vec.push_back(std::fpos<mbstate_t>(pos));
         }
    }
    inline void rol(std::string filename,std::fpos<mbstate_t> pos,std::string& str)
    {
    std::ifstream f(filename);
    f.seekg(pos);
    std::getline(f,str);
    }
    inline bool exist(std::string name)
    {
        std::ifstream hd(name);
        return hd.is_open() || hd.good();
    }
    inline bool readable(std::string name)
    {
	std::ifstream fc(name,std::ios::in);
        return fc.good();
    }
    inline bool writeable(std::string name)
    {
	std::ofstream fo(name,std::ios::app);
        fo << "";
        return fo.good();
    }
    template<typename T>
    inline T write(const std::string file,const T data)
    {
        std::ofstream out(file,std::ios::app);
        if (!out.is_open()) return "cant_open";
        out << data << std::endl;
        return data;
    }
    inline std::string read(std::string file)
    {
    	std::ifstream dc(file,std::ios::in);
	if (!dc.is_open())
	{
	   throw std::runtime_error("cant open.file");
	}
	std::string out;
	std::getline(dc, out);
	return out;
    }
    template<typename T>
    inline void prt(const T& data,bool line)
    {
        if (line == true)
        {
             std::cout<<data<<std::endl;
        }
        if (line == false)
        {
             std::cout<<data;
        }
        return;
    }
    template<typename E>
    inline void ipt(E& name)
    {
        std::cin>>name;
        if (std::cin.fail())
        {
             std::cin.clear();
             std::cin.ignore();
        }
        return;
    }
}
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
