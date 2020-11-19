#include "DifficultyState.h"
#include "PongGameState.h"
#include "SFML Game engine/Asset Manager/AssetManager.h"

DifficultyState::DifficultyState(const sf::Vector2u &windowSize, StateManager &manager) : GameState(windowSize), 
title("Choose your difficulty:", AssetManager::get().getDefaultFont(Fonts::ARCADE_N)),
beginner("-beginner", AssetManager::get().getDefaultFont(Fonts::ARCADE_N)),
intermediate("-intermediate", AssetManager::get().getDefaultFont(Fonts::ARCADE_N)),
expert("-expert:", AssetManager::get().getDefaultFont(Fonts::ARCADE_N)),
goodLuck("good luck!", AssetManager::get().getDefaultFont(Fonts::ARCADE_N))
{
	title.setPosition(windowSize.x / 2.f - getHalfSize(title).x, 0.f);
	beginner.setPosition(windowSize.x / 2.f - getHalfSize(beginner).x, windowSize.y * 0.3);
	intermediate.setPosition(windowSize.x / 2.f - getHalfSize(intermediate).x, windowSize.y * 0.4);
	expert.setPosition(windowSize.x / 2.f - getHalfSize(expert).x, windowSize.y * 0.5);
	goodLuck.setPosition(windowSize.x / 2.f - getHalfSize(goodLuck).x, windowSize.y - getSize(goodLuck).y * 2.f);
}

void DifficultyState::drawState(sf::RenderWindow &window){
	window.draw(title);
	window.draw(beginner);
	window.draw(intermediate);
	window.draw(expert);
	window.draw(goodLuck);
}

void DifficultyState::update(float deltaTime){

}

void DifficultyState::pause(){

}

void DifficultyState::unpause(){

}

void DifficultyState::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime){
	if (isEntityClicked(beginner, window))
		manager.changeState(std::make_unique<PongGameState>(window.getSize(), manager, GameMode::ONE_PLAYER, Difficulty::BEGINNGER));
	else if (isEntityClicked(intermediate, window))
		manager.changeState(std::make_unique<PongGameState>(window.getSize(), manager, GameMode::ONE_PLAYER, Difficulty::INTERMEDIATE));
	else if (isEntityClicked(expert, window))
		manager.changeState(std::make_unique<PongGameState>(window.getSize(), manager, GameMode::ONE_PLAYER, Difficulty::EXPERT));
}
