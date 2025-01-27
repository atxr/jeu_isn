#include "Ennemi.h"



Ennemi::Ennemi()
{
}

Ennemi::Ennemi(int x, int y) : Perso(x,y), occupe(false), pause(true)
{
	for (int i = 0; i < 6; i++)
	{
		stringstream ss;
		ss << "graphics/ennemi/" << i << ".png";
		texturePerso.push_back(new Texture);
		if (!texturePerso[i]->loadFromFile(ss.str()))
		{
			cout << ss.str();
		}
	}

	setTexture(*texturePerso[0]);
	scale(0.026f, 0.026f);


	m_vie = 3;
	nbDegat = 1;
}

void Ennemi::updatePerso(Decor *decor, Vector2f positionHero)
{
	//SPRITE

	if (positionHero.x < getPosition().x)
	{
		setTexture(*texturePerso[3]);
	}

	else
	{
		setTexture(*texturePerso[0]);
	}

	//TEST DE GRAVITE

	Collision * test = new Collision;

	test->longueur = 25;
	test->hauteur = 40;
	test->position = getPosition();
	test->vitesse = 2;

	test->vitesse = GRAVITE;

	decor->testCollisionBas(test);

	if (test->statut)
	{
		setPosition(getPosition() + Vector2f(0, GRAVITE));
	}

	else
	{
		setPosition(Vector2f(getPosition().x, test->valeur));
	}

	test->position = getPosition();
	test->statut = false;
	test->valeur = 0;

	//ACTION A FAIRE

	if (decor->testVisee(getPosition(), positionHero))
	{
		if (!pauseFeu)
		{
			chronoFeu.restart();
			pauseFeu = true;
		}

		else if (chronoFeu.getElapsedTime().asSeconds() > 0.5)
		{
			feu = true;
			chronoFeu.restart();
		}
	}

	else 
	{
		pauseFeu = false;
		feu = false;
	}

	if (feu && chronoFeu.getElapsedTime().asSeconds() > ((rand() % 200) + 0.5) / 100.f)
	{
		if (1)
		{
			if (positionHero.x >= getPosition().x)
			{
				direction = true;
			}

			else
			{
				direction = false;
			}

			tabBalle.push_back(new Balle(getPosition(), direction));

			feu = false;
		}
	}

	else
	{
		if (pause)
		{
			if (chronoAction.getElapsedTime().asSeconds() > rand() % 4 + 3 /*Nombre aleatoire entre 4 et 6*/)
			{
				pause = false;
			}
		}

		else if (!occupe)
		{
			action = rand() % 3;
			if (action == 3)
			{
				action = 0;
			}
			occupe = true;
			chronoAction.restart();
		}

		else
		{
			switch (action)
			{
			case AVANCER_DROITE:
				setTexture(*texturePerso[static_cast<int>(sprite.getElapsedTime().asSeconds() * 6) % 3]);

				decor->testCollisionDroite(test);

				if (test->statut)
				{
					setPosition(getPosition() + Vector2f(2, 0));
				}
				else
				{
					setPosition(Vector2f(test->valeur, getPosition().y)); //On colle le perso a la paroi
					occupe = false;
					pause = true;
				}

				break;

			case AVANCER_GAUCHE:
				setTexture(*texturePerso[(static_cast<int>(sprite.getElapsedTime().asSeconds() * 6) % 3) + 3]);

				decor->testCollisionGauche(test);

				if (test->statut)
				{
					setPosition(getPosition() - Vector2f(2, 0));
				}
				else
				{
					setPosition(Vector2f(test->valeur, getPosition().y)); //On colle le perso a la paroi
					occupe = false;
					pause = true;
				}

				break;
			default:
				break;
			}


			if (chronoAction.getElapsedTime().asSeconds() > 0.5)
			{
				occupe = false;
				pause = true;
				chronoAction.restart();
			}

		}
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

		if (!tabBalle[i]->update() || !test->statut)
		{
			tabBalle.erase(tabBalle.begin() + i);
		}
	}
}


Ennemi::~Ennemi()
{
}
