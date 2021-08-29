#include "Delay.h" 
#include "Player.h" 
#include "OneBall.h" 
#include "MakeThrow.h"

#include <iostream>
using namespace sf;




int run() {

	RenderWindow wnd(VideoMode(1000, 1000), "Game");
	wnd.setView(View(FloatRect(0,0,200,200)));

	Player AxemanHero;
	AxemanHero.create("textures/Axeman.png", sf::IntRect(0, 0, 32, 32));
	
	std::vector<OneBall> balls;
	Delay Pause;

	Direction last = Direction::DOWN;


	
	while (wnd.isOpen()) {

		Event event;

		while (wnd.pollEvent(event)) {
			if (event.type == Event::EventType::Closed) wnd.close();
		}

		wnd.clear(Color(34,139,34));

		AxemanHero.attack(last, Pause);
		AxemanHero.motion(last, Pause, wnd, balls);
		AxemanHero.draw(wnd);

		for (auto& ball : balls) {
			ball.drawAndUpdate(wnd);
		}

		wnd.display();
	}

	return 0;
}

int main() {

	try
	{
		run();
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Undefind eror" << std::endl;
	}

	return 0;
}