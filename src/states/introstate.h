#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "state.h"

class IntroState : public State
{
private:
protected:
	static IntroState* _instance;
	IntroState(){}
public:
	static IntroState* instance();
    ~IntroState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // INTROSTATE_H
