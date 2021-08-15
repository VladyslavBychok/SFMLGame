#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <thread>

using namespace sf;

sf::Vector2f getCursorPosFromHero(sf::Vector2f heroPos, const sf::RenderWindow& wnd) {
	auto pos = Vector2f(Mouse::getPosition(wnd));
	pos.x /= 5.f;
	pos.y /= 5.f;
	return pos - heroPos;
}

class OneBall {
private:
	sf::Vector2f curr;
	sf::Vector2f dir;
	Texture TextureBall;
	Sprite Ball;
	void calcDir(sf::Vector2f mousePos) {
		auto ap = mousePos - curr;
		auto len = sqrtf( ap.x * ap.x + ap.y * ap.y );
		auto apn = sf::Vector2f( ap.x / len, ap.y / len );
		dir = apn;
	}
public:
	OneBall(sf::Vector2f curr, const sf::RenderWindow& wnd) {
		TextureBall.loadFromFile("textures/Ball.png");
		Ball.setTexture(TextureBall);

		this->curr = curr;
		calcDir( getCursorPosFromHero( curr , wnd));
	}

	void drawAndUpdate(RenderWindow &wnd) {
		//for (int l = 0; l < coordinates.size(); l++) {
		//
		//	Ball.setPosition(coordinates[l].x, coordinates[l].y);
		//	wnd.draw(Ball);
		//}
		Ball.setPosition(curr);
		wnd.draw(Ball);
		curr += dir;
	}
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};



template<class T>
void print(const sf::Vector2<T> vec) {
	std::cout << vec.x << " " << vec.y << std::endl;
}

int main() {
	RenderWindow wnd(VideoMode(1000, 1000), "Game");
	wnd.setView(View(FloatRect(0,0,200,200)));
	Texture TextureAxeman;
	TextureAxeman.loadFromFile("textures/Axeman.png");
	

	Sprite Axeman;
	Axeman.setTexture(TextureAxeman);
	Axeman.setTextureRect(IntRect(0,0,32,32));
	
	std::vector<OneBall> balls;


	float x = 0, y = 0, BallX = 0, BallY = 0;
	int i = 0, j = 0;
	clock_t lastTime = 0u;
	bool attack = false, BallSpawn = false;
	
	std::vector<sf::Vector2f> coordinates;

	Direction last = DOWN;

	while (wnd.isOpen()) {
		Event event;

		while (wnd.pollEvent(event)) {
			if (event.type == Event::EventType::Closed) wnd.close();
		}

		

		wnd.clear(Color(34,139,34));

		if(Mouse::isButtonPressed(Mouse::Button::Left)){
			auto position = Mouse::getPosition(wnd);
			if (clock() - lastTime >= 80) {
				attack = true;
				std::cout << "x = " << position.x - Axeman.getPosition().x << "y = " << position.y - Axeman.getPosition().y << std::endl;
				
				balls.push_back( OneBall(Axeman.getPosition(), wnd) );

				
				lastTime = clock();
			}
		}		

		if (attack) {
			switch (last)
			{
			case UP:
				Axeman.setTextureRect(IntRect(32 * j + 320, 96, 32, 32));
				break;
			case DOWN:
				Axeman.setTextureRect(IntRect(32 * j + 320, 0, 32, 32));
				break;
			case LEFT:
				Axeman.setTextureRect(IntRect(32 * j + 320, 32, 32, 32));
				break;
			case RIGHT:
				Axeman.setTextureRect(IntRect(32 * j + 320, 64, 32, 32));
				break;
			}

			//std::this_thread::sleep_for(std::chrono::milliseconds(50));
			if (clock() - lastTime >= 80) {
				lastTime = clock();
				j++;

				if (j >= 5) {
					j = 0;
					attack = false;
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			x -= 0.1f;
			Axeman.setTextureRect(IntRect(32 * i, 32, 32, 32));
			last = LEFT;
			if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			x += 0.1f;
			Axeman.setTextureRect(IntRect(32 * i, 64, 32, 32));
			last = RIGHT;
			if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			y -= 0.1f;
			Axeman.setTextureRect(IntRect(32 * i, 96, 32, 32));
			last = UP;
			if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			y += 0.1f;
			Axeman.setTextureRect(IntRect(32*i, 0, 32, 32));
			last = DOWN;
			if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}
		}

		Axeman.setPosition(x,y);
		wnd.draw(Axeman);


		for (auto& ball : balls) {
			ball.drawAndUpdate(wnd);
		}

		wnd.display();
	}
}