#pragma once

#include <string>
#include <SFML/Graphics.hpp>

constexpr float PI = 3.14159265358979323846f;
constexpr float MIN_PI = 3.14f;
constexpr float HALF_PI = 1.57079632679489661923f;
constexpr float QUARTER_PI = 0.7853982f;

/**
* Function to return the size of an object 
*/
template<class SFML_OBJECT>
sf::Vector2f getSize(const SFML_OBJECT &object) {
	return sf::Vector2f(object.getGlobalBounds().width, object.getGlobalBounds().height);
}

/*
* Function to return the position of the center of a SFML object relative to its current position
*/
template<class SFML_OBJECT>
sf::Vector2f getHalfSize(const SFML_OBJECT &object) {
	return sf::Vector2f(object.getGlobalBounds().width / 2.f, object.getGlobalBounds().height / 2.f);
}

/*
* Function to return the position of the right edge of a SFML object
*/
template<class SFML_OBJECT>
float getRightEdge(const SFML_OBJECT &object) {
	return object.getPosition().x + object.getGlobalBounds().width;
}

/*
* Function to return the position of the bottom edge of a SFML object
*/
template<class SFML_OBJECT>
float getBottomEdge(const SFML_OBJECT &object) {
	return object.getPosition().y + object.getGlobalBounds().height;
}

/*
* Function to return the position of the center of a SFML object relative to its current position
*/
template<class SFML_OBJECT>
sf::Vector2f getCenterPosition(const SFML_OBJECT &object) {
	return object.getPosition() + getHalfSize(object);
}

/**
* function to map a value from one range proportionally to another.
*
* @param valueToMap: the incoming value to be converted
* @param startOne: lower bound of the value's current range
* @param endOne: upper bound of the value's current range
* @param startTwo: lower bound of the value's target range
* @param endTwo: upper bound of the value's target range
*
* Returns the proportional number in the new range.
*/
template<class type>
constexpr type mapper(type valueToMap, type startOne, type endOne, type startTwo, type endTwo) {
	return (1 - ((valueToMap - startOne) / (endOne - startOne))) * startTwo + ((valueToMap - startOne) / (endOne - startOne)) * endTwo;
}

/**
* function to limit an incoming value between a maximum and minimum value. If the value to be constrained is larger or smaller than
* the max or min, return either the max or min depending on which limit was exceeded. Otherwise simply return the number sent.
*
* @param numToConstrain: the incoming value to be constrained.
* @param min: lower bound.
* @param max: upper bound.
*
* Returns: constrained number
*/
template<class type>
constexpr type constrain(type numToConstrain, type min, type max) {
	return (numToConstrain <= min) ? min : (numToConstrain >= max) ? max : numToConstrain;
}

template <class type>
constexpr type toRadians(type degrees) {
	return (degrees * PI) / 180;
}

template <class type>
constexpr type toDegrees(type radians) {
	return (radians * 180) / PI;
}