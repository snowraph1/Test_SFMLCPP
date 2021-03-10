#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <random>
#include <list>

using namespace std;
using namespace sf;

class Obstacle {
	public:
		RectangleShape shape;
};

int main() {
	const Vector2f gravity(0.f, 0.4f);
	const int screenWidth = 600;
	const int screenHeight = 1100;

	const float playerBig = 0.1f;
	const float playerSmall = 0.05f;

	float barSpeed;

	RenderWindow window(VideoMode(screenWidth, screenHeight), "Title");

	window.setFramerateLimit(120);

	Event event;

	Texture texture;

	if (!texture.loadFromFile("res/img/Circle.png"))
	{
		cout << "Not loaded";
	}

	int spritePos;

	Sprite sprite;
	sprite.setTexture(texture);
	FloatRect fr = sprite.getGlobalBounds();
	sprite.setOrigin(fr.width / 2, fr.height / 2);
	sprite.setPosition(screenWidth / 2, screenHeight / 4 * 3);

	cout << sprite.getPosition().x << sprite.getPosition().y;

	Clock clock;
	Clock spawnClock;

	float playerScale = playerBig;
	bool isSmall = false;

	sprite.setScale(playerScale, playerScale);

	float timeSpawn;

	float randomTime = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.5, 3.2);

	list<Obstacle> obstacles;

	while (window.isOpen())
	{
		Time time = clock.getElapsedTime();

		timeSpawn = spawnClock.getElapsedTime().asSeconds();

		if (timeSpawn > randomTime) {
			randomTime = dis(gen);
			//cout << "test : " << randomTime << "\n";
			Obstacle obs = Obstacle();
			obs.shape = RectangleShape(Vector2f(200, 50));
			obs.shape.setFillColor(sf::Color(124, 252, 0));
			obstacles.push_back(obs);
			cout << obstacles.size();
			spawnClock.restart();
		}

		while (window.pollEvent(event)) {
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;

				case Event::KeyPressed:
					if (event.key.code == Keyboard::Space) {
						
					}
					break;

				case Event::MouseButtonPressed:
					if (event.mouseButton.button == Mouse::Left) {
						if (isSmall) {
							playerScale = playerBig;
							isSmall = false;
						}
						else
						{
							playerScale = playerSmall;
							isSmall = true;
						}
					}
					break;
			}
		}

		clock.restart().asMilliseconds();

		for (Obstacle var : obstacles)
		{
			cout << var.shape.getPosition().x << ", " << var.shape.getPosition().y;
			var.shape.setPosition(var.shape.getPosition().x, var.shape.getPosition().y + 0.6f);
			cout << var.shape.getPosition().x << ", " << var.shape.getPosition().y;
		}

		window.clear();

		sprite.setScale(playerScale, playerScale);

		window.draw(sprite);

		for (Obstacle var : obstacles)
		{
			window.draw(var.shape);
		}

		window.display();
	}

	return 0;
}