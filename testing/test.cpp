#include "../facs.hpp"
int main() {
    std::ifstream f("testing\\test.txt", std::ios::binary);
    if (!f.is_open()) {
        std::cout << "Loi mo file!";
        return 1;
    }
    try 
    {
        std::string str;
        takeline<Text, Norm> t(f);
        f.clear();
        f.seekg(0);
        takeline<Text,SKeyw> u(f,"g");
        f.clear();
        f.seekg(0);
        takeline<Text,EKeyw> g(f,"g");
        f.clear();
        f.seekg(0);
        takeline<Text,SLent> h(f,16);
        f.clear();
        f.seekg(0);
        takeline<Text,ELent> j(f,16);
        f.clear();
        f.seekg(0);
        for (int i =0;i<t();i++)
        {
            std::cout<<t[i]<<std::endl;
        }
        std::cout<<"end part"<<std::endl;
        for (int i =0;i < u();i++)
        {
            std::cout<<u[i]<<std::endl;
        }
        std::cout<<"end part"<<std::endl;
        for (int i =0;i < g();i++)
        {
            std::cout<<g[i]<<std::endl;
        }
        std::cout<<"end part"<<std::endl;
        for (int i =0;i < h();i++)
        {
            std::cout<<h[i]<<std::endl;
        }
        std::cout<<"end part"<<std::endl;
        for (int i =0;i < j();i++)
        {
            std::cout<<j[i]<<std::endl;
        }
        std::cout<<"end part"<<std::endl;
    }
    catch(...)
    {
        std::cout<<"bug some where"<<std::endl;
    }
}