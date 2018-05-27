#include "Input.h"
#include <iostream>

using namespace std;
using namespace sf;

Input::Input()
{
}

Input::Input(sf::RenderWindow * window) : window(window)
{
	bouton.droite = bouton.gauche = bouton.haut = bouton.bas = bouton.attaque = bouton.pause = rejouer = false;
}


Input::~Input()
{
}

bool Input::getStatut(int id)
{
	bool value;
	switch (id)
	{
	case DROITE:
		value = bouton.droite;
		break;

	case GAUCHE:
		value = bouton.gauche;
		break;

	case HAUT:
		value = bouton.haut;
		break;

	case BAS:
		value = bouton.bas;
		break;

	case ATTAQUE:
		value = bouton.attaque;
		break;

	case PAUSE:
		value = bouton.pause;
		break;
	}
	return value;
}

void Input::setBouton(int id, bool value)
{
	switch (id)
	{
	case DROITE:
		bouton.droite = value;
		break;

	case GAUCHE:
		bouton.gauche = value;
		break;

	case HAUT:
		bouton.haut = value;
		break;

	case BAS:
		bouton.bas = value;
		break;

	case ATTAQUE:
		bouton.attaque = value;
		break;

	case PAUSE:
		bouton.pause = value;
		break;
	}
}

void Input::update()
{
	rejouer = false;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{

			//Fenetre ferrmée
		case Event::Closed:
			window->close();
			break;

			//Touche pressée
		case Event::KeyPressed:
			switch (event.key.code)
			{
			case Keyboard::Right:
				setBouton(DROITE, true);
				direction = true;
				break;

			case Keyboard::Left:
				setBouton(GAUCHE, true);
				direction = false;
				break;

			case Keyboard::Up:
				setBouton(HAUT, true);
				break;

			case Keyboard::Down:
				setBouton(BAS, true);
				break;

			case Keyboard::Space:
				setBouton(ATTAQUE, true);
				break;

			case Keyboard::Escape:
				setBouton(PAUSE, true);
				break;

			default:
				setBouton(HAUT, false);
				break;
			}

			rejouer = true;

			break;

			//Touche relachée
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Right:
				setBouton(DROITE, false);
				break;

			case Keyboard::Left:
				setBouton(GAUCHE, false);
				break;

			case Keyboard::Up:
				setBouton(HAUT, false);
				break;

			case Keyboard::Down:
				setBouton(BAS, false);
				break;

			case Keyboard::Space:
				setBouton(ATTAQUE, false);
				break;

			case Keyboard::Escape:
				setBouton(PAUSE, false);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

bool Input::getDirection()
{
	return direction;
}

bool Input::getRejouer()
{
	return rejouer;
}
