#include <iostream>
#include <fstream>
#include <iomanip>

#pragma warning (disable : 4996)

const size_t MAX_SIZE = 1024;

struct HexViewerFile
{
	unsigned char* data;
	size_t dataSize;
};


void freeHexViewerFile(HexViewerFile& file)
{
	delete[] file.data;
	file.dataSize = 0;
}

size_t getFileSize(std::ifstream& file)
{
	unsigned int currentPos = file.tellg();
	file.seekg(0, std::ios::end);

	size_t fileSize = file.tellg();
	file.seekg(currentPos);

	return fileSize;
}

HexViewerFile init(const char* filePath)
{
	std::ifstream ifs(filePath, std::ios::binary);
	HexViewerFile myFile;

	if (!ifs.is_open())
	{
		myFile.data = nullptr;
		myFile.dataSize = 0;
		return myFile;
	}

	myFile.dataSize = getFileSize(ifs);
	myFile.data = new unsigned char[myFile.dataSize];
	ifs.read((char*)myFile.data, myFile.dataSize);

	ifs.close();
	return myFile;
}

bool isValidSymbol(char ch)
{
	return ch >= 'a' && ch <= 'z' ||
		ch >= 'A' && ch <= 'Z' ||
		ch >= '0' && ch <= '9';
}

void print(const HexViewerFile& myFile)
{
	for (size_t i = 0; i < myFile.dataSize; i++)
	{
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)myFile.data[i] << ' ';
	}
	std::cout << std::endl;

	for (size_t i = 0; i < myFile.dataSize; i++)
	{
		if (isValidSymbol(myFile.data[i]))
		{
			std::cout << myFile.data[i] << "  ";
		}
		else
		{
			std::cout << ".. ";
		}
	}
	std::cout << std::endl;
}


void add(const char* filePath, unsigned char bytes)
{
	std::ofstream file(filePath, std::ios::binary | std::ios::app);
	if (!file.is_open())
	{
		std::cout << "Error opening file!" << std::endl;
		return;
	}

	file.write((const char*)&bytes, sizeof(bytes));

	file.close();
}
void change(const char* filePath, int index, unsigned char bytes)
{
	std::fstream file(filePath, std::ios::binary | std::ios::in | std::ios::out);
	if (!file.is_open())
	{
		std::cout << "Error opening file!" << std::endl;
		return;
	}

	file.seekp(index);

	file.write((const char*)&bytes, sizeof(bytes));
	
	file.close();

	std::cout << "Operation executed successfully. " << std::endl;
}
void save(const HexViewerFile& myFile)
{
	std::fstream file("myData.dat", std::ios::binary);

	file.write((const char*)&myFile.data, sizeof(myFile.data));
	file.write((const char*)&myFile.dataSize, sizeof(myFile.dataSize));

	file.close();

	std::cout << "File successfully saved." << std::endl;
	
}
void saveAs(const HexViewerFile& myFile, const char* filePath)
{
	std::ofstream outputFile("newFileSave.dat", std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return;
	}

	outputFile.write((const char*)&myFile.data, sizeof(myFile.data));
	outputFile.write((const char*)&myFile.dataSize, sizeof(myFile.dataSize));

	outputFile.close();
	std::cout << "The information is saved in newFileSave.dat" << std::endl;
	return;
}
int main()
{

	std::cout << "Enter a file path: " << std::endl;
	char filePath[MAX_SIZE];
	std::cin >> filePath;

	HexViewerFile myFile = init("myData.dat");
	


	int size = sizeof(myFile);

	std::cout << "File loaded successfully. " << "Size: " << size << " bytes" << std::endl;


	char command[MAX_SIZE];
	do
	{

	   std::cin >> command;


	    if (strcmp(command, "view") == 0)
		{
			print(myFile);
			freeHexViewerFile(myFile);

			std::cout << std::endl;
		}

		else if (strcmp(command, "add") == 0)
		{
			
			add(filePath, sizeof(char));

			std::cout << std::endl;
		}
		else if (strcmp(command, "change") == 0)
		{
			unsigned int index, bytes;

			std::cin >> index;
			std::cin >> bytes;

			change(filePath, index, bytes);

			std::cout << std::endl;
		}
		else if (strcmp(command, "save") == 0)
		{

			save(myFile);

			std::cout << std::endl;
		}
		else if (strcmp(command, "saveAs") == 0)
		{

			saveAs(myFile,"newFileSave.dat");

			std::cout << std::endl;
		}

	} while (strcmp(command, "exit") != 0);
	
}
