#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include "containers.h"
#include "globals.h"
void readFile(string, std::vector<Department*>&, std::vector<Course*>&, std::vector<University*>&, int&, int&, int&, int&);

#endif