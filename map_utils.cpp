#include "map_utils.hpp"

namespace map_utils
{
    std::vector<std::vector<status>> readMap(const std::string& filename)
    {
        std::cout << "filename: " << filename << std::endl;
        std::ifstream source;
        source.open(filename);
        std::vector<std::vector<status>> map;
        std::string line;
        
        while (std::getline(source, line))
        {   
            std::vector<status> line_status = stringToStatus(line);
            map.push_back(line_status);
        }
        return map;
    }


    std::vector<status> stringToStatus(std::string& line)
    {
        std::vector<status> line_status;

        for(unsigned i = 0; i < line.size(); i++)
        {
            if(line[i] == 'I')
            {
                // INIT
                line_status.push_back(status::Init);
            }

            if(line[i] == 'G')
            {
                // GOAL
                line_status.push_back(status::Goal);
            }

            if(line[i] == ' ')
            {
                // EMPTY
                line_status.push_back(status::Empty);
            }

            if(line[i] == '#')
            {
                // OBSTACLE
                line_status.push_back(status::Obstacle);
            }
        }

        return line_status;
    }


    void displayMap(const std::vector<std::vector<status>>& map)
    {
        for(unsigned i = 0; i < map.size(); i++)
        {
            for(unsigned j = 0; j < map[i].size(); j++)
            {
                std::cout << statusToString(map[i][j]);
            }
            std::cout << std::endl;
        }
    }

    std::string statusToString(const status& current_state)
    {
        switch (current_state)
        {
        case status::Empty:
            return " ";
        
        case status::Obstacle:
            return "#";

        case status::Init:
            return "I";

        case status::Goal:
            return "G";
        }
    }

} // end map_utils namespace