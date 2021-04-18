#ifndef A_STAR_HPP
#define A_STAR_HPP

#include "map_utils.hpp"

namespace a_star
{
    std::vector<std::vector<map_utils::status>> searchPath(
        const std::vector<std::vector<map_utils::status>>& map);
        
} // end a_star namespace

#endif // A_STAR_HPP