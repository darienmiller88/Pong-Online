#include "Paddle.h"
#include <iostream>

Paddle::Paddle(Orientation orientation, const sf::Vector2f &paddleSize, const sf::Vector2u &windowSize) : 
ySpeed(0), body(sf::Vector2f(paddleSize)), score(0), isGamePaused(false), orientation(orientation){
	resetToDefaultPosition(windowSize);
}

void Paddle::move(const sf::Event &e, const sf::Vector2u &windowSize, float speed){
	if (sf::Keyboard::isKeyPressed(keys.first) and !isGamePaused)
		ySpeed = -speed;
	else if (sf::Keyboard::isKeyPressed(keys.second) and !isGamePaused)
		ySpeed = speed;
	else if (e.type == sf::Event::KeyReleased and !isGamePaused)
		ySpeed = 0;
}

void Paddle::update(const sf::Vector2u &windowSize, float deltaTime){
	float constrainedY = windowSize.y - body.getSize().y;

	body.move(0.f, ySpeed * deltaTime);
	body.setPosition(body.getPosition().x, constrain(body.getPosition().y, 0.f, constrainedY));
}

void Paddle::cpuMove(float moveOffSet, float speedToMove){
	body.move(0.f, speedToMove);
	/*if (!isGamePaused and ballYSpeed < 0)
		body.move(0.f, -speedToMove);
	else if(!isGamePaused and ballYSpeed > 0)
		body.move(0.f, speedToMove);*/
		//body.setPosition(body.getPosition().x, ballY);
}

void Paddle::setPosition(const sf::Vector2f &position){
	body.setPosition(position);
}

void Paddle::increaseScore(){
	score++;
}

void Paddle::drawPaddle(sf::RenderWindow &window){
	window.draw(body);
}

void Paddle::setScore(int newScore){
	score = newScore;
}

void Paddle::setGameKeys(const MovementKeys &keys){
	this->keys = keys;
}

void Paddle::pausePaddle(){
	isGamePaused = true;
}

void Paddle::unPausePaddle(){
	isGamePaused = false;
}

const sf::Vector2f &Paddle::getPosition() const{
	return body.getPosition();
}

const MovementKeys &Paddle::getUserKeys() const{
	return keys;
}

float Paddle::getPaddleRightEdge() const{
	return getRightEdge(body);
}

float Paddle::getPaddleBottomEdge() const{
	return getBottomEdge(body);
}

std::string Paddle::getScore() const{
	return std::to_string(score);
}

const sf::Vector2f &Paddle::getSize() const{
	return body.getSize();
}

void Paddle::resetToDefaultPosition(const sf::Vector2u &windowSize){
	switch (orientation) {
		case Orientation::LEFT:
			body.setPosition(body.getSize().x * 2.f, windowSize.y / 2.f - getHalfSize(body).y);
			keys = MovementKeys(sf::Keyboard::W, sf::Keyboard::S);
			break;
		case Orientation::RIGHT:
			body.setPosition(windowSize.x - (body.getSize().x * 2.f), windowSize.y / 2.f - getHalfSize(body).y);
			keys = { sf::Keyboard::Up, sf::Keyboard::Down };
			break;
	}
}
