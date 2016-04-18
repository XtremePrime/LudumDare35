#include "storystate.h"

StoryState* StoryState::_instance;
StoryState* StoryState::instance(){
	if(_instance == NULL)
		_instance = new StoryState();
	return _instance;
}

void StoryState::init(Game* game)
{

}

void StoryState::cleanup()
{

}

void StoryState::handle_events(Game* game, sf::Event event)
{

}

void StoryState::update(Game* game, sf::Time deltaTime)
{

}

void StoryState::render(Game* game)
{

}

void StoryState::pause()
{

}
void StoryState::resume()
{

}
