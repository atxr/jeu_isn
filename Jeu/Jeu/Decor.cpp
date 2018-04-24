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

void Decor::loadMap(int const level, sf::RenderWindow &window)
{
	//Chargement de la map

	string fileDir;

	switch (level)
	{
	case 1:
		fileDir = "level1.txt";
		break;
	case 2:
		fileDir = "level2.txt";
		break;
	case 3:
		fileDir = "level3.txt";
		break;
	}

	ifstream fichierLevel(fileDir);

	if (fichierLevel)
	{
		vector<int> line;
		string buffer;

		MAP_SIZE_X = 50;
		MAP_SIZE_Y = 20;

		map.clear();

		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			for (int xPosFichier = 0; xPosFichier < 1; xPosFichier++)
			{
				getline(fichierLevel, buffer);
				istringstream iss(buffer);
				for (int i = 0; i < MAP_SIZE_X; i++)
				{
					int value;
					iss >> value;
					line.push_back(value);
				}
			}
			map.push_back(line);
			line.clear();
		}

		fichierLevel.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier level." << endl;
	}

	//Dessin

	window.draw(background);

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_Y; x++)
		{
			switch (map[y][x])
			{
			case TRANSPARANT:
				tileSprite.setTextureRect(IntRect(TRANSPARANT_X, TRANSPARANT_Y, TILE_SIZE, TILE_SIZE));
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

			case ECHELLE:
				tileSprite.setTextureRect(IntRect(ECHELLE_X, ECHELLE_Y, TILE_SIZE, TILE_SIZE));
				break;

			default:
				tileSprite.setTextureRect(IntRect(TRANSPARANT_X, TRANSPARANT_Y, TILE_SIZE, TILE_SIZE));
				break;
			}

			tileSprite.setPosition(Vector2f(x*TILE_SIZE, y*TILE_SIZE));
			window.draw(tileSprite);
		}
	}

}

void Decor::testCollision(Mouvement * mouvement)
{
	int xPerso = mouvement->position.x;
	int yPerso = mouvement->position.y;
	int numTileXGauche = floor(xPerso / TILE_SIZE);
	int numTileXDroite = floor((xPerso + 25) / TILE_SIZE); //25 = longueur du perso
	int numTileYHaut = floor(yPerso / TILE_SIZE);
	int numTileYBas = floor((yPerso + 40) / TILE_SIZE); //40 = largeur du perso

	int numTileXSuivant = numTileXDroite + 1;
	int numTileXPrecedant = numTileXGauche - 1;

	//Droite

	if (numTileXSuivant * TILE_SIZE > xPerso + 25 /*Longueur perso*/ + 2 /*Vitesse du perso*/)
	{
		mouvement->droite = true;
	}

	else if (numTileXSuivant == MAP_SIZE_X)
	{
		mouvement->maxDroite = MAP_SIZE_X * TILE_SIZE - 25;
	}

	else if (map[numTileYBas][numTileXSuivant] == TRANSPARANT)
	{
		mouvement->droite = true;
	}

	else
	{
		mouvement->maxDroite = xPerso + 0.9;
	}

	//Gauche

	if (numTileXGauche == 0)
	{
		if (xPerso - 2 > 0)
		{
			mouvement->gauche = true;
		}

		else
		{
			mouvement->maxGauche = 0;
		}
	}

	else if (map[numTileYBas][floor((xPerso - 2) / 32)] == 0)
	{
		mouvement->gauche = true;
	}

	//Haut


	//Tomber

	if (yPerso + 40 + 2 > 480)
	{
		yPerso = 480 - 40;
	}

	else if (map[floor((yPerso + 2) / 32)][numTileXGauche] == TRANSPARANT && map[floor((yPerso + 2) / 32)][numTileXDroite] == TRANSPARANT)
	{
		mouvement->bas = true;
	}
}

