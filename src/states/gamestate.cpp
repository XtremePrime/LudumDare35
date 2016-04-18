#include "gamestate.h"

GameState* GameState::_instance;
GameState* GameState::instance(){
	if(_instance == NULL)
		_instance = new GameState();
	return _instance;
}

void GameState::init(Game* game)
{
	//- Init everything
	font.loadFromFile("res/font/PressStart2P.ttf");
	std::cout << "Font loaded!\n";
	hud.init();
	std::cout << "Timer loaded!\n";
	level.init(LEVEL_WIDTH, LEVEL_HEIGHT);
	std::cout << "Level loaded!\n";
	player.init(sf::Vector2f(0+16, 0+16), 64, 64);
	std::cout << "Player loaded!\n";
	//- Init keys
	/*keys["up"] = sf::Keyboard::W;
	keys["down"] = sf::Keyboard::S;
	keys["left"] = sf::Keyboard::A;
	keys["right"] = sf::Keyboard::D;
	keys["action"] = sf::Keyboard::Space;*/
	//- Set view
	view.reset(sf::FloatRect(0, 0, 860, 640));
}

void GameState::cleanup()
{

}

void GameState::handle_events(Game* game, sf::Event event)
{
	player.handle_events(event);
	if(player.action && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		//- Is the ore a resource?
		if(level.get_tile(player.get_pos().x, player.get_pos().y, 64).is_resource)
		{
			player.get_inventory().add_iron(1);
			std::cout << "Iron: " << player.get_inventory().get_iron() << "\nMagiBerries: " << player.get_inventory().get_magiberries() << "\n";
		}

		//- Village check
		for(int i = 0; i < level.get_villages().size(); ++i)
		{
			if(level.get_villages()[i]->get_bbox().intersects(player.get_bbox()))
			{
				std::cout << "Village!\n";
				break;
			}
		}
	}

	//- Handle player movement
	/*sf::FloatRect new_pos;
	#define press(key) sf::Keyboard::isKeyPressed(key)
	if(press(keys["up"]))
	{
		// if ((**i).canMove(0,-1,_world))
		// 		(**i)._sprite.Move(0,-32);
		new_pos = sf::FloatRect(player.get_pos().x+player.vx, player.move().y, w, h);
		if(player)
	}
	#undef press*/
}

void GameState::update(Game* game, sf::Time deltaTime)
{
	//- Level
	level.update(deltaTime);
	//- Player
	player.update(deltaTime);
	player.move2(deltaTime);
	//- Timer & Rest
	hud.update(deltaTime, this->player, this->view);
}

void GameState::render(Game* game)
{

	level.render( *(game->get_window()), player.get_pos() );

	sf::Vector2f camera_pos;
	camera_pos.x = player.get_pos().x + 10 - (860/2);
	camera_pos.y = player.get_pos().y + 10 - (640/2);
	if(camera_pos.x < 0)
		camera_pos.x = 0;
	if(camera_pos.y < 0)
		camera_pos.y = 0;

	if(camera_pos.x > (LEVEL_WIDTH*32)/2 - (860/2))
		camera_pos.x = (LEVEL_WIDTH*32)/2 - (860/2);
	if(camera_pos.y > (LEVEL_HEIGHT*32)/2 - (640/2))
		camera_pos.y = (LEVEL_HEIGHT*32)/2 - (640/2);

	view.reset(sf::FloatRect(camera_pos.x, camera_pos.y, 860, 640));
	// view.zoom(0.5f);
	// std::cout << camera_pos.x << "," << camera_pos.y << " | " << player.get_pos().x << "," << player.get_pos().y << "\n";


	game->get_window()->setView(view);




	player.render( *(game->get_window()) );
	hud.render( *(game->get_window()), player.get_pos(), this->view );
}

void GameState::pause()
{

}
void GameState::resume()
{

}
