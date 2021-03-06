#ifndef MAP_UTILS_HPP
#define MAP_UTILS_HPP

#include <fstream> // read file options
#include <vector>
#include <string>
#include <iostream>


namespace map_utils
{
    enum class status {Init, Goal, Empty, Obstacle, Path, Closed, Solution};

    std::vector<std::vector<status>> readMap(const std::string& filename);

    std::vector<status> stringToStatus(std::string& line);

    void displayMap(const std::vector<std::vector<status>>& map);

    std::string statusToString(const status& current_state);
    
    std::vector<int> getCoordinates(const std::vector<std::vector<status>>& map, const status& state);

    void printPath(std::vector<std::vector<int>>& path);

}


#endif // MAP_UTILS_HPP