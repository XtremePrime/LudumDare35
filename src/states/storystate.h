#ifndef STORYSTATE_H
#define STORYSTATE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "state.h"

class StoryState : public State
{
private:
protected:
	static StoryState* _instance;
	StoryState(){}
public:
	static StoryState* instance();
    ~StoryState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();
};

#endif // STORYSTATE_H
