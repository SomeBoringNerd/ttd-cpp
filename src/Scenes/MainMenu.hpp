#pragma once

#include "../Utility/GUI.hpp"
#include "Credit.hpp"
#include "Platform/Platform.hpp"
#include "Scene.hpp"

#include <iostream>
#include <stdlib.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "../TheDumpsterFire.hpp"

class MainMenu : public Scene
{
public:
	static MainMenu* currentInstance;
	MainMenu()
	{
		this->name = "MainMenu";

		Play = new Button("Play", ((1280 / 2) - 300), 250, 600);
		_Credit = new Button("Credits", ((1280 / 2) - 300), 350, 600);
		Other = new Button("Other projects", ((1280 / 2) - 300), 450, 600);
		Option = new Button("Options", ((1280 / 2) - 300), 550, 290);
		Quit = new Button("Quit", ((1280 / 2) + 10), 550, 290);

		setViewportX(641);
		setViewportY(361);

		GameName = new Text("Through The Dark", 80);

		music.openFromFile("content/music/main.wav");
		music.setVolume(getGlobalMusicVolume());
		music.setLoop(true);
		music.play();
	};

	// I love C++ and the fact it WONT ALLOW UNUSED VARIABLES
	void ThisFunctionAllowTheCodeToCompileDontQuestionItPlease()
	{}

	static void OptionsButton(void* userData)
	{
		MainMenu* mainMenu = static_cast<MainMenu*>(userData);
		mainMenu->ThisFunctionAllowTheCodeToCompileDontQuestionItPlease();
	}

	static void Exit(void* userData)
	{
		MainMenu* mainMenu = static_cast<MainMenu*>(userData);
		mainMenu->window->close();
	}

	static void OtherGames(void* userData)
	{
		MainMenu* mainMenu = static_cast<MainMenu*>(userData);
		// userData need to be used, so we call empty function so that fucking thing can compile
		mainMenu->ThisFunctionAllowTheCodeToCompileDontQuestionItPlease();

		std::string url = "https://someboringnerd.xyz/projects";

#ifdef _WIN32
		std::string command = "start " + url;
		system(command.c_str());
#elif __linux__
		std::string command = "xdg-open " + url + " >/dev/null 2>&1";

		system(command.c_str());
#elif __APPLE__
		// for macOS
		std::string command = "open " + url;
		system(command.c_str());
#else
		cout << "Unsupported OS." << endl;
#endif
	}

	static void Credits(void* userData)
	{
		MainMenu* mainMenu = static_cast<MainMenu*>(userData);
		mainMenu->music.stop();
		LoadAnotherScene("Credits");
	}

	static void PlayButton(void* userData)
	{
		MainMenu* mainMenu = static_cast<MainMenu*>(userData);
		mainMenu->music.stop();
		LoadAnotherScene("Walker");
	}

	void Render(sf::RenderWindow& getWindow, sf::View view) override
	{
		window = &getWindow;
		sf::Texture BackGround_Texture;
		BackGround_Texture.loadFromFile("content/textures/mainBack.png");

		sf::RectangleShape BackGround(sf::Vector2f(1280, 720));
		BackGround.setTexture(&BackGround_Texture);

		getWindow.draw(BackGround);

		GameName->Render(getWindow, sf::Vector2f(0, 50), true);

		Play->Render(getWindow, view, &PlayButton, this);
		_Credit->Render(getWindow, view, &Credits, this);
		Other->Render(getWindow, view, &OtherGames, this);
		Option->Render(getWindow, view, &OptionsButton, this);
		Quit->Render(getWindow, view, &Exit, this);
	}

private:
	sf::Music music;
	sf::RenderWindow* window;
	Button *Quit, *Play, *Option, *_Credit, *Other;
	Text* GameName;
};