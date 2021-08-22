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
	static Texture text;
	static Sprite sprite;
	void calcDir(sf::Vector2f mousePos) {
		auto len = sqrtf(mousePos.x * mousePos.x + mousePos.y * mousePos.y );
		auto apn = sf::Vector2f(mousePos.x / len, mousePos.y / len );
		dir = apn;
	}

public:
	OneBall(sf::Vector2f curr, const sf::RenderWindow& wnd) {
		if (static bool isInit = false; !isInit) {
			text.loadFromFile("textures/Ball.png");
			sprite.setTexture(text);
			isInit = true;
		}

		this->curr = curr + sf::Vector2f(8.f, 8.f);
		calcDir( getCursorPosFromHero( curr , wnd) - sf::Vector2f(16.f, 16.f));
	}

	void drawAndUpdate(RenderWindow &wnd) {
		sprite.setPosition(curr);
		wnd.draw(sprite);
		curr += dir / 5.f;
	}
};
Texture OneBall::text;
Sprite OneBall::sprite;

class Player {
public:
	Player() {
		x_ = y_ = 0.f;
	}

	void create(const std::string  addressTexture, const int recLeft, const int recTop, const int recWidth, const int recHeight) {
		texture_.loadFromFile(addressTexture);
		sprite_.setTexture(texture_);
		sprite_.setTextureRect(IntRect(recLeft, recTop, recWidth, recHeight));
	}
	


private:
	float x_;
	float y_;
	Texture texture_;
	Sprite sprite_;
};

class Delay {
public:
	Delay() {
		LastTime = 0u;
	}

	void TimePause(bool& attack, std::vector<OneBall>& balls, Sprite& Axeman, sf::RenderWindow& window) {
		if (clock() - LastTime >= 80) {
			attack = true;
			balls.push_back(OneBall(Axeman.getPosition(), window));
			LastTime = clock();
		}
	}

	void TimePause(bool& attack, int& j) {
		if (clock() - LastTime >= 80) {
			LastTime = clock();
			j++;

			if (j >= 5) {
				j = 0;
				attack = false;
			}
		}
	}

	void TimePause(int& i) {
		if (clock() - LastTime >= 80) {
			i++;
			if (i == 5) i = 0;
			LastTime = clock();
		}
	}

private:
	clock_t LastTime;
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

	//Player AxemanHero;
	//AxemanHero.create("textures/Axeman.png", 0, 0, 32, 32);

	Texture TextureAxeman;
	TextureAxeman.loadFromFile("textures/Axeman.png");
	
	Sprite Axeman;
	Axeman.setTexture(TextureAxeman);
	Axeman.setTextureRect(IntRect(0,0,32,32));
	
	std::vector<OneBall> balls;


	float x = 0, y = 0;
	int i = 0, j = 0;
	clock_t lastTime = 0u;
	bool attack = false, BallSpawn = false;
	
	Direction last = DOWN;

	/*
	структурировать код
	удалять элементы вектора
	добавить противника, убивать его
	*/
	Delay Pause;
	while (wnd.isOpen()) {
		Event event;

		while (wnd.pollEvent(event)) {
			if (event.type == Event::EventType::Closed) wnd.close();
		}

		wnd.clear(Color(34,139,34));
		
		if(Mouse::isButtonPressed(Mouse::Button::Left)){
			Pause.TimePause(attack, balls, Axeman, wnd);
			/*if (clock() - lastTime >= 80) {//////////////////////////////////////////////////////////////////////////////
				attack = true;				
				balls.push_back( OneBall(Axeman.getPosition(), wnd) );				
				lastTime = clock();
			}*/
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
			Pause.TimePause(attack, j);
			/*if (clock() - lastTime >= 80) {
				lastTime = clock();
				j++;

				if (j >= 5) {
					j = 0;
					attack = false;
				}
			}*/
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
			x -= 0.1f;
			Axeman.setTextureRect(IntRect(32 * i, 32, 32, 32));
			last = LEFT;
			Pause.TimePause(i);
			/*if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}*/
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
			x += 0.1f;
			Axeman.setTextureRect(IntRect(32 * i, 64, 32, 32));
			last = RIGHT;
			Pause.TimePause(i);
			/*if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}*/
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			y -= 0.1f;
			Axeman.setTextureRect(IntRect(32 * i, 96, 32, 32));
			last = UP;
			Pause.TimePause(i);
			/*if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}*/
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			y += 0.1f;
			Axeman.setTextureRect(IntRect(32*i, 0, 32, 32));
			last = DOWN;
			Pause.TimePause(i);
			/*if (clock() - lastTime >= 80) {
				i++;
				if (i == 5) i = 0;
				lastTime = clock();
			}*/
		}

		Axeman.setPosition(x,y);
		wnd.draw(Axeman);


		for (auto& ball : balls) {//foreach
			ball.drawAndUpdate(wnd);
		}

		wnd.display();
	}
}