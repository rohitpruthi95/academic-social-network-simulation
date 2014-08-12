#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include "containers.h"
#include "faculty.h"
#include "student.h"
extern std::vector<University*> universities;
extern std::vector<Course*> courses;
extern std::vector<Department*> departments;
extern map<string,Department*> stringToDepartment;
extern int facultyRandom;
extern int studentRandom;
extern int courseRandom;
extern int friendRandom;
extern int roundRobinCounter;
extern std::vector<Faculty*> faculties;
extern std::vector<Student*> students;
extern std::vector<string> namesList;
extern pthread_mutex_t mutex;
#define PERSON pair<string,int>
#define DEPARTMENT pair<string,string>
#define INTEREST string
#define COURSE pair<string,string>
#define HOME pair<string,string>

extern map< PERSON , set<PERSON > > adj; //graph

extern map< COURSE , vector<PERSON> > courseMap;
extern map< DEPARTMENT , vector<PERSON> > departmentMap;
extern map< INTEREST , vector<PERSON> > interestMap;
extern map< HOME , vector<PERSON> > homeMap;

extern map< PERSON , Faculty*> facultyMap;
extern map< PERSON , Student*> studentMap;
extern fstream fl;
#endif
