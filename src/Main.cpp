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

int viewportX, viewportY;

void setViewportX(int x)
{
	viewportX = x;
}
void setViewportY(int y)
{
	viewportY = y;
}

int tp_flag = 0;
int teleportFlag()
{
	return tp_flag;
}
void setTeleportFlag(int e)
{
	tp_flag = e;
}

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

bool orderExecuted = false;
bool drawTextBox = false;

bool _orderExecuted()
{
	return orderExecuted;
}
bool _drawTextBox()
{
	return drawTextBox;
}

void setOrderExecuted(bool e)
{
	orderExecuted = e;
}
void setDrawTextBox(bool e)
{
	drawTextBox = e;
}
int id;
void setID(int e)
{
	id = e;
}

void RenderTextBox(sf::RenderWindow& window, sf::View view)
{
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	sf::FloatRect viewBounds(viewCenter - viewSize / 2.0f, viewSize);

	sf::Texture backGroundTexture;
	backGroundTexture.loadFromFile("content/textures/textbox.png");

	sf::RectangleShape backGround(sf::Vector2f(600, 250));
	backGround.setPosition(sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 300, viewBounds.top + (getWindowSizeY() - 300)));
	backGround.setTexture(&backGroundTexture);

	window.draw(backGround);

	// this is going to be really fucked up in a few months
	switch (id)
	{
		case 0: {
			Text* owl = new Text("This was such a great show...", 24);
			owl->Render(window, sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 280, viewBounds.top + (getWindowSizeY() - 280)), false, true);
			break;
		}
		case 1: {
			Text* gravity = new Text("That was weirdly fun.", 24);
			gravity->Render(window, sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 280, viewBounds.top + (getWindowSizeY() - 280)), false, true);
			break;
		}
		case 2: {
			Text* sleep = new Text("No time for this!", 24);
			sleep->Render(window, sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 280, viewBounds.top + (getWindowSizeY() - 280)), false, true);
			break;
		}
		case 3: {
			Text* puter = new Text("I love my computer", 24);
			puter->Render(window, sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 280, viewBounds.top + (getWindowSizeY() - 280)), false, true);
			Text* puter2 = new Text("all my friends are inside it!", 24);
			puter2->Render(window, sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 280, viewBounds.top + (getWindowSizeY() - 250)), false, true);
			break;
		}
		default:
			Text* weird = new Text("What you are seeing here is an error message", 24);
			weird->Render(window, sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 280, viewBounds.top + (getWindowSizeY() - 280)), false);
			Text* weird2 = new Text("Please report this on discord or whatever", 24);
			weird2->Render(window, sf::Vector2f(viewBounds.left + (getWindowSizeX() / 2) - 280, viewBounds.top + (getWindowSizeY() - 250)), false);
			break;
	}
}

void ExecuteOrder66(int ID)
{
	switch (ID)
	{
		default:
			break;
		case 0:
		case 1:
		case 2:
		case 3: // textbox related stuff
			setPlayerMove(false);
			drawTextBox = true;
			break;
		case 4: // door in the first room
			tp_flag = 1;
			break;
	}
}

bool Collide;
void setCollide(bool e)
{
	Collide = e;
}
bool doesCollide()
{
	return Collide;
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
	bool f3Menu;
	delete[] buffer;

	/********/

	window.setFramerateLimit(60);

	platform.setIcon(window.getSystemHandle());
	sf::Event event;

	new SceneManager();

	MainMenu* menu = new MainMenu();

	SceneManager::LoadScene(menu);
	sf::View worldView;
	worldView.setSize(1280, 720);

	window.setView(worldView);

	while (window.isOpen())
	{
		orderExecuted = false;
		window.setView(worldView);

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
					worldView.reset(sf::FloatRect(-((x - 1280) / 2), -((y - 720) / 2), x, y));
					SceneManager::RefreshUI();
				}
				else
				{
					worldView.reset(sf::FloatRect(0, 0, x, y));
					SceneManager::RefreshUI();
				}
			}
		}

		worldView.setCenter(sf::Vector2f(viewportX, viewportY));
		worldView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

		// Inside the game loop or the function where you check input
		if (isKeyPressed(sf::Keyboard::F3))
		{
			if (!f3Menu)
			{
				vDrawEntityHitboxes = !vDrawEntityHitboxes;
				f3Menu = true;
			}
		}
		else
		{
			f3Menu = false;
		}

		// dont run game update if the game is not focused
		if (getWindowState())
		{
			window.clear();
			window.setView(worldView);
			SceneManager::Update(window, worldView);
		}

		if (isKeyPressed(sf::Keyboard::E) && !orderExecuted && Collide)
		{
			orderExecuted = true;
			ExecuteOrder66(id);
		}

		if (drawTextBox)
		{
			RenderTextBox(window, window.getView());

			if (isKeyPressed(sf::Keyboard::Z))
			{
				drawTextBox = false;
				setPlayerMove(true);
			}
		}
		window.display();

		Collide = false;
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
