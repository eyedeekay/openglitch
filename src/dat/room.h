#ifndef ROOM_H
#define ROOM_H
#include <SFML/System.hpp>
#include <vector>
#include <fstream>
#include <iostream>
class room
{
	public:
		room(sf::Vector2f start_pos, sf::Vector2f end_pos, int id);
		void add_pickup(int pickup_type);
		void add_pickup(int pickup_type, sf::Vector2f position);
		void add_monster(int monster_type);
		void add_monster(int monster_type, sf::Vector2f position);
		const int room_id;
		void write_to_files(std::ofstream& wall_file,
							std::ofstream& pickup_file,
							std::ofstream& monster_file);
		struct monster_data
		{
			int type;
			sf::Vector2f position;
		};
		struct pickup_data
		{
			int type;
			sf::Vector2f position;
		};
		~room();
	private:
		
		std::vector<monster_data> monsters;
		std::vector<pickup_data> pickups;
		sf::Vector2f start, end;
		std::mt19937 generator;
};


#endif
