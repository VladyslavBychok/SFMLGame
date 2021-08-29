#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>

sf::Vector2f getCursorPosFromHero(sf::Vector2f heroPos, const sf::RenderWindow& wnd) noexcept(true);

class OneBall final {
private:

	sf::Vector2f curr;
	sf::Vector2f dir;

	static sf::Texture text;
	static sf::Sprite sprite;

	void calcDir(sf::Vector2f mousePos) noexcept(true);

public:
	OneBall(sf::Vector2f curr, const sf::RenderWindow& wnd) noexcept(false);

	OneBall(const OneBall&) = default; // copy constructor 

	OneBall(OneBall&&) = default; // move constructor

	OneBall& operator=(const OneBall&) = default; // copy assignment operator

	void drawAndUpdate(sf::RenderWindow& wnd) noexcept(true);

	~OneBall() = default;
};