#include <iostream>
#include "map_utils.hpp"
#include "a_star.hpp"

int main()
{
    /* Goal map */
    std::string filename("../maps/map_2.txt");
    std::vector<std::vector<map_utils::status>> map = map_utils::readMap(filename);
    std::cout << "Initial map: " << std::endl;
    map_utils::displayMap(map);

    /* Solution map */
    std::vector<std::vector<map_utils::status>> solution = 
        a_star::searchPath(map);
    std::cout << "Solution map: " << std::endl;
    map_utils::displayMap(solution);

    return 0;
}