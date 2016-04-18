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
	player.init(sf::Vector2f(860/2-64/2, 640/2-64/2), 64, 64);
	std::cout << "Player loaded at " << player.get_pos().x << "," << player.get_pos().y << "\n";
	//- Init keys
	/*keys["up"] = sf::Keyboard::W;
	keys["down"] = sf::Keyboard::S;
	keys["left"] = sf::Keyboard::A;
	keys["right"] = sf::Keyboard::D;
	keys["action"] = sf::Keyboard::Space;*/
	//- Set view
	view.reset(sf::FloatRect(0, 0, 860, 640));

	music.openFromFile("res/music/POL-pocket-garden-short.wav");
	action_sound.init("action.wav");
	shift_sound.init("shift.wav");
	mine_sound.init("mine.wav");
	music.setLoop(true);
	music.setVolume(25.0f);
	music.play();

	//- Menu sprite
	if(menu_texture.loadFromFile("res/tiles/menu.png"))
		std::cout << "Success!\n";
	menu_sprite.setTexture(menu_texture);
	menu_sprite.setPosition(sf::Vector2f(0, 0));
}

void GameState::cleanup()
{

}

void GameState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::LostFocus)
		pause();
	else if(event.type == sf::Event::GainedFocus)
		resume();

	if(paused) return;

	if(!in_menu)
		player.handle_events(event);

	if(in_menu)
	{
		player.erase_movement();
		bool held;
		if(event.type == sf::Event::KeyPressed)
		{
			/*if(event.key.code == sf::Keyboard::Space)
			{
			    const int BUY = 0, GIFT = 1, LEAVE = 2;
				switch(option)
				{
					case BUY:
						if(player.get_inventory().get_magiberries() > 0)
						{
							player.set_power(player.get_power() + (float)player.get_inventory().get_magiberries()/10);
							player.get_inventory().add_magiberries(player.get_inventory().get_magiberries()*-1);
						}
						in_menu = false;
						option = 0;
						return;
					break;
					case GIFT:
						if(player.get_inventory().get_iron() > 0)
						{
							std::cout << "Donated " << player.get_inventory().get_iron() << "!\n";
							cur_village->favour = (float)player.get_inventory().get_iron() / (float)10;
							player.get_inventory().add_iron(player.get_inventory().get_iron()*-1);
						}
						in_menu = false;
						option = 0;
						return;
					break;
					case LEAVE:
						in_menu = false;
						option = 0;
						return;
					break;
					default:
					break;
				}
			}else*/ if(event.key.code == sf::Keyboard::W){
				if(option > 0)
					option--;
			}else if(event.key.code == sf::Keyboard::S){
				if(option < 2)
					option++;
			}else if(event.key.code == sf::Keyboard::Num1){
				if(player.get_inventory().get_magiberries() > 0)
				{
					player.set_power(player.get_power() + (float)player.get_inventory().get_magiberries()/10);
					player.get_inventory().add_magiberries(player.get_inventory().get_magiberries()*-1);
				}
				in_menu = false;
				option = 0;
				return;
			}else if(event.key.code == sf::Keyboard::Num2){
				if(player.get_inventory().get_iron() > 0)
				{
					std::cout << "Donated " << player.get_inventory().get_iron() << "!\n";
					cur_village->favour = cur_village->favour += (float)player.get_inventory().get_iron() / (float)5;
					player.get_inventory().add_iron(player.get_inventory().get_iron()*-1);
				}
				in_menu = false;
				option = 0;
				return;
			}else if(event.key.code == sf::Keyboard::Num3){
				in_menu = false;
				option = 0;
				return;
			}
			std::cout << "Menu: " << in_menu << " | O: " << option << " | FAV: " << cur_village->favour << " | POW: " << player.get_power() << "\n";
		}
	}

	if(!in_menu && player.action && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		//- Is the ore a resource?
		if(level.get_tile(player.get_pos().x, player.get_pos().y, 27).is_resource)
		{
			const int IR = 2, MB = 1;
			switch(level.get_tile(player.get_pos().x, player.get_pos().y, 27).resource_code)
			{
				case IR:
				{
					if(player.get_shape() == Shape::IRON)
					{
						player.get_inventory().add_iron(1);
						std::cout << "Iron: " << player.get_inventory().get_iron() << "\nMagiBerries: " << player.get_inventory().get_magiberries() << "\n";
						action_sound.play();
					}
					else
					{
						std::cout << "[GS]: Not shapeshifter!\n";
					}
				}
				break;
				case MB:
					player.get_inventory().add_magiberries(1);
					std::cout << "Iron: " << player.get_inventory().get_iron() << "\nMagiBerries: " << player.get_inventory().get_magiberries() << "\n";
					mine_sound.play();
				break;
				default:
				break;
			}

		}

		//- Village check
		for(int i = 0; i < level.get_villages().size(); ++i)
		{
			if(level.get_villages()[i]->get_bbox().intersects(player.get_bbox()))
			{
				this->cur_village = level.get_villages()[i];
				in_menu = true;
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
	if(paused) return;

	if(level.get_villages()[0]->favour >= 100.0f)
		game->change_state(GameOverState::instance());

	//- Level
	level.update(deltaTime);
	//- Player
	if(!in_menu){
		player.update(deltaTime);
		player.move2(deltaTime);
	}
	//- Timer & Rest
	hud.update(deltaTime, this->player, *level.get_villages()[0]);
}

void GameState::render(Game* game)
{

	level.render( *(game->get_window()), player.get_pos());

	/*sf::Vector2f camera_pos;
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


	game->get_window()->setView(view);*/



	hud.render( *(game->get_window()), player.get_pos(), this->view );
	player.render( *(game->get_window()) );

	if(in_menu)
		game->get_window()->draw(menu_sprite);
}

void GameState::pause()
{
	paused = true;
}

void GameState::resume()
{
	paused = false;
}
