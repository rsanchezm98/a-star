#include "a_star.hpp"

namespace a_star
{
    std::pair<std::vector<std::vector<map_utils::status>>, std::vector<std::vector<int>>> searchPath(
        std::vector<std::vector<map_utils::status>> map)
    {
        auto initTime = std::chrono::high_resolution_clock::now();

        std::vector<int> initCoords = map_utils::getCoordinates(map, map_utils::status::Init);
        std::vector<int> goalCoords = map_utils::getCoordinates(map, map_utils::status::Goal);

        std::pair<std::vector<std::vector<map_utils::status>>, std::vector<std::vector<int>>> solution;

        std::vector<a_star_node> open;
        std::vector<a_star_node> evaluated_nodes;

        // first node
        a_star_node init_node;
        init_node.horizontal = initCoords[1];
        init_node.vertical = initCoords[0];
        init_node.g = 0; // distance from init to the node
        init_node.h = computeHeuristic(goalCoords, initCoords);

        addToOpenList(init_node, map, open);

        while(open.size() > 0)
        {
            // first we need to sort the open vector according to f = g + h. The lower in the end
            sortOpen(open);

            // get the last element
            a_star_node current_node = open.back(); 
            evaluated_nodes.push_back(current_node);

            // remove the current node
            open.pop_back(); 

            // update the map status
            map[current_node.vertical][current_node.horizontal] = map_utils::status::Path;

            // check if we reached the goal
            if(current_node.horizontal == goalCoords[1] && current_node.vertical == goalCoords[0])
            {
                auto finTime = std::chrono::high_resolution_clock::now();
                auto duration_ = std::chrono::duration_cast<std::chrono::nanoseconds>(finTime - initTime);

                
                std::vector<std::vector<int>> path = buildPath(map, evaluated_nodes, goalCoords);
                map[initCoords[0]][initCoords[1]] = map_utils::status::Init;
                map[goalCoords[0]][goalCoords[1]] = map_utils::status::Goal;

                std::cout << "[a_star_info]: Found the shortest path!" << std::endl;
                std::cout << "[a_star_info]: Elapsed time: " << duration_.count()*1.0/1e6 << " ms" << std::endl;
                 
                solution.first = map;
                solution.second = path;
                return  solution; // return std::pair
            }

            // check the neighbours and compute its components so as to add them to open list
            goWithNeighbours(current_node, goalCoords, open, map);
            
        }

        // if we get here it means that no solution was found
        std::cout << "[a_star_info]: No solution was found!" << std::endl;

        return solution;
        
    }

    int computeHeuristic(const std::vector<int>& goal, const std::vector<int>& node_coordinates)
    {
        int heur = abs(goal[1] - node_coordinates[1]) + abs(goal[0] - node_coordinates[0]);
        return heur;
    }

    void addToOpenList(const a_star_node& node, 
                        std::vector<std::vector<map_utils::status>>& map, 
                        std::vector<a_star_node>& open)
    {
        open.push_back(node);
        map[node.vertical][node.horizontal] = map_utils::status::Closed;
    }

    void sortOpen(std::vector<a_star_node>& open)
    {
        std::sort(open.begin(), open.end(), compareRule);
    }

    bool compareRule(const a_star_node& a, const a_star_node& b)
    {
        int f_first = a.g + a.h;
        int f_second = b.g + b.h;

        return f_first > f_second;
    }

    void goWithNeighbours(a_star_node& current_node, std::vector<int> goalCoords, 
                        std::vector<a_star_node>& open, 
                        std::vector<std::vector<map_utils::status>>& map)
    {
        /* We have to check if:
           - the position is in the map
           - the position is empty or is the end
        */

        // up
        if(current_node.vertical - 1 >= 0)
        {
            if(map[current_node.vertical - 1][current_node.horizontal] == map_utils::status::Empty ||
                map[current_node.vertical - 1][current_node.horizontal] == map_utils::status::Goal)
            {
                // if we are here it means that we can add the new node to the openlist
                a_star_node up_node;
                up_node.horizontal = current_node.horizontal;
                up_node.vertical = current_node.vertical - 1;
                up_node.g = current_node.g + 1; // distance from init to the node
                std::vector<int> coords;
                coords.push_back(up_node.vertical);
                coords.push_back(up_node.horizontal);
                up_node.h = computeHeuristic(goalCoords, coords);
                up_node.parent.push_back(current_node.vertical);
                up_node.parent.push_back(current_node.horizontal);
                addToOpenList(up_node, map, open);

            }
        }

        // down
        if(current_node.vertical + 1 < map.size())
        {
            if(map[current_node.vertical + 1][current_node.horizontal] == map_utils::status::Empty ||
                map[current_node.vertical + 1][current_node.horizontal] == map_utils::status::Goal)
            {
                // if we are here it means that we can add the new node to the openlist
                a_star_node down_node;
                down_node.horizontal = current_node.horizontal;
                down_node.vertical = current_node.vertical + 1;
                down_node.g = current_node.g + 1; // distance from init to the node
                std::vector<int> coords;
                coords.push_back(down_node.vertical);
                coords.push_back(down_node.horizontal);
                down_node.h = computeHeuristic(goalCoords, coords);
                down_node.parent.push_back(current_node.vertical);
                down_node.parent.push_back(current_node.horizontal);
                addToOpenList(down_node, map, open);

            }
        }

        // left
        if(current_node.horizontal - 1 >= 0)
        {
            if(map[current_node.vertical][current_node.horizontal - 1] == map_utils::status::Empty ||
                map[current_node.vertical][current_node.horizontal - 1] == map_utils::status::Goal)
            {
                // if we are here it means that we can add the new node to the openlist
                a_star_node left_node;
                left_node.horizontal = current_node.horizontal - 1;
                left_node.vertical = current_node.vertical;
                left_node.g = current_node.g + 1; // distance from init to the node
                std::vector<int> coords;
                coords.push_back(left_node.vertical);
                coords.push_back(left_node.horizontal);
                left_node.h = computeHeuristic(goalCoords, coords);
                left_node.parent.push_back(current_node.vertical);
                left_node.parent.push_back(current_node.horizontal);
                addToOpenList(left_node, map, open);

            }
        }

        // right
        if(current_node.horizontal + 1 < map[0].size())
        {
            if(map[current_node.vertical][current_node.horizontal + 1] == map_utils::status::Empty ||
                map[current_node.vertical][current_node.horizontal + 1] == map_utils::status::Goal)
            {
                // if we are here it means that we can add the new node to the openlist
                a_star_node right_node;
                right_node.horizontal = current_node.horizontal + 1;
                right_node.vertical = current_node.vertical;
                right_node.g = current_node.g + 1; // distance from init to the node
                std::vector<int> coords;
                coords.push_back(right_node.vertical);
                coords.push_back(right_node.horizontal);
                right_node.h = computeHeuristic(goalCoords, coords);
                right_node.parent.push_back(current_node.vertical);
                right_node.parent.push_back(current_node.horizontal);
                addToOpenList(right_node, map, open);
            }
        }
    }

    std::vector<std::vector<int>> buildPath(std::vector<std::vector<map_utils::status>>& map, 
                    std::vector<a_star_node>& evaluated_nodes, std::vector<int>& goal)
    {
        auto index = getNodePosition(evaluated_nodes, goal);
        std::vector<std::vector<int>> path;
        
        while(true) // to be in the Init position
        {
            std::vector<int> current;
            auto x = evaluated_nodes[index].horizontal;
            auto y = evaluated_nodes[index].vertical;

            current.push_back(y);
            current.push_back(x);

            path.push_back(current);

            map[y][x] = map_utils::status::Solution;

            index = getNodePosition(evaluated_nodes, evaluated_nodes[index].parent);

            if(index == 0)
            {
                std::vector<int> current_;
                auto x_ = evaluated_nodes[index].horizontal;
                auto y_ = evaluated_nodes[index].vertical;

                current_.push_back(y);
                current_.push_back(x);

                path.push_back(current_);

                return path;                
            }
        }

        return path;
    }

    int getNodePosition(std::vector<a_star_node>& evaluated_nodes, std::vector<int>& pos)
    {

        for(unsigned i = 0; i < evaluated_nodes.size(); i++)
        {
            if(evaluated_nodes[i].vertical == pos[0] && evaluated_nodes[i].horizontal == pos[1])
            {
                return i;
            }
        }
    }
} // end a_star namespace