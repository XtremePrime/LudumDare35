#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "state.h"

class GameOverState : public State
{
private:
protected:
	static GameOverState* _instance;
	GameOverState(){}

	sf::Texture tx;
	sf::Sprite sprite;
public:
	static GameOverState* instance();
    ~GameOverState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // GAMEOVERSTATE_H
