#ifndef spec_hpp
#define spec_hpp
#include "include.hpp"
#include "declaration.hpp"
#include "subf.hpp"
#include "../utils/io_utils.hpp"
    template<MainMode M,SubMode S>
    class takeline;
    // offset section
    template<>
    class takeline<Offset,Norm>
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
		            if (!internal_requied(in,pos,str)) break;
		            vec.push_back(pos);
	            }
        }
        std::streampos operator[] (int iter)
        {
            return vec[iter];
        }
        size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Offset,EKeyw>
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
                    if (!internal_requied(f,pos,str)) break;
                    if(!utils::belong_const_f(kw,str)) vec.push_back(pos);
                }
            }
            std::streampos operator[] (int iter)
            {
                return vec[iter];
            }
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Offset,SKeyw>
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
                    if (utils::belong_const_f(kw,str)) vec.push_back(pos);
                }
            }
            std::streampos operator[] (int iter)
            {
                return vec[iter];
            }
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Offset,SLent>
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
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Offset,ELent>
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
            size_t operator() ()
        {return vec.size();}
    };
    //end of offset section

    // text section
    template<>
    class takeline<Text,Norm>
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
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Text,SKeyw>
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
                    if (utils::belong_const_f(kw,str)) vec.push_back(str);
                }
            }
            std::string operator[] (int iter)
            {
                return vec[iter];
            }
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Text,EKeyw>
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
                    if (!utils::belong_const_f(kw,str)) vec.push_back(str);
                }
            }
            std::string operator[] (int iter)
            {
                return vec[iter];
            }
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Text,SLent>
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
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Text,ELent>
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
            size_t operator() ()
        {return vec.size();}
    };
    //end of text section

    //full section
    template<>
    class takeline<Full,Norm> : Empty
    {
        private:
            std::vector<Fidx> vec;
        public:
            takeline(std::ifstream& f) : Empty(f)
            {
    	        f.clear();
    	        std::streampos pos = 0;
    	        std::string str;
    	        while (true)
    	            {
    		            if (!internal_requied(f,pos,str)) break;
    		            vec.push_back({pos,str});
    	            }
            }
            Fidx operator[] (int iter)
            {
                return vec[iter];
            }
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Full,SKeyw> : Empty
    {
        private:
            std::vector<Fidx> vec;
        public:
            takeline(std::ifstream& f,const std::string& str) : Empty(f,str)
            {
                std::fpos<mbstate_t> pos;
                std::string st;
                while (true)
                {
                    if (!internal_requied(f,pos,st)) break;
                    if (utils::belong_const_f(str,st)) vec.push_back({pos,st});
                }
            }
            Fidx& operator[] (size_t iter)
            {return vec[iter];}
            size_t operator() (size_t iter)
            {return vec.size();}
    };
    template<>
    class takeline<Full,EKeyw> : Empty
    {
        private:
            std::vector<Fidx> vec;
        public:
            takeline(std::ifstream& f,const std::string& str) : Empty(f,str)
            {
                std::fpos<mbstate_t> pos;
                std::string st;
                while (true)
                {
                    if (!internal_requied(f,pos,st)) break;
                    if (!utils::belong_const_f(str,st)) vec.push_back({pos,st});
                }
            }
            Fidx& operator[] (size_t iter)
            {return vec[iter];}
            size_t operator() ()
            {return vec.size();}
    };
    template<>
    class takeline<Full,SLent> : Empty
    {
        private:
            std::vector<Fidx> vec;
        public:
            takeline(std::ifstream& f,int range) : Empty(f,range)
            {
                std::fpos<mbstate_t> pos;
                std::string str;
                while (true)
                {
                    if (!internal_requied(f,pos,str)) break;
                    if (str.length() == range) vec.push_back({pos,str});
                }
            }
            Fidx& operator[] (size_t iter)
            {return vec[iter];}
            size_t operator() ()
            {return vec.size();}
    };
    
    //end of full section

    // lent section
    template<>
    class takeline<Lent,Norm>
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
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Lent,SKeyw> : Empty
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
                    if (utils::belong_const_f(kw,str)) vec.push_back(str.length());
                }
            }
            size_t operator[] (size_t iter)
            {return vec[iter];}
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Lent,EKeyw> : Empty
    {
        private:
            std::vector<size_t> vec;
        public:
            takeline(std::ifstream& f,const std::string& str) : Empty(f,str)
            {
                std::string t;
                while (true)
                {
                    if(!internal_requied_num(f,t)) break;
                    if (utils::belong_const_f(str,t)) vec.push_back(t.length());
                }
            }
            size_t operator[] (size_t iter) {return vec[iter];}
            size_t operator() ()
        {return vec.size();}
    };
    template<>
    class takeline<Lent,SLent> : Empty
    {
        private:
            std::vector<size_t> vec;
        public:
            takeline(std::ifstream& f,int range) : Empty(f,range)
            {
                std::string str;
                while (true)
                {
                    if (!internal_requied_num(f,str)) break;
                    if (str.length() == range) vec.push_back(str.length());
                }
            }
            size_t operator[] (size_t iter)
            {return vec[iter];}
            size_t operator() ()
        {return vec.size();}
    };
    template<> 
    class takeline<Lent,SLent> : Empty
    {
        private:
            std::vector<size_t> vec;
        public:
            takeline(std::ifstream& f,int range)
            {
                std::string str;
                while(true)
                {
                    if (!internal_requied_num(f,str)) break;
                    if (str.length() == range) vec.push_back(str.length());
                }
            }
            size_t operator[] (size_t iter)
            {return vec[iter];}
            size_t operator() ()
            {
                return vec.size();
            }
    };
    template<>
    class takeline<Lent,ELent>
    {
        private:
            std::vector<size_t> vec;
        public:
            takeline(std::ifstream& f,size_t range)
            {
                std::string str;
                while (true)
                {
                    if (!internal_requied_num(f,str)) break;
                    if (str.length() != range) vec.push_back(str.length());
                }
            }
            size_t operator[] (size_t iter)
            {return vec[iter];}
            size_t operator() ()
            {return vec.size();}
    };
    //end of lent section
//end of takeline specialization section
#endif