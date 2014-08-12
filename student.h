#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <map>
#include <vector>
#include "containers.h"

class Student;
class Student {
	int studentId;
	string name;
	Department* department;
public:
	string university;
	string home;
	std::vector<string> interest;
	std::vector<string> courses;
	string dept;
	int year;
	Student(int, string, Department*, string, std::vector<string>);
	~Student();
	Department* getDepartment() const;
	int getStudentId() const;
	string getHostel() const;
	std::vector<string> getInterest() const;
	string getName() const;
};

void generateStudents(std::vector<University*>, int);
void generateStudent(University*, Department*, int);
void printStudents();

#endif /* STUDENT_H_ */
