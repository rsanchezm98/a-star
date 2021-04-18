#ifndef A_STAR_HPP
#define A_STAR_HPP

#include "map_utils.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

namespace a_star
{
    std::vector<std::vector<map_utils::status>> searchPath(
        std::vector<std::vector<map_utils::status>> map);

    struct a_star_node
    {
        int horizontal;
        int vertical;
        int g;
        int h;
    };

    int computeHeuristic(const std::vector<int>& goal, const std::vector<int>& node_coordinates);

    void sortOpen(std::vector<a_star_node>& open);

    void addToOpenList(const a_star_node& node, 
                        std::vector<std::vector<map_utils::status>>& map, 
                        std::vector<a_star_node>& open);
    
    bool compareRule(const a_star_node& a, const a_star_node& b);

    void goWithNeighbours(const a_star_node& current_node, std::vector<int> goalCoords, 
                        std::vector<a_star_node>& open, 
                        std::vector<std::vector<map_utils::status>>& map);
    

} // end a_star namespace

#endif // A_STAR_HPP