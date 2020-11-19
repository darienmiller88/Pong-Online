#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "SFML Game engine/Math stuff/Math.h"

//typedef to simplify this long winded declaration. Below, the need for a pair of keyboard keys is to allow the user to
//define what key will move the paddle up and down.
using MovementKeys = std::pair<sf::Keyboard::Key, sf::Keyboard::Key>;

/**
* Enum that will determine which side of the screen the paddle will be on.
*/
enum class Orientation {
	LEFT, RIGHT
};

/*
* class to determine the behavior of a pong paddle and store all of the relevant information.
*/
class Paddle{
	public:
		Paddle(Orientation orientation, const sf::Vector2f &paddleSize, const sf::Vector2u &windowSize);

		//function that allows the user to move their paddle by pressing the keys they assigned to it.
		void move(const sf::Event &e, const sf::Vector2u &windowSize, float speed);
		void update(const sf::Vector2u &windowSize, float deltaTime);

		//include a function that will allows a paddle to move by itself, in accordance with the ball's y position subtracted by an
		//"offset" that prevents the paddle from being perfect.
		void cpuMove(float moveOffSet, float speedToMove);
		void setPosition(const sf::Vector2f &position);
		void increaseScore();
		void drawPaddle(sf::RenderWindow &window);
		void setScore(int newScore);
		void setGameKeys(const MovementKeys &keys);
		void pausePaddle();
		void unPausePaddle();		
		std::string getScore() const;
		const sf::Vector2f &getPosition() const;
		const sf::Vector2f &getSize() const;
		const MovementKeys &getUserKeys() const;
		float getPaddleBottomEdge() const;
		float getPaddleRightEdge() const;

		template<class SFML_OBJECT>
		bool intersects(const SFML_OBJECT &ball) const;

		//checks the ball to see if it is between the top and bottom of the paddle
		bool isBallInRange(const sf::RectangleShape &ball) const;
		void resetToDefaultPosition(const sf::Vector2u &windowSize);
	private:
		Orientation orientation;

		//a pair of SFML key representing which keyboard key moves the paddle up and down. first = up key. second = down key.
		MovementKeys keys;

		//the rectangle representing the shape of the paddle
		sf::RectangleShape body;

		//how fast the paddle moves up and down
		float ySpeed;
		int score;
		bool isGamePaused;
};

template<class SFML_OBJECT>
inline bool Paddle::intersects(const SFML_OBJECT &ball) const{
	return body.getGlobalBounds().intersects(sf::FloatRect(ball.getGlobalBounds()));
}
