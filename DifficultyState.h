#pragma once
#include "SFML Game engine/States/GameState.h"
#include "Enums.h"

class DifficultyState : public GameState{
	public:	
		DifficultyState(const sf::Vector2u &windowSize, StateManager &manager);
		void drawState(sf::RenderWindow &window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) override;
	private:
		sf::Text title, beginner, intermediate, expert, goodLuck;
};

