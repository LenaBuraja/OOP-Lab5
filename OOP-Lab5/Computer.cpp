#include "Computer.h"
#include "Word.h"
#include "Game.h"
#include <stdio.h>  
#include <cstring>
#include <iostream>

Computer::Computer(int size) {
	this->size = 0;
	soft = new Soft*[this->size];
	setSize(size);
}

Computer::Computer(Computer& program) : Computer(program.getSize()) {
	for (int i = 0; i < getSize(); i++) {
		setSoft(i, program.getSoft(i));
	}
}

void Computer::setSize(int newSize) {
	Soft* *newSoft = new Soft*[newSize];
	int minSize = (size < newSize) ? size : newSize;
	for (int i = 0; i < minSize; i++) {
		newSoft[i] = soft[i];
	}
	delete soft;
	size = newSize;
	soft = newSoft;
}

void Computer::setSoft(int index, Soft* value) {
	if (index >= 0 || index < size) {
		soft[index] = value;
	}
}

Soft*& Computer::getSoft(int index) {
	return soft[index];
}

int Computer::getSize() {
	return size;
}

Computer::~Computer() {
	delete soft;
}

void Computer::sort() {
	for (int g = 0; g < getSize() - 1; g++) {
		for (int i = 0; i < getSize() - 1 - g; i++) {
			if (Soft::compare(soft[i], soft[i + 1]) >= 0) {
				Soft *resault = soft[i];
				soft[i] = soft[i + 1];
				soft[i + 1] = resault;
			}
		}
	}
}

void Computer::printSoft() {
	for (int i = 0; i < getSize(); i++) {
		std::cout << i + 1 << ". ";
		getSoft(i)->print();
	}
}

void Computer::searchVersionWord(int searchVersion) {
	char* title = "Word";
	int countVersion = 0;
	int countWord = 0;
	for (int i = 0; i < getSize(); i++) {
		if (dynamic_cast<Word*>(soft[i]) != NULL) {
			countWord++;
			if (searchVersion == dynamic_cast<Word*>(soft[i])->getVersion()) {
				getSoft(i)->print();
				countVersion++;
			}
		}
	}
	if (countVersion == 0) {
		std::cout << "On a computer that is not installed this version of Word." << std::endl;
	}
	if (countWord == 0) {
		std::cout << "The computer is not installed Word." << std::endl;
	}
} 

void Computer::searchGerneGame(Game::Genre searchGerne) {
	int countGame = 0;
	int countGerne = 0;
	for (int i = 0; i < getSize(); i++) {
		if (dynamic_cast<Game*>(soft[i]) != NULL) {
			countGame++;
			if (searchGerne == dynamic_cast<Game*>(soft[i])->getGenre()) {
				getSoft(i)->print();
				countGerne++;
			}
		}
	}
	if (countGerne == 0) {
		std::cout << "On a computer that is not installed this genre of game." << std::endl;
	}
	if (countGame == 0) {
		std::cout << "The computer is not installed game." << std::endl;
	}
}
