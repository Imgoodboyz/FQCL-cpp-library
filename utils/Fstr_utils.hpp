#ifndef fstr
#define fstr
#include "common include.hpp"

class Fstr : public Empty
{

    private:
        char* _arr = (char*)malloc(0);
        size_t length;
        size_t cap;

    public:
        Fstr(char* _pl_arr) : Empty(_pl_arr)
        {
            
        }

};

#endif