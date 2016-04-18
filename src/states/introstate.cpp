#include "introstate.h"

IntroState* IntroState::_instance;
IntroState* IntroState::instance(){
	if(_instance == NULL)
		_instance = new IntroState();
	return _instance;
}

void IntroState::init(Game* game)
{

}

void IntroState::cleanup()
{

}

void IntroState::handle_events(Game* game, sf::Event event)
{

}

void IntroState::update(Game* game, sf::Time deltaTime)
{

}

void IntroState::render(Game* game)
{

}

void IntroState::pause()
{

}
void IntroState::resume()
{

}
