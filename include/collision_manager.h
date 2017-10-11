#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include "include.h"
#include "wall.h"
#include "monster.h"
#include "projectile.h"
#include "pickup.h"
#include "shadow.h"
#include "command_queue.h"
class pickup;
class collision_manager
{
    public:
        collision_manager(monster* Player);
        collision_manager();
        virtual ~collision_manager();
        void check_collisions(command_queue& cmds);
        void update_shadows(sf::Vector2f view_center);
        void add_entity(entity*, cmd_category::ID type);
        void rmv_entity(entity&, cmd_category::ID type);
        void draw_shadows(sf::RenderWindow* window);
        void init_shadows(int screenx, int screeny);
    protected:

    private:
        std::vector<wall*> walls;
        std::vector<monster*> monsters;
        monster* the_player;
        std::vector<projectile*> bullets;
        std::vector<pickup*> pickups;
        ShadowHandler shadow_manager;
    private:
        void wall_monster_collisions(command_queue& cmds);
        void wall_bullet_collisions(command_queue& cmds);
        void monster_bullet_collisions(command_queue& cmds);
        void monster_pickup_collisions(command_queue& cmds);
        void monster_monster_collisions(command_queue& cmds);
        std::vector<sf::Vector2f> get_obstacles();
};
#endif // COLLISION_MANAGER_H
