#ifndef NAMES_ACCESSOR_H
#define NAMES_ACCESSOR_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "globals.h"
using namespace std;

string getRandomName();

void loadNamesList(string fileName);

void destroyNamesList();

#endif
