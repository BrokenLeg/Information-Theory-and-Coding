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
	if (argc < 2 || argc > 4)
	{
		std::cout << "Usage: entrop --file <filename> OR entrop --input" << std::endl;
		return INCORRECT_FORMAT;
	}

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//TODO: strings comparison
	if (strcmp(argv[1], "--file") == 0)
	{
		if (argc != 3)
		{
			std::cout << "usage: entrop --file <filename>" << std::endl;
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

	for (uint32_t i = 0; i < 256; i++)
	{
		if (statistics[i] > 0)
		{
			//CHECK: float-casting
			float probability = static_cast<float>(statistics[i]) / static_cast<float>(totalSize);
			entropy -= probability * log2f(probability);
		}
	}

	float information = totalSize * entropy;

	//TODO: fancy output
	std::cout << "Entropy H : " << entropy << std::endl;
	std::cout << "Information I : " << information << std::endl;
}
