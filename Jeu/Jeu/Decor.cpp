#include "Decor.h"


Decor::Decor()
{
	if (!tileTexture.loadFromFile("graphics/tile.png"))
	{
		cerr << "Erreur, texture introuvable." << endl;
	}
	else
	{
		tileSprite.setTexture(tileTexture);
	}

	if (!backgroundTexture.loadFromFile("graphics/background.png"))
	{
		cerr << "Erreur, texture introuvable." << endl;
	}
	else
	{
		background.setTexture(backgroundTexture);
	}
}

Decor::~Decor()
{
}

int Decor::getTILE_SIZE()
{
	return TILE_SIZE;
}

int Decor::getMapSizeX()
{
	return MAP_SIZE_X;
}

int Decor::getMapSizeY()
{
	return MAP_SIZE_Y;
}

void Decor::getMap(vector<vector<int>>* mapPointeur)
{
	mapPointeur = &map;
}

void Decor::loadMap(sf::RenderWindow *window)
{
	//Chargement de la map

	string fileDirMap = "level1map";;
	string fileDirPerso;

	ifstream fichierLevelMap(fileDirMap);

	if (fichierLevelMap)
	{
		vector<int> line;
		string buffer;

		MAP_SIZE_X = 300;
		MAP_SIZE_Y = 15;

		map.clear();

		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			getline(fichierLevelMap, buffer);
			istringstream iss(buffer);
			for (int i = 0; i < MAP_SIZE_X; i++)
			{
				int value;
				iss >> value;
				line.push_back(value);
			}
			map.push_back(line);
			line.clear();
		}

		fichierLevelMap.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier level." << endl;
	}



	//Dessin

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			switch (map[y][x])
			{
			case TRANSPARANT:
				tileSprite.setTextureRect(IntRect(TRANSPARANT_X, TRANSPARANT_Y, TILE_SIZE, TILE_SIZE));
				break;

			case ECHELLE:
				tileSprite.setTextureRect(IntRect(ECHELLE_X, ECHELLE_Y, TILE_SIZE, TILE_SIZE));
				break;

			case TERRE:
				tileSprite.setTextureRect(IntRect(TERRE_X, TERRE_ET_ROCHE_Y, TILE_SIZE, TILE_SIZE));
				break;

			case TERRE_GAZON:
				tileSprite.setTextureRect(IntRect(TERRE_GAZON_X, TERRE_ET_ROCHE_Y, TILE_SIZE, TILE_SIZE));
				break;

			case ROCHE:
				tileSprite.setTextureRect(IntRect(ROCHE_X, TERRE_ET_ROCHE_Y, TILE_SIZE, TILE_SIZE));
				break;

			case ROCHE_GAZON:
				tileSprite.setTextureRect(IntRect(ROCHE_GAZON_X, TERRE_ET_ROCHE_Y, TILE_SIZE, TILE_SIZE));
				break;

			default:
				tileSprite.setTextureRect(IntRect(TRANSPARANT_X, TRANSPARANT_Y, TILE_SIZE, TILE_SIZE));
				break;
			}

			tileSprite.setPosition(Vector2f(x*TILE_SIZE, y*TILE_SIZE));
			window->draw(tileSprite);
		}
	}

}

void Decor::testCollisionDroite(Collision * collision)
{
	int x = collision->position.x;
	int y = collision->position.y;

	int numTileXSuivant = floor((x + collision->longueur) / TILE_SIZE) + 1;
	int numTileYHaut = floor(y / TILE_SIZE);
	int numTileYBas = floor((y + collision->hauteur) / TILE_SIZE);

	if (numTileXSuivant * TILE_SIZE > x + collision->longueur + collision->vitesse)
	{
		collision->statut = true;
	}

	else if (numTileXSuivant == MAP_SIZE_X)
	{
		collision->valeur = MAP_SIZE_X * TILE_SIZE - 25;
	}

	else if (map[numTileYBas][numTileXSuivant] <= 1 && (map[numTileYHaut][numTileXSuivant]) <= 1)
	{
		collision->statut = true;
	}

	else
	{
		collision->valeur = x + 0.9;
	}
}

void Decor::testCollisionHaut(Collision * collision)
{
	int x = collision->position.x;
	int y = collision->position.y;

	int numTileXGauche = floor(x / TILE_SIZE);
	int numTileXDroite = floor((x + 25) / TILE_SIZE); //25 = longueur du perso
	int numTileYHaut = floor(y / TILE_SIZE);
	int numTileYPrecedant = numTileYHaut - 1;

	if (y - collision->vitesse <= 0)
	{
		collision->valeur = 0;
	}

	else if (y - collision->vitesse < numTileYHaut * TILE_SIZE && (map[numTileYPrecedant][numTileXGauche] > 1 || map[numTileYPrecedant][numTileXDroite] > 1))
	{
		collision->valeur = numTileYHaut * TILE_SIZE;
	}

	else
	{
		collision->statut = true;
	}
}

void Decor::testCollisionBas(Collision * collision)
{
	int x = collision->position.x;
	int y = collision->position.y;

	int numTileXGauche = floor(x / TILE_SIZE);
	int numTileXDroite = floor((x + collision->longueur) / TILE_SIZE);
	int numTileYSuivant = floor((y + collision->hauteur) / TILE_SIZE) + 1;

	if (y + collision->hauteur + collision->vitesse >= 480)
	{
		collision->valeur = 480 - (collision->hauteur + 0.1);
	}

	else if (y + collision->hauteur + collision->vitesse >= numTileYSuivant * TILE_SIZE)
	{
		if (map[numTileYSuivant][numTileXGauche] > 1 || map[numTileYSuivant][numTileXDroite] > 1)
		{
			collision->valeur = numTileYSuivant * TILE_SIZE - (collision->hauteur + 0.1);
		}

		else
		{
			collision->statut = true;
		}
	}

	else
	{
		collision->statut = true;
	}
}

void Decor::testCollisionGauche(Collision * collision)
{
	int x = collision->position.x;
	int y = collision->position.y;

	int numTileXGauche = floor(x / TILE_SIZE);
	int numTileYHaut = floor(y / TILE_SIZE);
	int numTileYBas = floor((y + collision->hauteur) / TILE_SIZE);

	if (numTileXGauche == 0)
	{
		if (x - collision->vitesse > 0)
		{
			collision->statut = true;
		}

		else
		{
			collision->valeur = 0;
		}
	}

	else if (map[numTileYBas][floor((x - collision->vitesse) / TILE_SIZE)] <= 1 && map[numTileYHaut][floor((x - collision->vitesse) / TILE_SIZE)] <= 1)
	{
		collision->statut = true;
	}

	else
	{
		collision->valeur = x;
	}
}

bool Decor::getEchelle(Vector2f const position)
{
	if (map[floor((position.y + 40) / TILE_SIZE)][floor(position.x / TILE_SIZE)] == ECHELLE || map[floor((position.y + 40) / TILE_SIZE)][floor((position.x + 25) / TILE_SIZE)] == ECHELLE)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Decor::testVisee(Vector2f position, Vector2f positionHero)
{
	bool test(false);
	bool fin(false);
	int dir;

	if (position.x < positionHero.x)
	{
		dir = 1;
	}

	else
	{
		dir = -1;
	}

	int numTileY = floor((position.y + 20) / TILE_SIZE);
	int numTileXHero = floor(positionHero.x / TILE_SIZE);
	int numTileX = floor(position.x / TILE_SIZE);

	if (numTileX == numTileXHero)
	{
		test = true;
	}

	else
	{
		int i = 0;

		while (!fin)
		{
			test = (map[numTileY][numTileX + i * dir] <= 1);

			if (numTileX + (i + 1) * dir == numTileXHero || !test)
			{
				fin = true;
			}

			else
			{
				i++;
			}
		}
	}

	return (positionHero.y >= position.y - 80 /*Hauteur*/ && positionHero.y <= position.y + 80 && fabs(position.x - positionHero.x) < 500 && test);
}
