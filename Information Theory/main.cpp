#include <iostream>
#include <fstream>
#include <Windows.h>

//zero initialized
static uint32_t statistics[256];
static uint32_t totalSize;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "usage: EntropyCount <filename>" << std::endl;
		return 1;
	}

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream file(argv[1], std::ios::in);
	uint8_t currentByte;
	
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

	float entropy = 0.0f;

	for (uint32_t i = 0; i < 256; i++)
	{
		if (statistics[i] > 0)
		{
			float probability = static_cast<float>(statistics[i]) / static_cast<float>(totalSize);
			entropy -= probability * log2f(probability);
		}
	}

	float information = totalSize * entropy;

	std::cout << "Entropy H : " << entropy << std::endl;
	std::cout << "Information I : " << information << std::endl;
}
