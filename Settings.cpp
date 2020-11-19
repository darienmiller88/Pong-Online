#include "Settings.h"
#include "SFML Game engine/States/StateManager.h"
#include "SFML Game engine/Asset Manager/AssetManager.h"
#include <iostream>

Settings::Settings(const sf::Vector2u &windowSize, StateManager &manager) : GameState(windowSize),
font(AssetManager::get().getDefaultFont(Fonts::ARCADE_N)), title("settings", font, 70),
backButton(sf::Text("back", font, 20), true), applyButton(sf::Text("apply", font, 20), true), 
keyBox({ 30.f, 30.f }, { windowSize.x / 2.f, windowSize.y / 2.f }, font, ""), playerOne("player one", font, 20),
playerTwo("player two", font, 20), moveUp("move up", font, 15), moveDown("move down", font, 15)
{
	title.setOrigin(getCenterPosition(title));
	playerOne.setOrigin(getCenterPosition(playerOne));
	playerTwo.setOrigin(getCenterPosition(playerTwo));
	moveUp.setOrigin(getCenterPosition(moveUp));
	moveDown.setOrigin(getCenterPosition(moveDown));

	playerOne.setPosition(windowSize.x / 4.f + 40.f, windowSize.y / 4.f);
	playerTwo.setPosition((windowSize.x + windowSize.x / 2.f) / 2.f - 40.f, windowSize.y / 4.f); 
	moveUp.setPosition(getHalfSize(moveUp).x, getBottomEdge(playerOne) * 1.3f);
	moveDown.setPosition(getHalfSize(moveDown).x, getBottomEdge(moveUp) * 1.3f);
	title.setPosition(windowSize.x / 2.f, getSize(title).y);
	
	keyBox.setCharacterLimit(1);
 	backButton.setPosition({ 0.f, windowSize.y - backButton.getButtonSize().y });
	backButton.setOnclickEvent([&]() { manager.popState(); });
	backButton.setColorPack(dm::ColorPack(sf::Color::White, sf::Color(150, 150, 150), sf::Color(50, 50, 50)));
	backButton.setTextColor(sf::Color::Black);
}

void Settings::drawState(sf::RenderWindow &window) {
	window.draw(title);
	window.draw(playerOne);
	window.draw(playerTwo);
	window.draw(moveUp);
	window.draw(moveDown);
	backButton.drawButton(window);
	keyBox.drawTextBox(window);
}

void Settings::update(float deltaTime) {

}

void Settings::pause() {

}

void Settings::unpause() {

}

void Settings::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) {
	keyBox.eventHandler(window, e);
	
	//This button will change states once it is clicked. When changing states, every member of this class will be 
	//erased due to the state getting removed. Any attempt to call or reference another variable after this will
	//result in a program crash due to the variable not existing at this point. 
	backButton.handleOnClickEvent(e, window);
}