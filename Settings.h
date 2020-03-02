#pragma once
#include "SFML Game engine/States/GameState.h"
#include "SFML Game engine/GUI/RectangularButton.h"
#include "SFML Game engine/GUI/Textbox.h"
#include "SFML Game engine/GUI/Slider.h"
//#include "PlusSign.h"

class Settings : public GameState{
	public:
		Settings(const sf::Vector2u &windowSize, StateManager &manager);
		void drawState(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) override;	
	private:
		//class PlusSign : public sf::Drawable {
		//	public:
		//		PlusSign(const sf::Vector2f &position, const sf::Vector2f &size) : horizontal(size), vertical(size){
		//			horizontal.rotate(-90);
		//			horizontal.setOrigin(getHalfSize(horizontal));
		//			vertical.setOrigin(getHalfSize(vertical));
		//			horizontal.setPosition(position);
		//			vertical.setPosition(position);
		//			//vertical.setPosition(position.x + getHalfSize(vertical).x, );
		//		}
		//		void setColor(const sf::Color& color);
		//		void eventHandler(const sf::Event& e, const sf::RenderWindow& window);
		//		void setOnClickEvent(const std::function<void()>& onClick);
		//	private:
		//		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		//	private:
		//		sf::RectangleShape horizontal, vertical;
		//};
		/*struct PlusSign {
			PlusSign(const sf::Vector2f &position, const sf::Vector2f &size) : horizontal(size), vertical(size){
				horizontal.rotate(-90);
				horizontal.setOrigin(getHalfSize(horizontal));
				vertical.setOrigin(getHalfSize(vertical));
				horizontal.setPosition(position);
				vertical.setPosition(position);
			}
			sf::RectangleShape horizontal, vertical;
		};*/
	private:
		const int FONT_SIZE = 20;
		sf::Font font;
		sf::Text playerOne, playerTwo, moveUp, moveDown, buttonText, title;
		std::pair<sf::CircleShape, sf::CircleShape> playerOneMoveUpToggle, playerOneMoveDownToggle;
		std::pair<sf::CircleShape, sf::CircleShape> playerTwoMoveUpToggle, playerTwoMoveDownToggle;
		RectangularButton backButton, applyButton;
		Textbox keyBox;
};

