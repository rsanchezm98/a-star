#include <iostream>
#include "map_utils.hpp"
#include "a_star.hpp"

int main()
{
    /* Goal map */
    std::string filename("../maps/map_3.txt");
    std::vector<std::vector<map_utils::status>> map = map_utils::readMap(filename);
    std::cout << "[main_info]: Initial map --> " << std::endl;
    map_utils::displayMap(map);

    /* Solution map */
    std::pair<std::vector<std::vector<map_utils::status>>, std::vector<std::vector<int>>> solution = 
        a_star::searchPath(map);
    std::cout << "[main_info]: Solution map --> " << std::endl;
    map_utils::displayMap(solution.first);
    map_utils::printPath(solution.second);

    return 0;
}