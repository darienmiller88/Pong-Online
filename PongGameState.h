#pragma once
#include "SFML Game engine/States/GameState.h"
#include "Paddle.h"

class PongGameState : GameState {
	public:
		PongGameState(const sf::Vector2u &windowSize, StateManager &manager);
		void drawState(sf::RenderWindow &window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) override;
	private:
		//Paddle left, right;
};

