#include "Hero.h"



Hero::Hero() : Perso::Perso()
{
}

Hero::Hero(int x, int y) : Perso(x,y)
{
	for (int i = 0; i < 7; i++)
	{
		stringstream ss;
		ss << "graphics/hero/" << i << ".png";
		texturePerso.push_back(new Texture);
		if (!texturePerso[i]->loadFromFile(ss.str()))
		{
			cout << ss.str();
		}
	}

	scale(0.026f, 0.026f);

	m_vie = 3;
	nbDegat = 2;

	sol = saut = false;
	
	direction = true ;
}


Hero::~Hero()
{
}



void Hero::updatePerso(Input *input, Decor *decor, Time time)
{
	setTexture(*texturePerso[0]);

	bouton.droite = input->getStatut(DROITE);
	bouton.gauche = input->getStatut(GAUCHE);
	bouton.haut = input->getStatut(HAUT);
	bouton.bas = input->getStatut(BAS);
	bouton.attaque = input->getStatut(ATTAQUE);
	bouton.pause = input->getStatut(PAUSE);

	direction = input->getDirection();

	Collision * test = new Collision;

	test->longueur = 27;
	test->hauteur = 40;
	test->position = getPosition();
	test->vitesse = 3;

	if (bouton.droite) //DROITE
	{
		setTexture(*texturePerso[(static_cast<int>(sprite.getElapsedTime().asSeconds() * 6) % 3) + 1]);

		decor->testCollisionDroite(test);

		if (test->statut)
		{
			setPosition(getPosition() + Vector2f(2, 0));
		}
		else
		{
			setPosition(Vector2f(test->valeur, getPosition().y)); //On colle le perso a la paroi
		}

		test->position = getPosition();
		test->statut = false;
		test->valeur = 0;
	}

	if (bouton.gauche) //GAUCHE
	{
		setTexture(*texturePerso[(static_cast<int>(sprite.getElapsedTime().asSeconds() * 6) % 3) + 4]);

		decor->testCollisionGauche(test);

		if (test->statut)
		{
			setPosition(getPosition() - Vector2f(2, 0));
		}

		else
		{
			setPosition(Vector2f(test->valeur, getPosition().y));
		}

		test->position = getPosition();
		test->statut = false;
		test->valeur = 0;
	}

	//TOMBER

	if (decor->getEchelle(getPosition()))
	{
		saut = false;
	}

	else
	{
		test->vitesse = GRAVITE;
		test->position = getPosition() + Vector2f(4, 0);
		test->longueur = 23; //Longeur du perso au niveau des pieds
		decor->testCollisionBas(test);

		if (test->statut)
		{
			setPosition(getPosition() + Vector2f(0, GRAVITE));
			sol = false;
		}

		else
		{
			setPosition(Vector2f(getPosition().x, test->valeur));
			sol = true;
		}

		test->position = getPosition();
		test->longueur = 25;
		test->statut = false;
		test->valeur = 0;
	}


	//SAUTER

	if (bouton.haut)
	{
		if (decor->getEchelle(getPosition()))
		{
			test->vitesse = 5;
			decor->testCollisionHaut(test);

			if (test->statut)
			{
				setPosition(getPosition() - Vector2f(0, test->vitesse));
			}

			else
			{
				setPosition(Vector2f(getPosition().x, test->valeur));
			}

			test->position = getPosition();
			test->statut = false;
			test->valeur = 0;

		}

		else if (sol)
		{
			saut = true;
			debutSaut = time;
		}
	}

	if (saut)
	{
		if (time.asSeconds() - debutSaut.asSeconds() < 0.5)
		{
			test->vitesse = 11 - 22 * (time.asSeconds() - debutSaut.asSeconds());
			decor->testCollisionHaut(test);

			if (test->statut)
			{
				setPosition(getPosition() - Vector2f(0, test->vitesse));
			}

			else
			{
				saut = false;
			}

			test->position = getPosition();
			test->statut = false;
			test->valeur = 0;
		}

		else
		{
			saut = false;
		}
	}

	if (bouton.bas) //SE BAISSER
	{
		if (decor->getEchelle(getPosition()))
		{
			test->vitesse = 4;
			decor->testCollisionBas(test);

			if (test->statut)
			{
				setPosition(getPosition() + Vector2f(0, test->vitesse));
			}

			else
			{
				setPosition(Vector2f(getPosition().x, test->valeur));
			}

			test->position = getPosition();
			test->statut = false;
			test->valeur = 0;
		}
	}

	if (bouton.attaque && !feu)
	{
		feu = true;
		debutFeu = time;
		tabBalle.push_back(new Balle(getPosition(), direction));
	}

	if (time.asMilliseconds() - debutFeu.asMilliseconds() > 500)
	{
		feu = false;
	}

	for (int i = 0; i < tabBalle.size(); i++)
	{
		tabBalle[i]->getCollision(test);

		if (direction)
		{
			decor->testCollisionDroite(test);
		}

		else
		{
			decor->testCollisionGauche(test);
		}

		bool testBalle = tabBalle[i]->update();

		if (!testBalle || !test->statut)
		{
			tabBalle.erase(tabBalle.begin() + i);
		}
	}
}
