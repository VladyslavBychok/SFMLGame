#include "OneBall.h"
#include "MakeThrow.h"

sf::Texture OneBall::text;
sf::Sprite OneBall::sprite;

sf::Vector2f getCursorPosFromHero(sf::Vector2f heroPos, const sf::RenderWindow& wnd) noexcept(true) {

	auto pos = sf::Vector2f(sf::Mouse::getPosition(wnd));

	pos.x /= 5.f;
	pos.y /= 5.f;
	return pos - heroPos;
}

void OneBall::calcDir(sf::Vector2f mousePos) noexcept(true) {

	auto len = sqrtf(mousePos.x * mousePos.x + mousePos.y * mousePos.y);
	auto apn = sf::Vector2f(mousePos.x / len, mousePos.y / len);
	dir = apn;
}

OneBall::OneBall(sf::Vector2f curr, const sf::RenderWindow& wnd) noexcept(false) {

	if (static bool isInit = false; !isInit) {
		text.loadFromFile("textures/Ball.png");

		if (!text.loadFromFile("textures/Ball.png")) 
			MAKE_THROW("Failed to load texture");

		sprite.setTexture(text);
		isInit = true;
	}

	this->curr = curr + sf::Vector2f(8.f, 8.f);

	calcDir(getCursorPosFromHero(curr, wnd) - sf::Vector2f(16.f, 16.f));
}

void OneBall::drawAndUpdate(sf::RenderWindow& wnd) noexcept(true) {

	sprite.setPosition(curr);
	wnd.draw(sprite);

	curr += dir / 5.f;
}
