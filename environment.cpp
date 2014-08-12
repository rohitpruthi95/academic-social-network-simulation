#include <vector>
#include "containers.h"
#include "parser.h"
#include "globals.h"
#include "logger.h"
void setEnvironment(char* filename){
	clearlog();
	readFile(filename,departments,courses,universities,facultyRandom,studentRandom,courseRandom,friendRandom);
	log("Enviroment Set");
}

