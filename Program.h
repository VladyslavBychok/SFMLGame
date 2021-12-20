#pragma once

#include "Delay.h" 
#include "Player.h" 
#include "OneBall.h" 
#include "MakeThrow.h"
#include "Enemy.h"

#include <iostream>

class Program final{
public:
	Program();

	Program(const Program&) = delete;
	Program(Program&&) = delete;
	Program& operator=(const Program&) = delete;
	Program& operator=(Program&&) = delete;

	~Program() = default;

	void launch() noexcept(false);
private:
	RenderWindow wnd;
	Player axemanHero;
	//Enemy death;
	std::vector<OneBall> balls;
	Delay pause;
	Direction last;
	Event event;
};