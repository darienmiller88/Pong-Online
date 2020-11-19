#pragma once
#include <SFML/Graphics.hpp>
#include "SFML Game engine/States/GameState.h"
#include "SFML Game engine/GUI/RectangularButton.h"

class TitleState : public GameState{
	public:
		TitleState(const sf::Vector2u &windowSize, StateManager &manager);
		void drawState(sf::RenderWindow &window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) override;
	private:
		const int FONT_SIZE = 20;
		sf::Text title;
		sf::Font font;
		sf::Clock clock;
		RectangularButton onePlayer, twoPlayer, online, highScores, settings, quit;
};