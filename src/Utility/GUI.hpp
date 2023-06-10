#pragma once

#include "../TheDumpsterFire.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
class Button
{
public:
	Button(std::string name, float x, float y, float length)
	{
		this->name = name;
		this->x = x;
		this->y = y;
		this->length = length;

		font.loadFromFile("content/fonts/BebasNeue-Regular.ttf");
	}

	std::string getName()
	{
		return this->name;
	}

	bool Hover(sf::Vector2i pos, sf::RectangleShape windowSize, sf::View view)
	{
		sf::RectangleShape m1(sf::Vector2f(8, 8));

		sf::Vector2f viewCenter = view.getCenter();
		sf::Vector2f viewSize = view.getSize();
		sf::FloatRect viewBounds(viewCenter - viewSize / 2.0f, viewSize);

		// Convert the relative viewport position to absolute coordinates
		float absoluteX = viewBounds.left + (pos.x / static_cast<float>(getWindowSizeX())) * viewBounds.width;
		float absoluteY = viewBounds.top + (pos.y / static_cast<float>(getWindowSizeY())) * viewBounds.height;

		m1.setPosition(sf::Vector2f(absoluteX, absoluteY));

		return windowSize.getGlobalBounds().intersects(m1.getGlobalBounds());
	}

	void Render(sf::RenderWindow& getWindow, sf::View view, void (*_setup)(void*), void* userData = nullptr)
	{
		sf::RectangleShape b1(sf::Vector2f(length, 75));
		b1.setPosition(x, y);

		if (drawEntityHitboxes())
		{
			float scaleX = static_cast<float>(getWindowSizeX()) / 1280.0f;
			float scaleY = static_cast<float>(getWindowSizeY()) / 720.0f;

			sf::Text text("Scaled mouse position : " + std::to_string(scaleX) + " | " + std::to_string(scaleY), font);

			text.setCharacterSize(20);
			text.setLetterSpacing(2);
			text.setPosition(sf::Vector2f(5, 0));
			text.setStyle(sf::Text::Regular);

			getWindow.draw(text);

			text.setString("Real mouse coordinates : " + std::to_string(sf::Mouse::getPosition(getWindow).x) + " | " + std::to_string(sf::Mouse::getPosition(getWindow).y));
			text.setPosition(sf::Vector2f(5, 24));
			getWindow.draw(text);

			text.setString("Relative mouse coordinates : " + std::to_string(sf::Mouse::getPosition(getWindow).x / scaleX) + " | " + std::to_string(sf::Mouse::getPosition(getWindow).y / scaleY));
			text.setPosition(sf::Vector2f(5, 48));
			getWindow.draw(text);
		}

		bool isHovering = Hover(sf::Mouse::getPosition(getWindow), b1, view);
		this->Render(getWindow, isHovering, view);

		if (isHovering && sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Left) != mouseState)
		{
			if (_setup != nullptr)
			{
				_setup(userData);
			}
		}

		mouseState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}

	void Render(sf::RenderWindow& getWindow, int isHovered, sf::View view)
	{
		view.getCenter();
		sf::RectangleShape b1(sf::Vector2f(length, 75));
		b1.setPosition(x, y);

		if (!isHovered)
		{
			static const sf::Color DarkGray(69, 69, 69);
			b1.setFillColor(DarkGray);
		}
		else
		{
			b1.setFillColor(sf::Color::Red);
		}

		getWindow.draw(b1);

		sf::RectangleShape b2(sf::Vector2f(length - 10, 65));
		if (!isHovered)
		{
			b2.setFillColor(sf::Color::White);
		}
		else
		{
			b2.setFillColor(sf::Color::Black);
		}

		b2.setPosition(x + 5, y + 5);
		getWindow.draw(b2);

		sf::Text text(name, font);
		text.setCharacterSize(72);
		text.setLetterSpacing(2);
		text.setStyle(sf::Text::Bold);
		if (!isHovered)
		{
			text.setFillColor(sf::Color::Black);
		}
		else
		{
			text.setFillColor(sf::Color::Red);
		}

		text.setPosition(sf::Vector2f(x + length / 2 - text.getLocalBounds().width / 2, y - 10));

		getWindow.draw(text);
	}

private:
	bool mouseState;
	std::string name;
	sf::Font font;
	float x, y, length;
	float widthPercentage, heightPercentage;
	sf::Vector2u initialWindowSize;
};

class Text
{
public:
	Text(std::string name, int fontSize)
	{
		this->name = name;
		this->fontSize = fontSize;
	}

	void Render(sf::RenderWindow& getWindow, sf::Vector2f pos, bool centered)
	{
		sf::Font font;
		font.loadFromFile("content/fonts/BebasNeue-Regular.ttf");
		std::string _name = name;
		sf::Text text(_name, font);
		text.setCharacterSize(fontSize);
		text.setLetterSpacing(2);
		text.setStyle(sf::Text::Bold);

		// for stupid reasons, _text width is always 0 no matter what so i have to do this shit
		if (!centered)
		{
			text.setPosition(pos);
		}
		else
		{
			text.setPosition(sf::Vector2f((1280 / 2) - (text.getGlobalBounds().width / 2), pos.y));
		}
		getWindow.draw(text);
	}

private:
	std::string name;
	float fontSize;
};