
#include "TitleState.h"
#include "SFML Game engine/Asset Manager/AssetManager.h"
#include "Settings.h"
#include "InstructionState.h"
#include <iostream>

TitleState::TitleState(const sf::Vector2u &windowSize, StateManager &manager) : GameState(windowSize),
font(AssetManager::get().getDefaultFont(Fonts::ARCADE_N)),
title("PONG", font, 100), onePlayer(sf::Text("1 player", font, FONT_SIZE), true), quit(sf::Text("quit", font, FONT_SIZE), true),
twoPlayer(sf::Text("2 player", font, FONT_SIZE), true), online(sf::Text("online", font, FONT_SIZE), true),
highScores(sf::Text("high scores", font, FONT_SIZE), true), settings(sf::Text("settings", font, FONT_SIZE), true)
{
	//title.setOrigin(getCenterPosition(title));
	onePlayer.setTextColor(sf::Color::Black);
	twoPlayer.setTextColor(sf::Color::Black);
	online.setTextColor(sf::Color::Black);
	highScores.setTextColor(sf::Color::Black);
	settings.setTextColor(sf::Color::Black);
	quit.setTextColor(sf::Color::Black);

	onePlayer.setColorPack(dm::ColorPack( sf::Color::White, sf::Color(150, 150, 150), sf::Color(50, 50, 50)));
	twoPlayer.setColorPack(dm::ColorPack( sf::Color::White, sf::Color(150, 150, 150), sf::Color(50, 50, 50)));
	online.setColorPack(dm::ColorPack(    sf::Color::White, sf::Color(150, 150, 150), sf::Color(50, 50, 50)));
	highScores.setColorPack(dm::ColorPack(sf::Color::White, sf::Color(150, 150, 150), sf::Color(50, 50, 50)));
	settings.setColorPack(dm::ColorPack(  sf::Color::White, sf::Color(150, 150, 150), sf::Color(50, 50, 50)));
	quit.setColorPack(dm::ColorPack(      sf::Color::White, sf::Color(150, 150, 150), sf::Color(50, 50, 50)));

	onePlayer.setOnclickEvent([&]() {
		manager.pushState(
			std::make_unique<InstructionState>(WINDOW_SIZE, manager, GameMode::ONE_PLAYER)
		);
	});
	twoPlayer.setOnclickEvent([&]() { 
		manager.pushState(
			std::make_unique<InstructionState>(WINDOW_SIZE, manager, GameMode::TWO_PLAYER)
		);
	});

	online.setOnclickEvent([]() { std::cout << "online\n"; });
	highScores.setOnclickEvent([]() { std::cout << "high scores\n"; });
	quit.setOnclickEvent([&]() { manager.quitGame(); });
	settings.setOnclickEvent([&]() {
		manager.pushState(
			std::make_unique<Settings>(WINDOW_SIZE, manager)
		); 
	});
	

	auto getXPosition = [&](const sf::RectangleShape &body) { return windowSize.x / 2.f - body.getSize().x / 2.f; };
	float effectiveHeight = windowSize.y - getBottomEdge(title);
	float combinedHeight = onePlayer.getButtonSize().y * 6;
	const int SPACING = (effectiveHeight - combinedHeight) / 6.f;

	onePlayer.setPosition({ getXPosition(onePlayer.getButtonBody()), getBottomEdge(title)                     + SPACING });
	twoPlayer.setPosition({ getXPosition(twoPlayer.getButtonBody()), getBottomEdge(onePlayer.getButtonBody()) + SPACING});
	online.setPosition({ getXPosition(online.getButtonBody()), getBottomEdge(twoPlayer.getButtonBody())       + SPACING });
	highScores.setPosition({ getXPosition(highScores.getButtonBody()), getBottomEdge(online.getButtonBody())  + SPACING });
	settings.setPosition({ getXPosition(settings.getButtonBody()), getBottomEdge(highScores.getButtonBody())  + SPACING });
	quit.setPosition({ getXPosition(quit.getButtonBody()), getBottomEdge(settings.getButtonBody())            + SPACING });
	title.setPosition(windowSize.x / 2.f - getHalfSize(title).x, 0.f);
}

void TitleState::drawState(sf::RenderWindow &window){
	window.draw(title);
	onePlayer.drawButton(window);
	twoPlayer.drawButton(window);
	online.drawButton(window);
	highScores.drawButton(window);
	settings.drawButton(window);
	quit.drawButton(window);
}

void TitleState::update(float deltaTime){
	if (clock.getElapsedTime().asSeconds() >= 10.f) {
		std::cout << "switching to demo state!\n";
		//push demo state
		clock.restart();
	}
}

void TitleState::pause(){

}

void TitleState::unpause(){

}

void TitleState::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime){
	onePlayer.handleOnClickEvent(e, window);
	twoPlayer.handleOnClickEvent(e, window);
	online.handleOnClickEvent(e, window);
	settings.handleOnClickEvent(e, window);
	highScores.handleOnClickEvent(e, window);
	quit.handleOnClickEvent(e, window);
}
