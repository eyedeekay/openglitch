#include "wall.h"
wall::wall(type wtype, const texture_manager& textures) : wall_type(wtype),
            sprite(textures.get(textures::walls), sf::IntRect(0,0,10,10)),
            entity(1)
{
    sf::FloatRect bounds = 	sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	sprite.setScale(0.5f, 0.5f);
}
void wall::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (draw_this)
    {
        target.draw(sprite, states);
    }
}
unsigned int wall::get_category() const
{
    switch (wall_type)
    {
        case wall1:
            return cmd_category::walls;
        default:
            //lmao
            assert(false);
    }
}
void wall::update_current(sf::Time delta, command_queue& cmds)
{
    //set_velocity(0.f, 0.f);
    draw_this = true;
}
sf::FloatRect wall::getBoundingRect() const
{
    sf::FloatRect to_return(getWorldTransform().transformRect(sprite.getGlobalBounds()));
    //to_return.left = getPosition().x;
    //to_return.top = getPosition().y;
    //to_return.width = sprite.getTexture()->getSize().x;
    //to_return.height = sprite.getTexture()->getSize().y;
    //to_return.left -= 1;
    //to_return.top -= 1;
    //to_return.width += 2;
    //to_return.height += 2;
    return to_return;
}
wall::~wall()
{
    //dtor
}
const sf::Sprite& wall::get_sprite() const
{
    return sprite;
}
