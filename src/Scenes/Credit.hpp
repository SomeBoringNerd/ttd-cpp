#pragma once

#include "../Utility/GUI.hpp"
#include "Platform/Platform.hpp"
#include "Scene.hpp"

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "../TheDumpsterFire.hpp"

class Credit : public Scene
{
public:
	Credit()
	{
		this->name = "Credit";

		back = new Button("Back", (25), 720 - 100, 300);

		Special = new Text("Special thanks to", 80);

		Zoe = new Text("@zoeyoung2563 : musics that are used in the game", 40);

		Aseprite1 = new Text("Aseprite team : making an amazing", 40);

		Aseprite2 = new Text("pixel art software and making it open source", 40);

		music.openFromFile("content/music/credit.wav");
		music.setVolume(getGlobalMusicVolume());
		music.setLoop(true);
		music.play();
	};

	void ThisFunctionAllowTheCodeToCompileDontQuestionItPlease()
	{}

	static void BackToMain(void* userData)
	{
		Credit* creditS = static_cast<Credit*>(userData);
		creditS->music.stop();
		LoadAnotherScene("MainMenu");
	}

	void Render(sf::RenderWindow& getWindow, sf::View view) override
	{
		sf::Texture BackGround_Texture;
		BackGround_Texture.loadFromFile("content/textures/mainBack.png");

		sf::RectangleShape BackGround(sf::Vector2f(1280, 720));
		BackGround.setTexture(&BackGround_Texture);

		getWindow.draw(BackGround);

		// Note : vector x position is overriden so just set it to 0 and forget about it
		Special->Render(getWindow, sf::Vector2f(0, 50), true);
		Zoe->Render(getWindow, sf::Vector2f(0, 200), true);
		Aseprite1->Render(getWindow, sf::Vector2f(0, 250), true);
		Aseprite2->Render(getWindow, sf::Vector2f(0, 290), true);

		back->Render(getWindow, view, &BackToMain, this);
	}

private:
	Button* back;
	Text* Special;
	Text* Zoe;
	Text* Aseprite1;
	Text* Aseprite2;

	sf::Music music;
	sf::RenderWindow* window;
};