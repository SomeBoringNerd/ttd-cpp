#pragma once

#include "../Utility/GUI.hpp"
#include "Platform/Platform.hpp"
#include "Scene.hpp"

#include <iostream>

#include "../Entity/Player.hpp"
#include "../Tiles/CollideTile.hpp"
#include "../Tiles/Tile.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "../TheDumpsterFire.hpp"

class Walker : public Scene
{
public:
	Walker()
	{

		this->name = "Walker";
		this->player = new Player(20, 0, 0, "Player", 0);

		if (false)
		{
			for (int x = 0; x < (64 * 15); x += 64)
			{
				if (x != 64 * 6 && x != 64 * 8)
				{
					tileset.insert(tileset.begin(), new Tile(sf::Vector2f(x, 550), "EmptyTile"));
					tileset.insert(tileset.begin(), new Tile(sf::Vector2f(x, 100), "EmptyTile"));
				}
			}

			// bed collider
			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(440, 4 * 64), "EmptyTile", 2));

			// desktop collider
			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(10 * 64 + 16, 124), "EmptyTile", 3));
			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(11 * 64, 124), "EmptyTile", 3));
			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(12 * 64 - 16, 124), "EmptyTile", 3));

			// doorframe collider
			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(15 * 64, 80), "EmptyTile", 4));

			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(16 * 64, 100), "EmptyTile"));
			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(17 * 64, 100), "EmptyTile", 1));
			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(18 * 64, 100), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(19 * 64, 100), "EmptyTile"));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(8 * 64, 100), "EmptyTile"));

			// some collider the loop at the beggining didnt add
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(6 * 64, 550), "EmptyTile"));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(8 * 64, 550), "EmptyTile"));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(15 * 64, 550), "EmptyTile"));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(16 * 64, 550), "EmptyTile"));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(17 * 64, 550), "EmptyTile"));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(18 * 64, 550), "EmptyTile"));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(19 * 64, 550), "EmptyTile"));

			for (int y = 0; y < 720; y += 64)
			{
				tileset.insert(tileset.begin(), new Tile(sf::Vector2f(350, y), "EmptyTile"));
				tileset.insert(tileset.begin(), new Tile(sf::Vector2f(1280 - 120, y), "EmptyTile"));
			}

			cTileset.insert(cTileset.begin(), new CollideTile(sf::Vector2f(64 * 9, 100), "EmptyTile", 0));
		}

		music.openFromFile("content/music/gameloop.wav");
		music.setVolume(getGlobalMusicVolume());
		music.setLoop(true);
		music.play();
		this->player->setPosition(527, 257);
	}

	void DrawMenu(sf::RenderWindow& getWindow, sf::View view)
	{
		sf::RectangleShape sWhite(sf::Vector2f(250, 245));
		sf::RectangleShape sBlack(sf::Vector2f(240, 235));
		sf::RectangleShape _sBlack(sf::Vector2f(240, 5));

		sf::Vector2f viewCenter = view.getCenter();
		sf::Vector2f viewSize = view.getSize();
		sf::FloatRect viewBounds(viewCenter - viewSize / 2.0f, viewSize);

		sWhite.setPosition(sf::Vector2f(viewBounds.left + 50, viewBounds.top + 50));
		sBlack.setPosition(sf::Vector2f(viewBounds.left + 55, viewBounds.top + 55));
		sBlack.setFillColor(sf::Color::Black);
		_sBlack.setPosition(sf::Vector2f(viewBounds.left + 55, viewBounds.top + 90));

		getWindow.draw(sWhite);
		getWindow.draw(sBlack);
		getWindow.draw(_sBlack);

		Text* Meta = new Text("Meta menu", 28);
		Meta->Render(getWindow, sf::Vector2f(viewBounds.left + 65, viewBounds.top + 55), false);

		Text* Inventory = new Text("Inventory", 28);
		Inventory->Render(getWindow, sf::Vector2f(viewBounds.left + 65, viewBounds.top + 100), false);

		Text* Party = new Text("Party", 28);
		Party->Render(getWindow, sf::Vector2f(viewBounds.left + 65, viewBounds.top + 150), false);

		Text* Storyline = new Text("Storyline", 28);
		Storyline->Render(getWindow, sf::Vector2f(viewBounds.left + 65, viewBounds.top + 200), false);

		Text* Achievements = new Text("Achievements", 28);
		Achievements->Render(getWindow, sf::Vector2f(viewBounds.left + 65, viewBounds.top + 250), false);
	}

	// I love C++ and the fact it WONT ALLOW UNUSED VARIABLES
	void ThisFunctionAllowTheCodeToCompileDontQuestionItPlease()
	{}

	bool pressed;
	bool _isKeyPressed(sf::Keyboard::Key key)
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

	void Render(sf::RenderWindow& getWindow, sf::View view) override
	{
		sf::Vector2f viewCenter = view.getCenter();
		sf::Vector2f viewSize = view.getSize();
		sf::FloatRect viewBounds(viewCenter - viewSize / 2.0f, viewSize);

		getWindow.setView(view);
		sf::RectangleShape BackGroundColor(sf::Vector2f(getWindowSizeX(), getWindowSizeY()));
		BackGroundColor.setPosition(sf::Vector2f(viewBounds.left, viewBounds.top));
		BackGroundColor.setFillColor(sf::Color(63, 63, 113));

		sf::Texture BackGround_Texture;
		BackGround_Texture.loadFromFile("content/textures/game_background2.png");

		sf::RectangleShape BackGround(sf::Vector2f(1280, 720));
		BackGround.setTexture(&BackGround_Texture);

		sf::Texture House2_Texture;
		House2_Texture.loadFromFile("content/textures/House2.png");

		sf::RectangleShape House2_Shape(sf::Vector2f(1920, 720));
		House2_Shape.setTexture(&House2_Texture);
		House2_Shape.setPosition(2000, 2000);

		sf::Texture Darkness_T;
		Darkness_T.loadFromFile("content/textures/HouseOmniousDarkness.png");

		sf::RectangleShape Darkness(sf::Vector2f(384, 129));
		Darkness.setTexture(&Darkness_T);

		Darkness.setPosition(3174, 2368);

		getWindow.draw(BackGroundColor);
		getWindow.draw(BackGround);
		getWindow.draw(House2_Shape);

		for (Tile* tile : tileset)
		{
			tile->Render(getWindow, player);
		}

		player->Render(getWindow);

		if (isKeyHold(sf::Keyboard::C) && !shouldDraw)
		{
			shouldDraw = true;
			setPlayerMove(false);
		}
		else if (isKeyHold(sf::Keyboard::X) && shouldDraw)
		{
			shouldDraw = false;
			setPlayerMove(true);
		}

		if (drawEntityHitboxes())
		{
			float scaleX = static_cast<float>(getWindowSizeX()) / 1280.0f;
			float scaleY = static_cast<float>(getWindowSizeY()) / 720.0f;

			Text* Scaled = new Text("Scaled mouse position: " + std::to_string(scaleX) + " | " + std::to_string(scaleY), 28);
			Scaled->Render(getWindow, sf::Vector2f(viewBounds.left + 10, viewBounds.top + 170), false, true);

			Text* Real = new Text("Real mouse coordinates: " + std::to_string(sf::Mouse::getPosition(getWindow).x) + " | " + std::to_string(sf::Mouse::getPosition(getWindow).y), 28);
			Real->Render(getWindow, sf::Vector2f(viewBounds.left + 10, viewBounds.top + 200), false, true);

			Text* Relative = new Text("Relative mouse coordinates : " + std::to_string(sf::Mouse::getPosition(getWindow).x / scaleX) + " | " + std::to_string(sf::Mouse::getPosition(getWindow).y / scaleY), 28);
			Relative->Render(getWindow, sf::Vector2f(viewBounds.left + 10, viewBounds.top + 230), false, true);

			sf::Vector2f mouseWorldPos = getWindow.mapPixelToCoords(sf::Mouse::getPosition(getWindow), view);
			Text* World = new Text("World mouse coordinates: " + std::to_string(mouseWorldPos.x) + " | " + std::to_string(mouseWorldPos.y), 28);
			World->Render(getWindow, sf::Vector2f(viewBounds.left + 10, viewBounds.top + 260), false, true);
		}

		for (CollideTile* tile : cTileset)
		{
			tile->Render(getWindow, player);
		}

		if (shouldDraw && !_drawTextBox())
		{
			DrawMenu(getWindow, view);
		}

		sf::Texture UI_Texture;
		UI_Texture.loadFromFile("content/textures/UI_Test.png");

		Text* UIText = new Text("...", 50);
		Text* UIText2 = new Text("?", 50);

		sf::RectangleShape _UI(sf::Vector2f(164 * 2, 70 * 2));
		_UI.setTexture(&UI_Texture);
		_UI.setPosition(sf::Vector2f(viewBounds.left + 10, viewBounds.top + 10));

		getWindow.draw(_UI);
		if (doesCollide())
		{
			UIText2->Render(getWindow, sf::Vector2f(viewBounds.left + 72, viewBounds.top + 40), false, true);
		}
		else
		{
			UIText->Render(getWindow, sf::Vector2f(viewBounds.left + 64, viewBounds.top + 40), false, true);
		}

		getWindow.draw(Darkness);

		setViewportX(player->getPosition().x);
		setViewportY(player->getPosition().y);
	}

private:
	bool notAlreadyTriggered;
	bool shouldDraw = false;
	sf::Music music;
	Player* player;
	std::vector<Tile*> tileset;
	std::vector<CollideTile*> cTileset;
};