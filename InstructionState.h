#pragma once
#include "SFML Game engine/States/GameState.h"
#include "Enums.h"

class InstructionState : public GameState{		
	public:
		InstructionState(const sf::Vector2u &windowSize, StateManager &manager, GameMode mode);
		void drawState(sf::RenderWindow &window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) override;
	private:
		sf::Text titleOnePlayer, titleTwoPlayer, onePlayerInstructions, twoPlayerInstructions, continueText, spaceToContinue;
		GameMode mode;
};

