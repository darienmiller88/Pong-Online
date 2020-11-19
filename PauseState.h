#pragma once
#include "SFML Game engine/States/GameState.h"

class PauseState : public GameState{
	public:
		PauseState(const sf::Vector2u &windowSize, StateManager &manager, const sf::Keyboard::Key &keyToPause);
		void drawState(sf::RenderWindow &window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) override;
	private:
		sf::Keyboard::Key keyToPause; 
};

