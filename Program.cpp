#include "Program.h"

Program::Program() : last{ Direction::DOWN } {
	wnd.create(VideoMode(1000, 1000), "Game");
}

void Program::launch() {
	wnd.setView(View(FloatRect(0, 0, 200, 200)));
	axemanHero.create("textures/Axeman.png", sf::IntRect(0, 0, 32, 32));

	while (wnd.isOpen()) {

		while (wnd.pollEvent(event)) {
			if (event.type == Event::EventType::Closed) wnd.close();
		}

		wnd.clear(Color(34, 139, 34));

		axemanHero.attack(last, pause);
		axemanHero.motion(last, pause, wnd, balls);
		axemanHero.draw(wnd);

		for (auto& ball : balls) {
			ball.drawAndUpdate(wnd);
		}

		
		wnd.display();
	}
}
