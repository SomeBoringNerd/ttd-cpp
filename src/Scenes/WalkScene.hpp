#pragma once

#include "../Utility/GUI.hpp"
#include "Platform/Platform.hpp"
#include "Scene.hpp"

#include <iostream>

#include "../Entity/Player.hpp"
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

		if (true)
		{
			for (int x = 0; x < (64 * 15); x += 64)
			{
				tileset.insert(tileset.begin(), new Tile(sf::Vector2f(x, 720 - 48), "EmptyTile", 1));
				tileset.insert(tileset.begin(), new Tile(sf::Vector2f(x, 100), "EmptyTile", 1));
			}

			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(80, 3 * 64), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(80, 4 * 64), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(80, 5 * 64), "EmptyTile", 1));

			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(10 * 64 + 16, 124), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(11 * 64, 124), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(12 * 64 - 16, 124), "EmptyTile", 1));

			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(15 * 64, 80), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(16 * 64, 100), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(17 * 64, 100), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(18 * 64, 100), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(19 * 64, 100), "EmptyTile", 1));

			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(15 * 64, 720 - 48), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(16 * 64, 720 - 48), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(17 * 64, 720 - 48), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(18 * 64, 720 - 48), "EmptyTile", 1));
			tileset.insert(tileset.begin(), new Tile(sf::Vector2f(19 * 64, 720 - 48), "EmptyTile", 1));

			for (int y = 0; y < 720; y += 64)
			{
				tileset.insert(tileset.begin(), new Tile(sf::Vector2f(-10, y), "EmptyTile"));
				tileset.insert(tileset.begin(), new Tile(sf::Vector2f(1280 - 58, y), "EmptyTile"));
			}
		}

		music.openFromFile("content/music/gameloop.wav");
		music.setVolume(getGlobalMusicVolume());
		music.setLoop(true);
		music.play();
	}

	void DrawMenu(sf::RenderWindow& getWindow)
	{
		sf::RectangleShape sWhite(sf::Vector2f(250, 400));
		sf::RectangleShape sBlack(sf::Vector2f(240, 390));
		sf::RectangleShape _sBlack(sf::Vector2f(240, 5));

		sWhite.setPosition(sf::Vector2f(50, 50));
		sBlack.setPosition(sf::Vector2f(55, 55));
		sBlack.setFillColor(sf::Color::Black);
		_sBlack.setPosition(sf::Vector2f(55, 90));

		getWindow.draw(sWhite);
		getWindow.draw(sBlack);
		getWindow.draw(_sBlack);

		Text* Meta = new Text("Meta menu", 28);
		Meta->Render(getWindow, sf::Vector2f(65, 55), false);

		Text* Inventory = new Text("Inventory", 28);
		Inventory->Render(getWindow, sf::Vector2f(65, 100), false);

		Text* Party = new Text("Party", 28);
		Party->Render(getWindow, sf::Vector2f(65, 150), false);

		Text* Storyline = new Text("Storyline", 28);
		Storyline->Render(getWindow, sf::Vector2f(65, 200), false);

		Text* Achievements = new Text("Achievements", 28);
		Achievements->Render(getWindow, sf::Vector2f(65, 250), false);
	}

	void Render(sf::RenderWindow& getWindow, sf::View view) override
	{
		view.getCenter();
		sf::RectangleShape BackGroundColor(sf::Vector2f(5000, 5000));
		BackGroundColor.setPosition(sf::Vector2f(-2000, -2000));
		BackGroundColor.setFillColor(sf::Color(63, 63, 113));

		sf::Texture BackGround_Texture;
		BackGround_Texture.loadFromFile("content/textures/game_background2.png");

		sf::RectangleShape BackGround(sf::Vector2f(1280, 720));
		BackGround.setTexture(&BackGround_Texture);

		getWindow.draw(BackGroundColor);
		getWindow.draw(BackGround);

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

		if (shouldDraw)
		{
			DrawMenu(getWindow);
		}
	}

private:
	bool shouldDraw = false;
	sf::Music music;
	Player* player;
	std::vector<Tile*> tileset;
};