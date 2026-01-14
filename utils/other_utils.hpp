#ifndef other
#define other
#include "common include.hpp"
namespace utils
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