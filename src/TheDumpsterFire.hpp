#pragma once

/*************************************************************************************************************************/
/*

Context for that header : In C++ there's this fucking thing called "Circular declaration"

tl:dr : C++ is dumb, it took me 3 hours to find this stupid solution. Find implementation in main.cpp

in better term : any function / variables that need to be in the global scope for any reason will be declared and / or defined here

**************************************************************************************************************************/
#include <string>

void LoadAnotherScene(std::string name);

int getGlobalMusicVolume();
int getWindowState();

int getWindowSizeX();
int getWindowSizeY();

void setViewportX(int x);
void setViewportY(int y);

bool drawEntityHitboxes();
bool isKeyPressed(sf::Keyboard::Key);
bool isKeyHold(sf::Keyboard::Key);
void setPlayerMove(bool newVal);
void ExecuteOrder66(int);
bool canPlayerMove();

void RenderTextBox(sf::RenderWindow&, sf::View);
void setID(int);

bool _orderExecuted();
bool _drawTextBox();
bool doesCollide();

void setOrderExecuted(bool);
void setDrawTextBox(bool);
void setCollide(bool);

int teleportFlag();
void setTeleportFlag(int);