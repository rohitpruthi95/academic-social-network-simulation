#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "globals.h"
using namespace std;

string getRandomName() {
	int size = namesList.capacity();
	int idx;
	idx = rand() % size;
	return namesList.at(idx);
}

void loadNamesList(string fileName) {
	fstream fileInput;
	fileInput.open(fileName.c_str(), fstream::in);
	vector<string> loadedNames;
	string line;
	if (fileInput.is_open()) {
		while (getline(fileInput, line)) {
			loadedNames.push_back(line);
		}
		fileInput.close();
	}
	namesList.clear();
	namesList = loadedNames;
	loadedNames.clear();
	return;
}

void destroyNamesList() {
	namesList.clear();
}
