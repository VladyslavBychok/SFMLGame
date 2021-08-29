#pragma once
#include "OneBall.h"


using namespace sf;

class Delay final {
public:
	Delay();

	Delay(const Delay&) = default; // copy constructor 

	Delay(Delay&&) = default; // move constructor 

	Delay& operator=(const Delay&) = default; // copy assignment operator

	void timePause(std::vector<OneBall>& balls, const sf::Sprite& Axeman, const sf::RenderWindow& window) noexcept(true);

	void buttonTimePause() noexcept(true);

	void animationTimePause() noexcept(true);
	
	void timePause() noexcept(true);

	int getI();

	int getJ();

	bool getIsAttack();

	~Delay() = default;

private:
	clock_t lastTime;
	int i;
	int j;
	bool isAttack;
};