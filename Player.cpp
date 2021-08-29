#include "Player.h"
#include "MakeThrow.h"



Player::Player() : x_{ 0.f }, y_{ 0.f }{}

void Player::create(const std::string  addressTexture, sf::IntRect size) noexcept(false) {

	texture_.loadFromFile(addressTexture);

	if (!texture_.loadFromFile(addressTexture)) 
		MAKE_THROW("Failed to load image");

	sprite_.setTexture(texture_);
	sprite_.setTextureRect(size);
}

void Player::draw(sf::RenderWindow& window) noexcept(false) {

	if (!window.isOpen())
		MAKE_THROW("Window is closed");

	sprite_.setPosition(x_, y_);
	window.draw(sprite_);
}

void Player::attack(Direction last, Delay& Pause) noexcept(true) {

	if (Pause.getIsAttack()) {

		switch (last)
		{
		case Direction::UP:
			sprite_.setTextureRect(IntRect(32 * Pause.getJ() + 320, 96, 32, 32));
			break;
		case Direction::DOWN:
			sprite_.setTextureRect(IntRect(32 * Pause.getJ() + 320, 0, 32, 32));
			break;
		case Direction::LEFT:
			sprite_.setTextureRect(IntRect(32 * Pause.getJ() + 320, 32, 32, 32));
			break;
		case Direction::RIGHT:
			sprite_.setTextureRect(IntRect(32 * Pause.getJ() + 320, 64, 32, 32));
			break;
		}

		Pause.animationTimePause();

	}
}

void Player::motion(Direction& last, Delay& Pause, const sf::RenderWindow& window,std::vector<OneBall>& balls) noexcept(true) {

	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		x_ -= 0.1f;

		sprite_.setTextureRect(IntRect(32 * Pause.getI(), 32, 32, 32));
		last = Direction::LEFT;
		Pause.timePause();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		x_ += 0.1f;

		sprite_.setTextureRect(IntRect(32 * Pause.getI(), 64, 32, 32));
		last = Direction::RIGHT;
		Pause.timePause();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		y_ -= 0.1f;

		sprite_.setTextureRect(IntRect(32 * Pause.getI(), 96, 32, 32));
		last = Direction::UP;
		Pause.timePause();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		y_ += 0.1f;

		sprite_.setTextureRect(IntRect(32 * Pause.getI(), 0, 32, 32));
		last = Direction::DOWN;
		Pause.timePause();
	}

	if (Mouse::isButtonPressed(Mouse::Button::Right))
		Pause.timePause(balls, sprite_, window);

	if (Mouse::isButtonPressed(Mouse::Button::Left))
		Pause.buttonTimePause();
	
}