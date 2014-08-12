#ifndef FACULTY_H_
#define FACULTY_H_

#include <string>
#include <map>
#include <vector>
#include "containers.h"

class Faculty;
class Faculty {
	int facultyId;
	string name;
	Department* department;
public:
	string home;
	std::vector<string> interest;
	string university;
	string dept;
	std::vector<string> courses;
	Faculty(int, string, Department*, string, std::vector<string>);
	~Faculty();
	Department* getDepartment() const;
	int getFacultyId() const;
	string getHouse() const;
	std::vector<string> getInterest() const;
	string getName() const;
};

void generateFaculties(std::vector<University*>, int);
void generateFaculty(University*, Department*, int);
void printFaculties();

#endif /* FACULTY_H_ */
