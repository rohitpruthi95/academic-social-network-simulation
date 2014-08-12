#include <vector>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include "containers.h"
#include "faculty.h"
#include "student.h"
using namespace std;
std::vector<University*> universities;
std::vector<Course*> courses;
std::vector<Department*> departments;
map<string,Department*> stringToDepartment;
int facultyRandom;
int studentRandom;
int courseRandom;
int friendRandom;
int roundRobinCounter = 0;
std::vector<Faculty*> faculties;
std::vector<Student*> students;
std::vector<string> namesList;
pthread_mutex_t mutex;
#define PERSON pair<string,int>
#define DEPARTMENT pair<string,string>
#define INTEREST string
#define COURSE pair<string,string>
#define HOME pair<string,string>
map< PERSON , set<PERSON > > adj; //graph

map< COURSE , vector<PERSON> > courseMap;
map< DEPARTMENT , vector<PERSON> > departmentMap;
map< INTEREST , vector<PERSON> > interestMap;
map< HOME , vector<PERSON> > homeMap;

map< PERSON , Faculty*> facultyMap;
map< PERSON , Student*> studentMap;

fstream fl;
