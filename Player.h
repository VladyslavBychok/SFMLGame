#pragma once

#include "Delay.h"

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Player final {

public:
	Player();

	Player(const Player&) = default; // copy constructor 
	
	Player(Player&&) = default; // move constructor 

	Player& operator=(const Player&) = default; // copy assignment operator

	void create(const std::string  addressTexture, sf::IntRect size) noexcept(false);

	void draw(sf::RenderWindow& window) noexcept(false);

	void attack(Direction last, Delay& Pause) noexcept(true);

	void motion(Direction& last, Delay& Pause, const sf::RenderWindow& window, std::vector<OneBall>& balls) noexcept(true);

	~Player() = default;

private:
	float x_;
	float y_;

	sf::Texture texture_;
	sf::Sprite sprite_;
};

