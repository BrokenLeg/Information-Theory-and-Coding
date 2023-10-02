#include <iostream>
#include <fstream>
#include <Windows.h>

//TODO: global
static uint32_t statistics[256];
static uint32_t totalSize;

//TODO: cmd errors
#define INCORRECT_FORMAT 1
#define FILE_NOT_GIVEN 2

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 5)
	{
		std::cout << "Usage: entrop --file <filename> OR entrop --input" << std::endl;
		return INCORRECT_FORMAT;
	}

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//TODO: strings comparison
	if (strcmp(argv[1], "--file") == 0)
	{
		if (argc != 4)
		{
			std::cout << "usage: entrop --file <filename> <output>" << std::endl;
			return FILE_NOT_GIVEN;
		}

		//TODO: correct file
		std::ifstream file(argv[2], std::ios::in | std::ios::binary);
		uint8_t currentByte;

		//CHECK: correct reading, more efficient reading
		while (file)
		{
			file >> currentByte;

			if (file.eof())
			{
				break;
			}

			statistics[currentByte]++;
			totalSize++;
		}
	}
	else if (strcmp(argv[1], "--input") == 0)
	{
		uint8_t currentByte;
		while (std::cin >> currentByte)
		{
			statistics[currentByte]++;
			totalSize++;
		}
	}
	else
	{
		std::cout << "Usage: entrop --file <filename> OR entrop --input" << std::endl;
		return INCORRECT_FORMAT;
	}

	float entropy = 0.0f;
	unsigned int sumOfLength = 0;
	unsigned int usedAlphabetSize = 0;
	for (uint32_t i = 0; i < 256; i++)
	{
		if (statistics[i] > 0)
		{
			//CHECK: float-casting
			usedAlphabetSize++;
			float probability = static_cast<float>(statistics[i]) / static_cast<float>(totalSize);
			sumOfLength -= std::ceil(log2f(probability));
			entropy -= probability * log2f(probability);
		}
	}

	float information = totalSize * entropy;
	float maximumEntropy = 8.0f; //log2f(256)
	float absolute = maximumEntropy - entropy;
	float relative = absolute/maximumEntropy;
	unsigned int additionalInfoSize = usedAlphabetSize + sumOfLength;
	float length = (additionalInfoSize + entropy * totalSize) / usedAlphabetSize;
	//TODO: fancy output

	std::ofstream outFile(argv[argc-1], std::ios::app);

	//std::cout << "File size N : " << totalSize << std::endl;
	//std::cout << "Entropy H : " << entropy << std::endl;
	//std::cout << "Information I : " << information << std::endl;

	std::string filename = (argc == 4) ? argv[2] : "";
	
	if (!filename.empty())
	{
		filename += " ";
	}

	outFile << filename << totalSize << ' ' << entropy << ' ' << maximumEntropy << ' ' << 
		information << ' ' << absolute << ' ' << relative << length << std::endl;
	outFile.close();

	//TODO: csv output
	for (uint32_t i = 0; i < 256; i++)
	{
		if (statistics[i] > 0)
		{
			//std::cout << "\'" << static_cast<char>(i) << "\' :" << statistics[i] << std::endl;
		}
	}
}
