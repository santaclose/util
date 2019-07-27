#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#define BLOCK_SIZE 94

using namespace std;

int main(int argc, char** argv)
{
  	ifstream ifs(argv[1]);
	string fileContents((istreambuf_iterator<char>(ifs)),
                 istreambuf_iterator<char>());

	int lineCount = 1;
	int rowLength = 0;

	for (int i = 0; i < fileContents.length(); i++)
	{
		if (fileContents[i] == '\n' && i != fileContents.length() - 1)
		{
			lineCount++;
		}
		
		if (lineCount == 1 && fileContents[i] != '\n')
		{
			rowLength++;
		}
	}

	cout << lineCount << endl << rowLength << endl;


	sf::Image pacmanImage, ghostImage, wallImage, foodImage;
	if (!wallImage.loadFromFile("w.png") || !foodImage.loadFromFile("f.png") || !ghostImage.loadFromFile("g.png") || !pacmanImage.loadFromFile("p.png"))
		return -1;

	sf::Image imgOutput;
	imgOutput.create(rowLength * BLOCK_SIZE, lineCount * BLOCK_SIZE, sf::Color::White);


	int currentBlockX = 0;
	int currentBlockY = 0;
	for (int i = 0; i < fileContents.length(); i++)
	{
		if (fileContents[i] == '\n'){
			currentBlockY++;
			currentBlockX = 0;
			continue;
		}

		sf::Image* img;
		switch(fileContents[i])
		{
			case ' ':
				currentBlockX++;
				continue; // don't draw anything
				break;
			case 'G':
				img = &ghostImage;
				break;
			case 'P':
				img = &pacmanImage;
				break;
			case '.':
				img = &foodImage;
				break;
			case '%':
				img = &wallImage;
				break;
		}


		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			for (int k = 0; k < BLOCK_SIZE; k++)
			{
				/*if (j == 0 || k == 0 || j == BLOCK_SIZE - 1 || k == BLOCK_SIZE - 1) // grid
				{
					imgOutput.setPixel(currentBlockX * BLOCK_SIZE + k, currentBlockY * BLOCK_SIZE + j, sf::Color::Black);
					continue;
				}*/
				//imgOutput.setPixel(currentBlockX * BLOCK_SIZE + k, currentBlockY * BLOCK_SIZE + j, sf::Color::Green);
				imgOutput.setPixel(currentBlockX * BLOCK_SIZE + k, currentBlockY * BLOCK_SIZE + j, img->getPixel(k, j));
			}
		}

		currentBlockX++;
	}


	if (!imgOutput.saveToFile("result.png"))
    	return -1;
}