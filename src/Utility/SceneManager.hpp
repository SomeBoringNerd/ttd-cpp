#pragma once

#include "../Scenes/Scene.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class SceneManager
{
public:
	static void LoadScene(Scene* _scene);
	static void LoadMainMenu();
	static void LoadCredits();
	static void Update(sf::RenderWindow& getWindow, sf::View view);
	static void RefreshUI();
	static int SceneLoaded();
	static SceneManager* getInstance()
	{
		static SceneManager instance;
		return &instance;
	}

private:
	inline static int isSceneLoaded;
	inline static Scene* scene;
};