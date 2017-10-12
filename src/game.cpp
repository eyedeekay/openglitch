#include "../include/game.h"

game::game(sf::ContextSettings settings) :
                gwindow(sf::VideoMode(1366, 768), "openglitch", sf::Style::None, settings),
                game_world(gwindow),
                the_player()
{
    ispaused = false;
    tick_clock.restart();
    dbg_clock.restart();
	//set some window preferences
	gwindow.setVerticalSyncEnabled(VSYNC);
	if (LIMIT_FPS == true) gwindow.setFramerateLimit(static_cast<unsigned int>(FPS));

	//set some values
	time_per_frame = sf::seconds(1.f/FPS);
	turn_no = 0;
    sf::Text* t(new sf::Text);
    fps_text = t;
	fps_font.loadFromFile("src/pixel.ttf");
    fps_text->setFont(fps_font);
    fps_text->setCharacterSize(25);
    fps_text->setColor(sf::Color::Yellow);
    fps_text->setPosition(0.f, 0.f);
	//print some console information
	std::cout << "Time spent initializing = " << dbg_clock.restart().asMicroseconds() << " µs\n";
	std::cout << "Successfully initialized game\n" << "FPS limited(soft): " <<
		LIMIT_FPS << std::endl << "FPS limit: " << FPS << std::endl;
	std::cout << "Vsync = " << VSYNC << std::endl;
	std::cout << "Anti-aliasing level: " << AA_LEVEL << "x\n\nRunning game...\n\n";
}
void game::run()
{
	sf::Time delta = sf::seconds(1.f/FPS);
	sf::Time accumulator = sf::Time::Zero;
	tick_clock.restart();
	fps_clock.restart();
	ups_clock.restart();
	while (gwindow.isOpen())
	{
        if (turn_no % (static_cast<int>(FPS)/6) == 0)
            fps_text->setString("fps:\t" + std::to_string(10000000.f/fps_clock.restart().asMicroseconds()).substr(0, 5));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && turn_no % (static_cast<int>(FPS)/6) == 0)
        {
            fps_text->setString(fps_text->getString() + "\nleft:\t" + (std::to_string(dbg_clock.restart().asMicroseconds())));
        }

        process_events();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && turn_no % (static_cast<int>(FPS)/6) == 0)
        {
            fps_text->setString(fps_text->getString() + "\nevent:\t" + (std::to_string(dbg_clock.restart().asMicroseconds())));
        }

		sf::Vector2f pos;

		if (!ispaused)
		{
            while (accumulator > delta)
            {
                accumulator -= delta;
                update(delta);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && turn_no % (static_cast<int>(FPS)/6) == 0)
                {
                    fps_text->setString(fps_text->getString() + "\nupdate:\t" + (std::to_string(dbg_clock.restart().asMicroseconds())));
                    fps_text->setString(fps_text->getString() + "\nups:\t" + (std::to_string(10000000.f/ups_clock.restart().asMicroseconds()).substr(0, 5)));
                }
            }
        }

		render();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && turn_no % (static_cast<int>(FPS)/6) == 0)
        {
            fps_text->setString(fps_text->getString() + "\nrender:\t" + (std::to_string(dbg_clock.restart().asMicroseconds())));
        }



        accumulator += tick_clock.restart();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && turn_no % (static_cast<int>(FPS)/6) == 0)
        {
            fps_text->setString(fps_text->getString() + "\n(" + std::to_string(game_world.get_cursor()->getPosition().x).substr(0,6)+
               ", " + std::to_string(game_world.get_cursor()->getPosition().y).substr(0,6) + ")");
        }

		turn_no++;
	}
}
void game::process_events()
{
    command_queue& cmds = game_world.get_cmd_queue();

	sf::Event event;
	while (gwindow.pollEvent(event))
	{
        the_player.handle_event(event, cmds);
        if (event.type == sf::Event::Closed)
            gwindow.close();
        if (event.type == sf::Event::GainedFocus)
            ispaused = false;
        if (event.type == sf::Event::LostFocus)
            ispaused = true;
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            //scroll in or out
            if (event.mouseWheelScroll.delta > 0.f)
                game_world.set_zoom(.9f);
            else game_world.set_zoom(1.1f);
        }
	}
	the_player.handle_input(cmds);
}
void game::update(sf::Time delta)
{
    game_world.update(delta);
}
void game::render()
{
	gwindow.clear();
	game_world.draw();
	gwindow.setView(gwindow.getDefaultView());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) gwindow.draw(*fps_text);
	gwindow.display();
}
game::~game()
{
    delete fps_text;
}
