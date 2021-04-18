#ifndef MAP_UTILS_HPP
#define MAP_UTILS_HPP

#include <fstream> // to include read file options
#include <vector>
#include <string>


namespace map_utils
{
    std::vector<std::string> readMap(const std::string& filename);

}


#endif // MAP_UTILS_HPP