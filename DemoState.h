#pragma once
#include "SFML Game engine/States/GameState.h"

class DemoState : public GameState{
	public:
		DemoState(const sf::Vector2u &windowSize, StateManager &manager);
		void drawState(sf::RenderWindow &window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager& manager, const sf::Event& e, const sf::RenderWindow& window) override;
	private:

};

