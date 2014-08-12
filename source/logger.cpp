#include <fstream>

#include "logger.h"
#include "globals.h"
using namespace std;
void startlog(){
	fl.open("log.txt",fstream::out|fstream::app);
}
void log(string s){
	fl << s << '\n';
}
void endlog(){
	fl.close();
}
void clearlog(){
	ofstream ff("log.txt");
	ff.close();
}

