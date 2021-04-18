#ifndef MAP_UTILS_HPP
#define MAP_UTILS_HPP

#include <fstream> // read file options
#include <vector>
#include <string>
#include <iostream>


namespace map_utils
{
    enum class status {Init, Goal, Empty, Obstacle};

    std::vector<std::vector<status>> readMap(const std::string& filename);
    std::vector<status> stringToStatus(std::string& line);
    void displayMap(const std::vector<std::vector<status>>& map);
    std::string statusToString(const status& current_state);

}


#endif // MAP_UTILS_HPP