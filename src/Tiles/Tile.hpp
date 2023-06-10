#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "../Entity/Player.hpp"
#include "../TheDumpsterFire.hpp"

class Tile
{
public:
	Tile(sf::Vector2f position, std::string name)
	{
		this->name = name;
		TileShape.setSize(sf::Vector2f(64, 64));
		TileShape.setPosition(position);
	};

	Tile(sf::Vector2f position, std::string name, int side)
	{
		this->name = name;
		TileShape.setSize(sf::Vector2f(64, 64));
		TileShape.setPosition(position);
		this->side = side;
	};

	void DrawHitBoxes(sf::RenderWindow& getWindow, Player* player)
	{
		sf::RectangleShape _side(sf::Vector2f(9999, 32));
		_side.setFillColor(sf::Color::Red);
		_side.setPosition(sf::Vector2f(0, TileShape.getPosition().y + 16));

		sf::RectangleShape _top(sf::Vector2f(32, 9999));
		_top.setFillColor(sf::Color::Red);
		_top.setPosition(sf::Vector2f(TileShape.getPosition().x + 16, 0));

		sf::RectangleShape topCollider(sf::Vector2f(64, 2));
		topCollider.setPosition(TileShape.getPosition());

		sf::RectangleShape bottomCollider(sf::Vector2f(64, 2));
		bottomCollider.setPosition(sf::Vector2f(TileShape.getPosition().x, TileShape.getPosition().y + 64));

		sf::RectangleShape leftCollider(sf::Vector2f(2, 64));
		leftCollider.setPosition(sf::Vector2f(TileShape.getPosition().x, TileShape.getPosition().y));

		sf::RectangleShape rightCollider(sf::Vector2f(2, 64));
		rightCollider.setPosition(sf::Vector2f(TileShape.getPosition().x + 64, TileShape.getPosition().y));

		sf::FloatRect playerHitbox = player->getShape().getGlobalBounds();

		if (playerHitbox.intersects(_top.getGlobalBounds()))
		{
			_top.setFillColor(sf::Color::Yellow);
		}
		if (playerHitbox.intersects(_side.getGlobalBounds()))
		{
			_side.setFillColor(sf::Color::Yellow);
		}

		getWindow.draw(_side);
		getWindow.draw(_top);
	}

	void Render(sf::RenderWindow& getWindow, Player* player)
	{
		sf::Texture tileTexture;
		tileTexture.loadFromFile("content/textures/tiles/" + name + ".png");

		TileShape.setTexture(&tileTexture);

		sf::RectangleShape _side(sf::Vector2f(9999, 32));
		_side.setFillColor(sf::Color::Red);
		_side.setPosition(sf::Vector2f(0, TileShape.getPosition().y + 16));

		sf::RectangleShape _top(sf::Vector2f(32, 9999));
		_top.setFillColor(sf::Color::Red);
		_top.setPosition(sf::Vector2f(TileShape.getPosition().x + 16, 0));

		sf::RectangleShape topCollider(sf::Vector2f(64, 2));
		topCollider.setPosition(TileShape.getPosition());

		sf::RectangleShape bottomCollider(sf::Vector2f(64, 2));
		bottomCollider.setPosition(sf::Vector2f(TileShape.getPosition().x, TileShape.getPosition().y + 64));

		sf::RectangleShape leftCollider(sf::Vector2f(2, 64));
		leftCollider.setPosition(sf::Vector2f(TileShape.getPosition().x, TileShape.getPosition().y));

		sf::RectangleShape rightCollider(sf::Vector2f(2, 64));
		rightCollider.setPosition(sf::Vector2f(TileShape.getPosition().x + 64, TileShape.getPosition().y));

		sf::FloatRect playerHitbox = player->getShape().getGlobalBounds();

		if (playerHitbox.intersects(topCollider.getGlobalBounds()))
		{
			topCollider.setFillColor(sf::Color::Blue);
		}
		if (playerHitbox.intersects(bottomCollider.getGlobalBounds()))
		{
			bottomCollider.setFillColor(sf::Color::Blue);
		}
		if (playerHitbox.intersects(leftCollider.getGlobalBounds()))
		{
			leftCollider.setFillColor(sf::Color::Blue);
		}
		if (playerHitbox.intersects(rightCollider.getGlobalBounds()))
		{
			rightCollider.setFillColor(sf::Color::Blue);
		}

		// so the deal with those _side and _top variable is that the player can never collide with the two of them at once
		// so if the player collide with _side, we only treat left and right collisions
		// if the player collide with _top, we only treat top and bottom
		// this allow proper collisions with terrain
		// in a way that dont create weird issues where the player
		// is stuck when colliding with terrain in some ways.
		// I hate programming, I hate myself and i need some fucking coffee
		if (playerHitbox.intersects(_top.getGlobalBounds()))
		{
			_top.setFillColor(sf::Color::Yellow);
			if (playerHitbox.intersects(topCollider.getGlobalBounds()))
			{
				// Handle collision with top collider
				player->setPosition(player->getPosition().x, topCollider.getPosition().y - playerHitbox.height);
			}
			if (playerHitbox.intersects(bottomCollider.getGlobalBounds()))
			{
				// Handle collision with bottom collider
				player->setPosition(player->getPosition().x, bottomCollider.getPosition().y);
			}
		}
		if (playerHitbox.intersects(_side.getGlobalBounds()))
		{
			_side.setFillColor(sf::Color::Yellow);
			if (playerHitbox.intersects(leftCollider.getGlobalBounds()) && player->getVelocity().x >= 0)
			{
				// Handle collision with left collider
				player->setPosition(leftCollider.getPosition().x - playerHitbox.width, player->getPosition().y);
			}
			if (playerHitbox.intersects(rightCollider.getGlobalBounds()) && player->getVelocity().x <= 0)
			{
				// Handle collision with right collider
				player->setPosition(rightCollider.getPosition().x, player->getPosition().y);
			}
		}

		getWindow.draw(TileShape);

		if (drawEntityHitboxes())
		{
			getWindow.draw(topCollider);
			getWindow.draw(bottomCollider);
			getWindow.draw(rightCollider);
			getWindow.draw(leftCollider);
		}
	}

	sf::RectangleShape getShape()
	{
		return TileShape;
	}

private:
	int side = 0;
	std::string name;
	sf::RectangleShape TileShape;
};