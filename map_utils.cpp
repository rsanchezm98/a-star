#include "map_utils.hpp"

namespace map_utils
{
    std::vector<std::string> readMap(const std::string& filename)
    {
        std::ifstream source;
        source.open(filename);
        std::vector<std::string> map;
        std::string line;
        while (std::getline(source, line))
        {
            map.push_back(line);
        }
        return map;
    }
} // end map_utils namespace