#include "PauseState.h"

PauseState::PauseState(const sf::Vector2u &windowSize, StateManager &manager, const sf::Keyboard::Key &keyToPause) : 
GameState(windowSize), keyToPause(keyToPause){

}

void PauseState::drawState(sf::RenderWindow &window){

}

void PauseState::update(float deltaTime){

}

void PauseState::pause(){

}

void PauseState::unpause(){

}

void PauseState::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime){

}
