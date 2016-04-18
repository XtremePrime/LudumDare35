#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "state.h"
#include "../gfx/hud.hpp"
#include "../level/level.h"
#include "../entities/player.h"
#include "../level/resource_tile.hpp"
#include "../level/village.h"
#include <vector>
#include <string>
#include <sstream>
#include "../util/sound.hpp"
#include "SFML/Audio.hpp"
#include "gameoverstate.h"

class GameState : public State
{
private:
	sf::Font font;
	sf::View view;
	Timer timer;
	Level level;
	const int LEVEL_WIDTH = 27, LEVEL_HEIGHT = 27;
	Player player;
	Hud hud;
	bool paused = false;
	//- Menu
	bool in_menu = false;
	Village* cur_village;
	int option = 0;
	sf::Texture menu_texture;
	sf::Sprite menu_sprite;
	//- Audio stuff
	sf::Music music;
	Sound action_sound, mine_sound, shift_sound;

protected:
	static GameState* _instance;
	GameState(){}
public:
	static GameState* instance();
    ~GameState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // GAMESTATE_H
