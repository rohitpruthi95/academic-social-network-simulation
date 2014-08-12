#include <fstream>
#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include "containers.h"
#include "environment.h"
#include "parser.h"
using namespace std; 

void readFile(string s, std::vector<Department*> &dep, std::vector<Course*> &course, std::vector<University*> &univ,int &facultyRandom, int &studentRandom, int &courseRandom, int &friendRandom){
	ifstream f(s.c_str());  
	string temp,temp2;
	int num1,num2; 
	float num3,num4;
	University *prev;
	Department *tempD; 
	Course *tempC; 
	while(!f.eof()){
		getline(f,s);
		stringstream ss(s); 

		if(s[0] == 'U'){
			ss >> temp; 
			ss >> temp; 
			prev = new University(temp);
			univ.push_back(prev);
			stringToDepartment.clear();
		}
		
		else if(s[0] == 'D'){
			ss >> temp; 
			ss >> temp >> num1 >> num2 >> num3 >> num4 ; 
			tempD = new Department(temp,num1,num2,num3,num4,prev);
			prev->addDepartment(tempD); 
			dep.push_back(tempD); 
			stringToDepartment[temp]=tempD;
		}

		else if(s[0] == 'C'){
			ss >> temp;
			ss >> temp >> temp2 >> num3; 
			tempD = stringToDepartment[temp2]; 
			tempC = new Course(temp,num3,tempD); 
			tempD->addCourse(tempC);
			course.push_back(tempC);
		}

		else if(s[0] == 'I'){
			ss >> temp; 
			ss >> temp >> num3;
			prev->addInterest(temp,num3); 
		}

		else if(s[0] == 'H'){
			ss >> temp;
			if(temp.length() == 6){
				ss >> temp; 
				prev->addHostel(temp); 
			}
			else{
				ss >> temp; 
				prev->addHouse(temp);
			}
		}

		else if(s[0] == 'F'){
			ss >> temp; 
			if(temp.length() == 12){
				ss >> num3; 
				prev->setFriendliness(num3); 
			}
			else{
				ss >> num3; 
				prev->setFriendshipRate(num3); 
			}
		}

		else if(s[0] == 'O'){
			ss >> temp;
			ss >> num3; 
			prev->setOpenness(num3); 
		}
		else if(s[0] == 'R'){
			ss >> temp; 
			ss >> facultyRandom >> studentRandom >> courseRandom >> friendRandom ; 	
		}
	}
}
