#include "DemoState.h"
#include "SFML Game engine/States/StateManager.h"

DemoState::DemoState(const sf::Vector2u &windowSize, StateManager &manager) : GameState(windowSize, manager){

}

void DemoState::drawState(sf::RenderWindow &window){

}

void DemoState::update(float deltaTime){

}

void DemoState::pause(){

}

void DemoState::unpause(){

}

void DemoState::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window){

}