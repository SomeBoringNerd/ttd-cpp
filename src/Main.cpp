#include "Platform/Platform.hpp"
#include "Scenes/Credit.hpp"
#include "Scenes/MainMenu.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/WalkScene.hpp"
#include "TheDumpsterFire.hpp"
#include "Utility/SceneManager.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define DRAW_HITBOXES true

sf::RenderWindow window;

static void Exit()
{
	window.close();
}

int focus = 1;
int x = 0, y = 0;

int getWindowSizeX()
{
	return x;
}
int getWindowSizeY()
{
	return y;
}

int getWindowState()
{
	return focus;
}
bool vDrawEntityHitboxes = false;
bool drawEntityHitboxes()
{
	return vDrawEntityHitboxes;
}

bool _canPlayerMove;
void setPlayerMove(bool newVal)
{
	_canPlayerMove = newVal;
}
bool canPlayerMove()
{
	return _canPlayerMove;
}

bool isKeyHold(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}
bool pressed = false;

bool isKeyPressed(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(key))
	{
		if (!pressed)
		{
			pressed = true;
			return true;
		}
	}
	else
	{
		pressed = false;
	}

	return false;
}

int main()
{
	util::Platform platform;

	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	// Use the screenScalingFactor
	window.create(sf::VideoMode(1280.0f * screenScalingFactor, 720.0f * screenScalingFactor), "Through The Dark");

	/**** Use icon ****/

	sf::Texture texture;
	texture.loadFromFile("logo.png");

	sf::Vector2u textureSize = texture.getSize();

	sf::Image image = texture.copyToImage();

	sf::Uint8* buffer = new sf::Uint8[textureSize.x * textureSize.y * 4];

	window.setIcon(64, 64, buffer);

	delete[] buffer;

	/********/

	window.setFramerateLimit(60);

	platform.setIcon(window.getSystemHandle());
	sf::Event event;

	new SceneManager();

	MainMenu* menu = new MainMenu();

	SceneManager::LoadScene(menu);
	sf::View view1;

	view1.reset(sf::FloatRect(1, 1, 1280, 720));

	window.setView(view1);

	while (window.isOpen())
	{
		window.setView(view1);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Exit();
			else if (event.type == sf::Event::GainedFocus)
			{
				focus = 1;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				focus = 0;
			}
			else if (event.type == sf::Event::Resized)
			{
				x = event.size.width;
				y = event.size.height;

				std::cout << "new window size : " << x << " / " << y << std::endl;
				float scaleX = 1;
				float scaleY = 1;
				std::cout << scaleX << " | " << scaleY << std::endl;
				if (x > 1280 && y > 720)
				{
					view1.reset(sf::FloatRect(-((x - 1280) / 2), -((y - 720) / 2), x, y));
					SceneManager::RefreshUI();
				}
				else
				{
					view1.reset(sf::FloatRect(0, 0, x, y));
					SceneManager::RefreshUI();
				}
			}
		}

		// Inside the game loop or the function where you check input
		if (isKeyPressed(sf::Keyboard::F3))
		{
			vDrawEntityHitboxes = !vDrawEntityHitboxes;
		}

		// dont run game update if the game is not focused
		if (getWindowState())
		{
			window.clear();

			SceneManager::Update(window, view1);
		}
		window.display();
	}

	return 0;
}

void LoadAnotherScene(std::string name)
{
	if (name == "MainMenu")
	{
		MainMenu* menu = new MainMenu();

		SceneManager::LoadScene(menu);
	}
	else if (name == "Credits")
	{
		Credit* cred = new Credit();

		SceneManager::LoadScene(cred);
	}
	else if (name == "Walker")
	{
		Walker* walk = new Walker();

		SceneManager::LoadScene(walk);
	}
}

int getGlobalMusicVolume()
{
	return 0;
}
