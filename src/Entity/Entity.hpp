#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

class Entity
{
public:
	explicit Entity(int health, int def, int atk, std::string name, int FLAG)
	{
		position = sf::Vector2f(0, 0);
		this->health = health;
		this->def = def;
		this->atk = atk;
		this->name = name;
		this->FLAG = FLAG;
		std::cout << "Constructor has been called for entity " << name << std::endl;
	}

	void Render(sf::RenderWindow& getWindow)
	{
		if (!hasStartedRanOnce)
		{
			Start();
			hasStartedRanOnce = 1;
		}
		Update(getWindow);
	};

	virtual void Update(sf::RenderWindow&) {};
	virtual void Start() {};

	int getHealth()
	{
		return health;
	}

	int getAttack()
	{
		return atk;
	}

	int getDefense()
	{
		return def;
	}

	int getFlag()
	{
		return FLAG;
	}

	sf::Vector2f getPosition()
	{
		return position;
	}

	void setPosition(float x, float y)
	{
		position = sf::Vector2f(x, y);
	}

private:
	sf::Vector2f position;
	std::string name;
	int health, def, atk, FLAG, hasStartedRanOnce = 0;
};