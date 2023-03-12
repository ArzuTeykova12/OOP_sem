﻿#include <iostream>
#include <fstream>
#include <iomanip>

#pragma once
#pragma warning (disable : 4996)

const size_t MAX_SIZE = 1024;
const size_t MAX_SIZEe = 1000;
const unsigned SPEC_DIGIT_POS = 4;

enum class Major
{
	Informatics = 4,
	ComputerScience = 8,
	SoftwareEngineering = 6
};

struct Student
{
	Major major;

	char firstName[MAX_SIZE];
	char lastName[MAX_SIZE];
	char email[MAX_SIZE];
	char fn[MAX_SIZE];
};
struct StudentsCollection
{
	Student* data;
};

unsigned int getStudentsCount(std::ifstream& file)
{
	char buff[MAX_SIZE];
	unsigned int studentsCount = 0;

	while (!file.eof())
	{
		file.getline(buff, MAX_SIZE);
		studentsCount++;
	}

	file.seekg(0, std::ios::beg);
	return studentsCount - 1;
}

void parseField(char* dest, const char*& src)
{
	while (*src != ',' && *src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}

	src++;
	*dest = '\0';
}

void setMajor(Student& student)
{
	if (student.fn[SPEC_DIGIT_POS] == (int)Major::Informatics)
	{
		student.major = Major::Informatics;
	}
	else if (student.fn[SPEC_DIGIT_POS] == (int)Major::ComputerScience)
	{
		student.major = Major::ComputerScience;
	}
	else if (student.fn[SPEC_DIGIT_POS] == (int)Major::SoftwareEngineering)
	{
		student.major = Major::SoftwareEngineering;
	}
}

void initialiseStudent(Student& student, const char* line)
{
	parseField(student.firstName, line);
	parseField(student.lastName, line);
	parseField(student.email, line);
	parseField(student.fn, line);

	setMajor(student);
}

int fillStudentsCollection(StudentsCollection& collection, const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "File can't be opened!" << std::endl;
		return -1;
	}

	unsigned int studentsCount = getStudentsCount(file);
	collection.data = new Student[studentsCount];

	char buff[MAX_SIZE];
	file.getline(buff, MAX_SIZE);
	for (size_t i = 0; i < studentsCount; i++)
	{
		file.getline(buff, MAX_SIZE);
		initialiseStudent(collection.data[i], buff);
	}

	file.close();
	return studentsCount;
}

void printByFn(const StudentsCollection& collection, const char* fn, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(collection.data[i].fn, fn) == 0)
		{
			std::cout << "Name: " << collection.data[i].firstName << ' ' << collection.data[i].lastName <<
				", Email: " << collection.data[i].email << ", FN: " << collection.data[i].fn << std::endl;
			if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::Informatics)
			{
				std::cout << "Major: Informatics" << std::endl;
			}
			else if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::ComputerScience)
			{
				std::cout << "Major: Computer science" << std::endl;
			}
			else if (collection.data[i].fn[SPEC_DIGIT_POS] == (int)Major::SoftwareEngineering)
			{
				std::cout << "Major: Software engineering" << std::endl;
			}
		}
	}
}

void print(std::fstream& file, const char fileName[])
{
	Student studentInfo;
	file.clear();
	file.seekg(0);
	std::cout << std::setw(MAX_SIZE) << setiosflags(std::ios::left)
		<< "Име" << '|' << resetiosflags(std::ios::left) << std::setw(MAX_SIZE)
		<< "Имейл" << '|' << std::setw(MAX_SIZE)
		<< "Факултетен номер" << std::endl;
	while (file.read((char*)&studentInfo, sizeof(studentInfo)))
	{
		std::cout << studentInfo.firstName << ", "
			<< studentInfo.lastName << ", " << studentInfo.email
			<< ", " << studentInfo.fn;
	}
	
}

void update(const StudentsCollection& collection, const char* fn, size_t size)
{
	char new_email[MAX_SIZE];
	std::cout << "Нов имейл: " << std::endl;
	std::cin >> new_email;
	int new_sizeEmail = strlen(new_email) + 1;
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(collection.data[i].fn, fn) == 0)
		{
			strcpy(collection.data[i].email, new_email);
		}
	}

}

//void updateEmail(const char fileName[], const char* fn, Student& s)
//{
//	std::cout << "Данни за студента: " << std::endl;
//	Student studentInfo;
//	
//	std::cout << studentInfo.firstName << ", " 
//		<< studentInfo.lastName << ", " << studentInfo.email 
//		<< ", " << studentInfo.fn << std::endl;
//	char new_email;
//	std::cout << "Нов имейл: " << std::endl;
//	std::cin >> new_email;
//	
//	//s.email = new_email;
//
//	//studentInfo.email = new_email;
//
//}

int save(std::fstream& file, const char fileName[])
{
	Student studentInfo;
	std::ofstream output("students2.cvc");
	if (!output)
	{
		return -1;
	}
	//header
	output << std::setw(MAX_SIZE) << setiosflags(std::ios::left)
		<< "Име" << '|' << resetiosflags(std::ios::left) << std::setw(MAX_SIZE)
		<< "Имейл" << '|' << std::setw(MAX_SIZE)
		<< "Факултетен номер" << std::endl;

	file.clear();
	file.seekg(0);

	while (file.read((char*)&studentInfo, sizeof(studentInfo)))
	{
		if (!(output << studentInfo.firstName << ", "
			<< studentInfo.lastName << ", " << studentInfo.email
			<< ", " << studentInfo.fn))
		{
			std::cout << "Записът в текстов файл е неуспешен" << std::endl;
			output.close();
			return 1;
		}
		
	}
	output.close();
	std::cout << "Информацията е записана в students2.cvc" << std::endl;
	return 0;
}
int main()
{
	std::cout << "Open file: ";
	char fileName[MAX_SIZE];
	std::cin >> fileName;

	
	//
	std::fstream fileStudent;
		 
	StudentsCollection collection;
	int size = fillStudentsCollection(collection, fileName);
	if (size == -1)
	{
		return -1;
	}

	std::cout << "File successfully opened!" << std::endl << std::endl;

	char command[MAX_SIZE];
	std::cin >> command;

	if (strcmp(command, "print") == 0)
	{
		char fn[MAX_SIZE];
		std::cin >> fn;

		printByFn(collection, fn, size);
		std::cout << std::endl;
	}
	// HW: Implement the rest of the commands
	if (strcmp(command, "edite") == 0)
	{
		char fn[MAX_SIZE];
		std::cin >> fn;
		
		update(collection, fn, size);
		std::cout << std::endl;
	}
	if (strcmp(command, "save") == 0)
	{
		char fn[MAX_SIZE];
		std::cin >> fn;

		save(fileStudent, fn);
		std::cout << std::endl;
	}

	delete[] collection.data;
}