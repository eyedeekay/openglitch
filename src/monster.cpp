#include "../include/monster.h"

//this function is declared in the global scope of monster.cpp and
//not shown in the class interface
textures::ID to_texture_ID(monster::type Type)
{
    //to do: abstract this to allow loading from a file
	switch (Type)
	{
		case monster::small_mutant:
			return textures::small_mutant;
		case monster::large_mutant:
			return textures::large_mutant;
	}
}
//this is a little confusing. the first 'type' refers to the type of variable
//to pass in to the constructor, while the second 'type' refers to the member variable
//to initialize, in this case it get initialized to the same type as the
//monster type passed into the constructor.
monster::monster(monster::type mtype, const texture_manager& textures) :
				 monster_type(mtype), sprite(textures.get(to_texture_ID(monster_type)))
{
	//a note, we could have avoided that confusing initializer statement
	//a bit by using sf::Sprite::setTexture() in this block instead.

	//set the sprites origin to the center of the local bounds of its bounding rectangle.
	//aka move its reference point from the top left corner to the center of the sprite
	sf::FloatRect bounds = 	sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
void monster::draw_current(sf::RenderTarget& target,
								  sf::RenderStates  states) const
{
	//the result of all this inheritence, oop, recursion, and sfml usage is that this is a super simple call
	target.draw(sprite, states);
}