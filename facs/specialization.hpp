#ifndef spec_hpp
#define spec_hpp
#include "include.hpp"
#include "declaration.hpp"
#include "subf.hpp"
    template<MainMode M,SubMode S>
    class takeline;
    // offset section
    template<>
    class takeline<Offset,Norm> : size_base<takeline<Offset,Norm>>
    {
        private:
            Empty p;
            std::vector<std::fpos<mbstate_t>> vec;
        public:
        takeline(std::ifstream& in) : p(in)
        {
	        std::streampos pos = 0;
	        std::string str;
	        while (true)
	            {
		            if (!internal_requied(in,vec,pos,str)) break;
		            vec.push_back(pos);
	            }
        }
        std::streampos operator[] (int iter)
        {
            return vec[iter];
        }
    };
    template<>
    class takeline<Offset,EKeyw> : size_base<takeline<Offset,EKeyw>>
    {
        private:
            std::vector<std::streampos> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,const std::string& kw) : p(f,kw)
            {
                std::streampos pos = 0;
                std::string str;
                while (true)
                {
                    if (!internal_requied(f,vec,pos,str)) break;
                    if(!utils::belong(kw,str)) vec.push_back(pos);
                }
            }
            std::streampos operator[] (int iter)
            {
                return vec[iter];
            }
    };
    template<>
    class takeline<Offset,SKeyw> : size_base<takeline<Offset,SKeyw>>
    {
        private:
            std::vector<std::streampos> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,const std::string& kw) : p(f,kw)
            {
                std::streampos pos = 0;
                std::string str;
                while (true)
                {
                    pos = f.tellg();
                    if (!std::getline(f,str)) break;
                    if (utils::belong(kw,str)) vec.push_back(pos);
                }
            }
            std::streampos operator[] (int iter)
            {
                return vec[iter];
            }
    };
    template<>
    class takeline<Offset,SLent> : size_base<takeline<Offset,SLent>>
    {
        private:
            std::vector<std::streampos> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,int range) : p(f,range)
            {
                std::string str;
                std::streampos pos;
                while (true)
                {
                    pos = f.tellg();
                    if (!std::getline(f,str)) break;
                    if (str.length() == range) vec.push_back(pos);
                }
            }
            std::streampos& operator[] (int iter)
            {
                return vec[iter];
            }
    };
    template<>
    class takeline<Offset,ELent> : size_base<takeline<Offset,ELent>>
    {
        private:
            std::vector<std::streampos> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,int range) : p(f,range)
            {
                std::string str;
                std::streampos pos;
                while (true)
                {
                    pos = f.tellg();
                    if (!std::getline(f,str)) break;
                    if (str.length() != range) vec.push_back(pos);
                }
            }
            std::streampos& operator[] (int iter)
            {
                return vec[iter];
            }
    };
    //end of offset section

    // text section
    template<>
    class takeline<Text,Norm> : size_base<takeline<Text,Norm>>
    {
        private:
            std::vector<std::string> vec;
            Empty p;
        public:
	        takeline(std::ifstream& f) : p(f)
	        {
	            f.clear();
	            std::string str;
	            while (true)
	            {
		            if (!std::getline(f,str)) break;
	                vec.push_back(str);
                }
            }
            std::string operator[] (int iter)
            {
                return vec[iter];
            }
    };
    template<>
    class takeline<Text,SKeyw> : size_base<takeline<Text,SKeyw>>
    {
        private:
            std::vector<std::string> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,const std::string& kw) : p(f,kw)
            {
                std::string str;
                while(true)
                {
                    if (!std::getline(f,str)) break;
                    if (utils::belong(kw,str)) vec.push_back(str);
                }
            }
            std::string operator[] (int iter)
            {
                return vec[iter];
            }
    };
    template<>
    class takeline<Text,EKeyw> : size_base<takeline<Text,EKeyw>>
    {
        private:
            std::vector<std::string> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,const std::string& kw) : p(f,kw)
            {
                std::string str;
                while (true)
                {
                    if (!std::getline(f,str)) break;
                    if (!utils::belong(kw,str)) vec.push_back(str);
                }
            }
            std::string operator[] (int iter)
            {
                return vec[iter];
            }
    };
    template<>
    class takeline<Text,SLent> : size_base<takeline<Text,SLent>>
    {
        private:
            std::vector<std::string> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,int range) : p(f,range)
            {
                std::string str;
                while (true)
                {
                    if (!std::getline(f,str)) break;
                    if (str.length() == range) vec.push_back(str);
                }
            }
            std::string& operator[] (int iter)
            {
                return vec[iter];
            }
    };
    template<>
    class takeline<Text,ELent> : size_base<takeline<Text,ELent>>
    {
        private:
            std::vector<std::string> vec;
            Empty p;
        public:
            takeline(std::ifstream& f,int range) : p(f,range)
            {
                std::string str;
                while (true)
                {
                    if (!std::getline(f,str)) break;
                    if (str.length() != range) vec.push_back(str);
                }
            }
            std::string& operator[] (int iter)
            {
                return vec[iter];
            }
    };
    //end of text section

    //full section
    template<>
    class takeline<Full,Norm> : size_base<takeline<Full,Norm>>
    {
        private:
            std::vector<Fidx> vec;
            Empty p;
        public:
            takeline(std::ifstream& f) : p(f)
            {
    	        f.clear();
    	        std::streampos pos = 0;
    	        std::string str;
    	        while (true)
    	            {
    		            pos = f.tellg();
    		            if (!std::getline(f,str)) break;
    		            vec.push_back({pos,str});
    	            }
            }
            Fidx operator[] (int iter)
            {
                return vec[iter];
            }
    };
    //end of full section

    // lent section
    template<>
    class takeline<Lent,Norm> : size_base<takeline<Lent,Norm>>
    {
        private:
            std::vector<int> vec;
            Empty p;
        public:
            takeline(std::ifstream& f) : p(f)
            {
                std::string str;
                while (true)
                {
                    if (!std::getline(f,str)) break;
                    vec.push_back(str.length());
                }
            }
            int operator[] (int iter)
            {return vec[iter];}
    };
    template<>
    class takeline<Lent,SKeyw> : Empty : size_base<takeline<Lent,SKeyw>>
    {
        private:
            std::vector<size_t> vec;
        public:
            takeline(std::ifstream& f,const std::string& kw) : Empty(f,kw)
            {
                std::string str;
                while (true)
                {
                    if (!std::getline(f,str)) break;
                    if (utils::belong(kw,str)) vec.push_back(str.length());
                }
            }
            size_t operator[] (size_t iter)
            {return vec[iter];}
    };
    template<>
    class takeline<Lent,EKeyw> : Empty : size_base<takeline<Lent,EKeyw>>
    {
        private:
            std::vector<size_t> vec;
        public:
            takeline(std::ifstream& f,const std::string& str) : Empty(f,str)
            {
                std::string t;
                while (true)
                {
                    
                }
            }
    };
    //end of lent section
//end of takeline specialization section
#endif