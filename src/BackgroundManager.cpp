#include <BackgroundManager.h>
#include <cmath>

BackgroundManager::BackgroundManager()
{
	for (int i = 0; i <= 3; i++)
	{
		std::string filename = "content/background/" + std::to_string(i) + ".png";
		texture[i].loadFromFile(filename);

		sf::RectangleShape spriteSize(WIN_SIZE);
		sprite[i] = spriteSize;
		sprite[i].setTexture(&texture[i]);
	}
}

void BackgroundManager::render(sf::RenderWindow& window, float xOff)
{
	for (int i = 0; i <= 3; i++)
	{
		sprite[i].setSize(window.getView().getSize());
		sprite[i].setOrigin(sprite[i].getSize().x / 2, sprite[i].getSize().y / 2);

		float spriteX = window.getView().getCenter().x + (xOff * i * i);

		while (spriteX < window.getView().getCenter().x - window.getView().getSize().x)
		{
			spriteX += sprite[i].getSize().x;
		}
		while (spriteX > window.getView().getCenter().x + window.getView().getSize().x)
		{
			spriteX -= sprite[i].getSize().x;
		}

		sprite[i].setPosition(spriteX, window.getView().getCenter().y);
		window.draw(sprite[i]);

		if (spriteX > window.getView().getCenter().x)
		{
			sprite[i].setPosition(spriteX - sprite[i].getSize().x, window.getView().getCenter().y);
		}
		else
		{
			sprite[i].setPosition(spriteX + sprite[i].getSize().x, window.getView().getCenter().y);
		}
		window.draw(sprite[i]);
	}
}