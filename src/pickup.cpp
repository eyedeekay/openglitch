#include "pickup.h"

std::vector<pickup_data> table = init_pickup_data();



pickup::pickup(pickup::type Type, const texture_manager& textures) :
            mtype(Type),
            sprite(textures.get(table[mtype].texture), table[mtype].texture_rect),
            entity(1)
{
    sf::FloatRect bounds = 	sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.scale(0.6f, 0.6f);
    draw_outline = false;
}
unsigned int pickup::get_category() const
{
    return cmd_category::pickups;
}
sf::FloatRect pickup::getBoundingRect() const
{
    sf::FloatRect to_return;
    to_return.left = getPosition().x - 1;
    to_return.top = getPosition().y - 1;
    to_return.width = sprite.getGlobalBounds().width;
    to_return.height = sprite.getGlobalBounds().height;
    return to_return;
}
void pickup::apply(monster& the_player) const
{
    table[mtype].action(the_player);
}
void pickup::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (draw_this)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        {
            sf::Vector2f v(getBoundingRect().width, getBoundingRect().height);
            sf::RectangleShape collide_rect(v);
            sf::FloatRect bounds = 	collide_rect.getLocalBounds();
            collide_rect.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            collide_rect.setPosition(getPosition());
            collide_rect.setOutlineColor(sf::Color::Black);
            collide_rect.setFillColor(sf::Color(0,0,0,0));
            collide_rect.setOutlineThickness(.5f);
            target.draw(collide_rect);
        }
        if (draw_outline)
        {
            sf::Vector2f v2(getBoundingRect().width, getBoundingRect().height);
            sf::CircleShape outline_circle(std::max((v2.x / sqrt(2)), (v2.y / sqrt(2))));
            outline_circle.setPosition(getPosition());
            outline_circle.setFillColor(sf::Color(0,0,0,0));
            outline_circle.setOutlineColor(sf::Color::White);
            outline_circle.setOutlineThickness(0.25f);
            outline_circle.setOrigin(outline_circle.getRadius(), outline_circle.getRadius());
            target.draw(outline_circle);
        }
        target.draw(sprite, states);
    }
}
pickup::~pickup()
{
    //dtor
}
void pickup::enable_outline()
{
    draw_outline = true;
}
void pickup::disable_outline()
{
    draw_outline = false;
}
void pickup::update_current(sf::Time delta, command_queue& cmds)
{
    //because draw() is const, we reset this to true here so culling can be recalculed before the next draw()
    draw_this = true;
}
