#ifndef WORLD_H
#define WORLD_H

#include "include.h"
#include "texture_manager.h"
#include "resource_manager.h"
#include "scene_node.h"
#include "entity.h"
#include "monster.h"
#include "sprite_node.h"
#include "player.h"
#include "command_queue.h"
#include "cursor.h"
#include "projectile.h"
#include "pickup.h"
#include "wall.h"
#include "collision_manager.h"
#include "emitter_node.h"
#include "particle_node.h"
class world : public sf::NonCopyable
{
    public:
        explicit world(sf::RenderWindow& window);
        virtual ~world();
        void update(sf::Time delta);
        void draw();
        command_queue& get_cmd_queue();
        void set_zoom(float f);
        float get_zoom();
        class spawn_point
        {
            public:
                spawn_point(monster::type stype, float x, float y);
                monster::type stype;
                float x;
                float y;
        };
        cursor* get_cursor();
        int get_player_hp();
        monster* get_player();
        texture_manager textures;
        private:
        enum scn_layer
        {
            bg_layer,
            air_layer,
            walls_layer,
            mon_layer,
            hud_layer,
            layer_count,
        };
    private:
        void load_textures();
        void build_scene();
        void adjust_player_v();
        void rotate_player();
        void update_cursor();
        void spawn_enemies();
        void add_enemy(monster::type, float x, float y);
        void add_enemies();
        bool matches_categories(scene_node::scn_pair& colliders, cmd_category::ID type_1, cmd_category::ID type_2);
        void destroy_OOB_entities();
        void load_walls();
        void load_pickups();
        void draw_reticle_line();
    private:
         collision_manager cmanager;
         sf::RenderWindow& wwindow;
         sf::View world_view;
         resource_manager<sf::Font, fonts::ID> fonts;
         resource_manager<sf::Sound, sounds::ID> sounds;
         scene_node scene_graph;
         std::array<scene_node*, layer_count> scene_layers;
         sf::FloatRect world_bounds;
         sf::Vector2f spawn_position;
         float zoom_level;
         monster* the_player;
         cursor* the_cursor;
         command_queue world_cmd_queue;
         std::vector<spawn_point> enemy_spawn_points;
};

#endif // WORLD_H
