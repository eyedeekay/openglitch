#include "room.h"
#include <random>
#include <chrono>
room::room(sf::Vector2f start_pos, sf::Vector2f end_pos, int id) :
	room_id(id),
	generator(time(0))
{
	int x1 = start_pos.x;
	int x2 = end_pos.x;
	int y2 = end_pos.y;
	int y1 = start_pos.y;
	if (x1 > x2) std::swap(x1, x2);
	if (y1 > y2) std::swap(y1, y2);
	start = start_pos;
	end = end_pos;
}
void room::add_pickup(int pickup_type)
{
	sf::Vector2f add_pos;
	std::uniform_int_distribution<int> xdist(start.x + 1, end.x - 1);
	std::uniform_int_distribution<int> ydist(start.y + 1, end.y - 1);
	int xpos = xdist(generator);
	int ypos = ydist(generator);
	add_pos = sf::Vector2f(xpos, ypos);
	pickup_data new_data;
	new_data.type = pickup_type;
	std::cout << add_pos.x << " " << add_pos.y << std::endl;
	new_data.position = add_pos;
	pickups.push_back(new_data);
}
void room::add_pickup(int pickup_type, sf::Vector2f position)
{
	pickup_data new_data;
	new_data.type = pickup_type;
	new_data.position = position;
	pickups.push_back(new_data);
}
void room::add_monster(int monster_type)
{
	sf::Vector2f add_pos;
	std::mt19937 generator;
	std::uniform_int_distribution<int> xdist(start.x + 1, end.x - 1);
	std::uniform_int_distribution<int> ydist(start.y + 1, end.y - 1);
	add_pos = sf::Vector2f(xdist(generator), ydist(generator));
	monster_data new_data;
	new_data.type = monster_type;
	std::cout << add_pos.x << " " << add_pos.y << std::endl;
	new_data.position = add_pos;
	monsters.push_back(new_data);
}
void room::add_monster(int monster_type, sf::Vector2f position)
{
	monster_data new_data;
	new_data.type = monster_type;
	new_data.position = position;
	monsters.push_back(new_data);
}
void room::write_to_files(std::ofstream& wall_file, std::ofstream& pickup_file, std::ofstream& monster_file)
{
	for (int x = start.x; x <= end.x; x++)
	{
		wall_file << 1 << " " <<  x * 5 << " " << start.y * 5 << std::endl;
		wall_file << 1 << " " <<  x * 5 << " " << end.y * 5 << std::endl;
	}
	for (int y = start.y; y <= end.y; y++)
	{
		wall_file << 1 << " " <<  start.x * 5 << " " << y * 5  << std::endl;
		wall_file << 1 << " " <<  end.x * 5 << " " << y * 5 << std::endl;
	}
	for (pickup_data pickup : pickups)
	{
		pickup_file << pickup.type << " " << pickup.position.x * 5 << " " << pickup.position.y * 5 << std::endl;
	}
	for (monster_data monster : monsters)
	{
		monster_file << monster.type << " " << monster.position.x * 5 << " " << monster.position.y * 5 << std::endl;
	}
}
room::~room()
{
}
