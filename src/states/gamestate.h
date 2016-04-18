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

class GameState : public State
{
private:
	sf::Font font;
	sf::View view;
	Timer timer;
	Level level;
	Player player;
	Hud hud;
	// std::map<std::string, sf::Keyboard::Key> keys;
	const int LEVEL_WIDTH = 32, LEVEL_HEIGHT = 32;
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
