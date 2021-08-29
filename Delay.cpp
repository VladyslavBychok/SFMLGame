#include "Delay.h"

Delay::Delay() : lastTime{ 0u }, i{ 0 }, j{ 0 }, isAttack{ false } {}

int Delay::getI() {
	return i;
}

int Delay::getJ() {
	return j;
}

bool Delay::getIsAttack() {
	return isAttack;
}

void Delay::timePause(std::vector<OneBall>& balls, const sf::Sprite& Axeman, const sf::RenderWindow& window) noexcept(true) {

	if (clock() - lastTime >= 80) {
		balls.push_back(OneBall(Axeman.getPosition(), window));
		lastTime = clock();
	}
}

void Delay::buttonTimePause() noexcept(true) {

	if (clock() - lastTime >= 80) {
		isAttack = true;
		lastTime = clock();
	}
}

void Delay::animationTimePause() noexcept(true) {

	if (clock() - lastTime >= 80) {
		lastTime = clock();
		j++;

		if (j >= 5) {
			j = 0;
			isAttack = false;
		}
	}
}

void Delay::timePause() noexcept(true) {

	if (clock() - lastTime >= 80) {
		i++;
		if (i == 5) i = 0;
		lastTime = clock();
	}
}
