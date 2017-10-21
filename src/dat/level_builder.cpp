

#include <iostream>
#include <fstream>
#include <SFML/System.hpp>
#include "room.h"
const int maxX = 400;
const int maxY = 400;
void resolve_walls();
int main(int argc, char **argv)
{
	std::vector<room> rooms;
	std::ofstream wall_file;
	wall_file.open("walls.bb", std::ios::trunc);
	std::ofstream pickup_file;
	pickup_file.open("pickups.bb", std::ios::trunc);
	std::ofstream monster_file;
	monster_file.open("monsters.bb", std::ios::trunc);
	
	rooms.push_back(room(sf::Vector2f(140, 150), sf::Vector2f(190, 165), 0));
	rooms.push_back(room(sf::Vector2f(180, 180), sf::Vector2f(220, 220), 1));
	rooms.push_back(room(sf::Vector2f(190, 120), sf::Vector2f(210, 180), 2));
	rooms.push_back(room(sf::Vector2f(210, 160), sf::Vector2f(250, 170), 3));
	rooms.push_back(room(sf::Vector2f(230, 140), sf::Vector2f(240, 160), 4));
	rooms.push_back(room(sf::Vector2f(230, 120), sf::Vector2f(260, 140), 5));
	rooms.at(1).add_pickup(2);
	rooms.at(1).add_pickup(3);
	rooms.at(0).add_pickup(4);
	rooms.at(0).add_monster(0);
	rooms.at(4).add_monster(0);
	rooms.at(3).add_pickup(5);
	rooms.at(5).add_pickup(6);
	rooms.at(5).add_pickup(7);
	rooms.at(5).add_monster(0);
	
	for (room each_room : rooms)
	{
		each_room.write_to_files(wall_file, pickup_file, monster_file);
	}
	monster_file.close();
	pickup_file.close();
	wall_file.close();
	resolve_walls();
	return 0;
}
void resolve_walls()
{
	std::ifstream walls_file;
	walls_file.open("walls.bb");
	std::vector<sf::Vector2f> in, out;
	int type, x, y;
	while (walls_file >> type >> x >> y)
	{
		in.push_back(sf::Vector2f(x, y));
	}
	walls_file.close();
	
	
	for (std::vector<sf::Vector2f>::iterator check_iter = in.begin();
			check_iter != in.end();
			check_iter++)
	{
		bool unique = true;
		for (std::vector<sf::Vector2f>::iterator against_iter = ++in.begin();
				against_iter != in.end();
				against_iter++)
		{
			if (*check_iter == *against_iter && check_iter != against_iter)
			{
				unique = false;
			}
		}
		if (unique) out.push_back(*check_iter);
	}
	
	std::ofstream walls_out;
	walls_out.open("walls.bb");
	for (sf::Vector2f each : out)
	{
		walls_out << 1 << " " << each.x << " " << each.y << std::endl;
	}
	walls_out.close();
}
