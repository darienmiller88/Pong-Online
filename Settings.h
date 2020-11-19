#pragma once
#include "SFML Game engine/States/GameState.h"
#include "SFML Game engine/GUI/RectangularButton.h"
#include "SFML Game engine/GUI/Textbox.h"
#include "SFML Game engine/GUI/Slider.h"

class Settings : public GameState{
	public:
		Settings(const sf::Vector2u &windowSize, StateManager &manager);
		void drawState(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) override;
	private:
		class PlusSign {
			public:
				PlusSign(const sf::Vector2f &position, const sf::Vector2f &size) : horizontal(size), vertical(size)  {
					horizontal.setOrigin(getHalfSize(horizontal));
					vertical.setOrigin(getHalfSize(vertical));


				}
			private:
				sf::RectangleShape horizontal, vertical;
		};
	private:		
		sf::Font font;
		sf::Text playerOne, playerTwo, moveUp, moveDown, buttonText;
		const int FONT_SIZE = 20;
		sf::Text title, test;
		RectangularButton backButton, applyButton;
		Textbox keyBox;
};

