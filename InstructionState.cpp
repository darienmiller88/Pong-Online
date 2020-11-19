#include "InstructionState.h"
#include "SFML Game engine/Asset Manager/AssetManager.h"
#include "SFML Game engine/States/StateManager.h"
#include "PongGameState.h"
#include "DifficultyState.h"

InstructionState::InstructionState(const sf::Vector2u &windowSize, StateManager &manager, GameMode mode) : GameState(windowSize),
titleOnePlayer("one player instructions", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 35),

titleTwoPlayer("two player instructions", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 35),

onePlayerInstructions("Use the \"w\" and \"s\" keys to move \nthe paddle up and down. The first \nto reach 10 points wins!",
AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 20),

twoPlayerInstructions("Player 1 (left) uses the \"w\" and \"s\" \nkeys to move the paddle up and down.\n\n" 
"Player 2 (right) uses the \"k\" and \"m\" \nkeys to move the paddle up and down. \n\nThe first to reach 10 points wins!", 
AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 20),

continueText("Continue", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 40), 

spaceToContinue("press space to continue!", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 30),

mode(mode)
{
	titleOnePlayer.setPosition(windowSize.x / 2.f - getHalfSize(titleOnePlayer).x, 0.f);
	titleTwoPlayer.setPosition(windowSize.x / 2.f - getHalfSize(titleTwoPlayer).x, 0.f);
	onePlayerInstructions.setPosition(windowSize.x / 2.f - getHalfSize(onePlayerInstructions).x, windowSize.y * 0.4f);
	twoPlayerInstructions.setPosition(windowSize.x / 2.f - getHalfSize(twoPlayerInstructions).x, windowSize.y * 0.3f);
	continueText.setPosition(windowSize.x / 2.f - getHalfSize(continueText).x, windowSize.y - getSize(continueText).y * 2.f);
	spaceToContinue.setPosition(windowSize.x / 2.f - getHalfSize(spaceToContinue).x, windowSize.y - getSize(spaceToContinue).y * 2.f);
}

void InstructionState::drawState(sf::RenderWindow &window){
	if (mode == GameMode::ONE_PLAYER){
		window.draw(titleOnePlayer);
		window.draw(onePlayerInstructions);
		window.draw(continueText);
	}else{
		window.draw(titleTwoPlayer);
		window.draw(twoPlayerInstructions);
		window.draw(spaceToContinue);
	}	
}

void InstructionState::update(float deltaTime){

}

void InstructionState::pause(){

}

void InstructionState::unpause(){

}

void InstructionState::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime){
	if (isEntityClicked(continueText, window)) 
		manager.changeState(std::make_unique<DifficultyState>(WINDOW_SIZE, manager));
	else if (isKeyPressed(sf::Keyboard::Space, e) and mode == GameMode::TWO_PLAYER)
		manager.changeState(std::make_unique<PongGameState>(WINDOW_SIZE, manager, GameMode::TWO_PLAYER, Difficulty::BEGINNGER));
}
