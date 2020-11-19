#include "PongGameState.h"
#include "SFML Game engine/Asset Manager/AssetManager.h"

PongGameState::PongGameState(const sf::Vector2u &windowSize, StateManager &manager, GameMode mode, Difficulty difficulty) :
GameState(windowSize), mode(mode), 
left(Orientation::LEFT, { 25.f, 100.f }, windowSize), right(Orientation::RIGHT, { 25.f, 100.f }, windowSize),
ball({ 15.f, 15.f }), ballSpeedMagnitude(800.f), isGamePaused(false), paddleSpeed(500.f),
scoreLeft("0", AssetManager::get().getDefaultFont(Fonts::ARCADE_N)), 
scoreRight("0", AssetManager::get().getDefaultFont(Fonts::ARCADE_N)), MAX_SCORE("5"),
win("win", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 50), 
playAgain("play again?\n(spacebar)", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 20),
reset("reset\n(click)", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 20), 
resume("resume", AssetManager::get().getDefaultFont(Fonts::ARCADE_N), 45),
menu("menu", AssetManager::get().getDefaultFont(Fonts::ARCADE_N)),
quit("quit", AssetManager::get().getDefaultFont(Fonts::ARCADE_N))
{
	ball.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	scoreLeft.setPosition(windowSize.x / 2.f - getSize(scoreLeft).x * 3.f, 0.f);
	scoreRight.setPosition(windowSize.x / 2.f + getSize(scoreRight).x * 2.f, 0.f);
	resume.setPosition(windowSize.x / 2.f - getHalfSize(resume).x, windowSize.y * 0.3f);
	menu.setPosition(windowSize.x / 2.f - getHalfSize(menu).x, getBottomEdge(resume) + getSize(menu).y * 3);
	quit.setPosition(windowSize.x / 2.f - getHalfSize(quit).x, getBottomEdge(menu) + getSize(quit).y * 3);

	setBallAngle();
	setDifficulty(difficulty);
	std::cout << "sin(" << ballAngle << "): " << sin(toRadians(ballAngle)) << "\n";
	std::cout << "cos(" << ballAngle << "): " << cos(toRadians(ballAngle)) << "\n";
	std::cout << "ball speed x: " << ballSpeed.x << " and y: " << ballSpeed.y << "\n";
}

void PongGameState::drawState(sf::RenderWindow &window){
	left.drawPaddle(window);
	right.drawPaddle(window);
	window.draw(scoreLeft);
	window.draw(scoreRight);
	endGame(window);
	createBorder(window);
	window.draw(ball);
	
	if (isGamePaused)
		drawPauseMenu(window);
}

void PongGameState::update(float deltaTime){
	if (!isGamePaused) {
		ball.move(ballSpeed.x * deltaTime , ballSpeed.y * deltaTime);
	}

	bounceBall();
	manageScore();
	changeBallAngle();
	if (mode == GameMode::ONE_PLAYER) {
		right.cpuMove(0.f, (ballSpeed.y * offset) * deltaTime);
	}

	left.update(WINDOW_SIZE, deltaTime);
	right.update(WINDOW_SIZE, deltaTime);
}

void PongGameState::pause(){
	left.pausePaddle();
	right.pausePaddle();
}

void PongGameState::unpause(){
	left.unPausePaddle();
	right.unPausePaddle();
}

void PongGameState::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window, float deltaTime){
	if (isKeyPressed(sf::Keyboard::P, e) and !isGamePaused) {
		pause();
		isGamePaused = true;
	}
	else if ((isKeyPressed(sf::Keyboard::P, e) or isEntityClicked(resume, window)) and isGamePaused) {
		unpause();
		isGamePaused = false;
	}
	else if (isEntityClicked(reset, window) or isEntityClicked(menu, window)) {
		manager.popState();
	}
	else if (isKeyPressed(sf::Keyboard::Space, e)) {
		resetGame();
	}
	else if (isEntityClicked(quit, window)) {
		manager.quitGame();
	}
	else if (mode == GameMode::ONE_PLAYER) {
		left.move(e, window.getSize(), paddleSpeed);
	}
	else if (mode == GameMode::TWO_PLAYER) {
		right.move(e, window.getSize(), paddleSpeed);
		left.move(e, window.getSize(), paddleSpeed);
	}
}

void PongGameState::bounceBall(){
	if (ball.getPosition().y < 0.f) {
		ballSpeed.y *= -1;

		//set the position of the ball to the top of the window to prevent it from getting stuck
		ball.setPosition(ball.getPosition().x, 0.f);
	}
	
	else if (getBottomEdge(ball) > WINDOW_SIZE.y) {
		ballSpeed.y *= -1;
		
		//Do the same for the bottom of the window
		ball.setPosition(ball.getPosition().x, WINDOW_SIZE.y - ball.getSize().y);
	}
}

void PongGameState::createBorder(sf::RenderWindow &window){
	sf::RectangleShape borderPiece({ 2.5f, 10.f });

	for (size_t i = 0; i < window.getSize().y; i += borderPiece.getSize().y * 2.f) {
		borderPiece.setPosition(window.getSize().x / 2, i);
		window.draw(borderPiece);
	}
}

void PongGameState::manageScore(){
	if (ball.getPosition().x > WINDOW_SIZE.x) {
		left.increaseScore();
		scoreLeft.setString(left.getScore());
		ball.setPosition(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
		setBallAngle();
	}
	else if (getRightEdge(ball) < 0.f) {
		right.increaseScore();
		scoreRight.setString(right.getScore());
		ball.setPosition(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
		setBallAngle();
	}
}

void PongGameState::endGame(sf::RenderWindow &window){
	if (left.getScore() == MAX_SCORE) {
		win.setPosition(WINDOW_SIZE.x * .2f, WINDOW_SIZE.y / 3.f);
		playAgain.setPosition(WINDOW_SIZE.x * .2f, WINDOW_SIZE.y / 2.f);
		reset.setPosition(WINDOW_SIZE.x * .2f, WINDOW_SIZE.y / 1.5f);
		window.draw(win);
		window.draw(playAgain);
		window.draw(reset);
		ballSpeed = sf::Vector2f();
		ball.setPosition(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y * 2.f);//move the ball off of the screen when the player wins
	}
	else if (right.getScore() == MAX_SCORE) {
		win.setPosition(WINDOW_SIZE.x * .6f, WINDOW_SIZE.y / 3.f);
		playAgain.setPosition(WINDOW_SIZE.x * .6f, WINDOW_SIZE.y / 2.f);
		reset.setPosition(WINDOW_SIZE.x * .6f, WINDOW_SIZE.y / 1.5f);
		window.draw(win);
		window.draw(playAgain);
		window.draw(reset);
		ballSpeed = sf::Vector2f();
		ball.setPosition(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y * 2.f);
	}
}

void PongGameState::resetGame(){
	ball.setPosition(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
	setBallAngle();
	left.setScore(0);
	right.setScore(0);
	left.resetToDefaultPosition(WINDOW_SIZE);
	right.resetToDefaultPosition(WINDOW_SIZE);
	scoreLeft.setString("0");
	scoreRight.setString("0");
}

void PongGameState::setBallAngle(){
	switch (rand.getNumberInRange(0, 3)){
		case 0: 
			ballAngle = 45;
			break;
		case 1:
			ballAngle = -45;
			break;
		case 2:
			ballAngle = 135;
			break;
		default:
			ballAngle = -135;
	}

	ballSpeed.x = cos(toRadians(ballAngle)) * ballSpeedMagnitude;
	ballSpeed.y = sin(toRadians(ballAngle)) * ballSpeedMagnitude;
}

void PongGameState::changeBallAngle(){		
	if (left.intersects(ball)) {
		ball.setPosition(left.getPaddleRightEdge(), ball.getPosition().y);
		float distanceFromPaddleBottom = abs(ball.getPosition().y - left.getPosition().y);
		float newAngle = mapper(distanceFromPaddleBottom, 0.f, left.getSize().y, -45.f, 45.f);
		ballSpeed.x = cos(toRadians(newAngle)) * ballSpeedMagnitude;
		ballSpeed.y = sin(toRadians(newAngle)) * ballSpeedMagnitude;
	}
	else if (right.intersects(ball)) {
		ball.setPosition(right.getPosition().x - ball.getSize().x, ball.getPosition().y);
		float distanceFromPaddleBottom = abs(ball.getPosition().y - right.getPosition().y);
		float newAngle = mapper(distanceFromPaddleBottom, 0.f, right.getSize().y, -45.f, 45.f );
		ballSpeed.x = -cos(toRadians(newAngle)) * ballSpeedMagnitude;
		ballSpeed.y = sin(toRadians(newAngle)) * ballSpeedMagnitude;
	}
}

void PongGameState::drawPauseMenu(sf::RenderWindow &window){
	sf::RectangleShape tintWindow(static_cast<sf::Vector2f>(WINDOW_SIZE));
	
	tintWindow.setFillColor(sf::Color(0, 0, 0, 100));
	window.draw(tintWindow);
	window.draw(resume);
	window.draw(menu);
	window.draw(quit);
}

void PongGameState::setDifficulty(Difficulty difficulty){
	switch (difficulty){
		case Difficulty::BEGINNGER:
			offset = 0.5;
			break;
		case Difficulty::INTERMEDIATE:
			offset = 0.7;
			break;
		default:
			offset = 0.9;
	}
}
