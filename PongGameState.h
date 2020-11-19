#pragma once
#include "SFML Game engine/States/GameState.h"
#include "SFML Game engine/Utilities/Random.h"
#include "Paddle.h"
#include "Enums.h"


class PongGameState : public GameState {
	public:
		PongGameState(const sf::Vector2u &windowSize, StateManager &manager, GameMode mode, Difficulty difficulty);
		void drawState(sf::RenderWindow &window) override;
		void update(float deltaTime) override;
		void pause() override;
		void unpause() override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime) override;

	private:
		void bounceBall();
		void createBorder(sf::RenderWindow &window);
		void manageScore();
		void endGame(sf::RenderWindow &window);
		void resetGame();
		void setBallAngle();
		void changeBallAngle();
		void drawPauseMenu(sf::RenderWindow &window);
		void setDifficulty(Difficulty difficulty);
	private:
		bool isGamePaused;
		double ballAngle;
		float ballSpeedMagnitude, paddleSpeed, offset;
		const std::string MAX_SCORE;
		sf::Vector2f ballSpeed;
		sf::Text scoreLeft, scoreRight, win, playAgain, reset, resume, menu, quit;
		Paddle left, right;
		Random rand;
		sf::RectangleShape ball;
		GameMode mode;
		Difficulty difficulty;
};

