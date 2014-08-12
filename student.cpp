#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "student.h"
#include "globals.h"
#include "namesAccessor.h"

using namespace std;
void updateYear();
//Student def
Student::Student(int _studentId, string _name, Department* _department,
		string _hostel, std::vector<string> _interest) {
	studentId = _studentId;
	name = _name;
	department = _department;
	home = _hostel;
	interest = _interest;
}
Student::~Student() {
	delete this;
}

Department* Student::getDepartment() const {
	return department;
}
int Student::getStudentId() const {
	return studentId;
}
string Student::getHostel() const {
	return home;
}
std::vector<string> Student::getInterest() const {
	return interest;
}
string Student::getName() const {
	return name;
}

void generateStudents(std::vector<University*> _universities,
		int _studentSeed) {
	srand(_studentSeed);
	updateYear();
	loadNamesList("student.txt");
	std::vector<Department*> _departments;
	for (unsigned int i = 0; i < _universities.size(); i++) {
		_departments = _universities[i]->getDepartment();
		for (unsigned int j = 0; j < _departments.size(); j++) {
			for (int k = 0; k < _departments[j]->getNoOfStudentsPerYear();
					k++) {
				generateStudent(_universities[i], _departments[j],
						_universities[i]->sId++);
			}
		}
	}
	destroyNamesList();
}

void generateStudent(University* _university, Department* _department,
		int _studentId) {

	string _name;

	_name = getRandomName();
	Student* _student;
	vector<string> _interest;
	for (unsigned int i = 0; i < _university->getInterest().size(); i++) {
		if (rand() % 100 < (int) (_university->getInterest()[i].second * 100)) {
			_interest.push_back(_university->getInterest()[i].first);
			interestMap[_university->getInterest()[i].first].push_back(
					make_pair(_university->getName(), _studentId));
		}
	}
	int j = rand() % _university->getHostel().size(); //random number
	string _hostel;
	_hostel = _university->getHostel()[j];
	_student = new Student(_studentId, _name, _department, _hostel, _interest);
	_student->university = _university->getName();
	_student->dept = _department->getName();
	_student->year = 1;
	departmentMap[make_pair(_university->getName(), _department->getName())].push_back(
			make_pair(_university->getName(), _studentId));
	homeMap[make_pair(_university->getName(), _hostel)].push_back(
			make_pair(_university->getName(), _studentId));
	studentMap[make_pair(_university->getName(), _studentId)] = _student;
	students.push_back(_student);
}

void updateYear() {
	vector<Student*>::iterator iter;
	for (iter = students.begin(); iter != students.end(); iter++) {
		(*iter)->year++;
	}
#define PERSON pair<string,int>
#define DEPARTMENT pair<string,string>
#define INTEREST string
#define COURSE pair<string,string>
#define HOME pair<string,string>
#define UNIV string
	vector<PERSON >::iterator it;
	map< DEPARTMENT, vector
	<PERSON > >::iterator itd;
	map<INTEREST, vector<PERSON > >::iterator iti;
	map< HOME, vector
	<PERSON > >::iterator ith;
	map<PERSON, Student*>::iterator itt;
	map<COURSE, vector<PERSON > >::iterator itc;

#define VP  vector<PERSON>
VP *temp;
	for (ith = homeMap.begin(); ith != homeMap.end(); ith++) {
		temp = new VP;
		for (it = (ith->second).begin(); it != (ith->second).end(); it++) {
			if(studentMap.find(*it) == studentMap.end()){
				(*temp).push_back(*it);
			} else if(studentMap[*it]->year <= 4){
				(*temp).push_back(*it);
			}
		}
		(ith->second).clear();
		ith->second = *temp;
	}
	for (itd = departmentMap.begin(); itd != departmentMap.end(); itd++) {
		temp = new VP;
		for (it = (itd->second).begin(); it != (itd->second).end(); it++) {
			if(studentMap.find(*it) == studentMap.end()){
				(*temp).push_back(*it);
			} else if(studentMap[*it]->year <= 4){
				(*temp).push_back(*it);
			}
		}
		(itd->second).clear();
		itd->second = *temp;
	}
	for (iti = interestMap.begin(); iti != interestMap.end(); iti++) {
		temp = new VP;
		for (it = (iti->second).begin(); it != (iti->second).end(); it++) {
			if(studentMap.find(*it) == studentMap.end()){
				(*temp).push_back(*it);
			} else if(studentMap[*it]->year <= 4){
				(*temp).push_back(*it);
			}
		}
		(iti->second).clear();
		iti->second = *temp;
	}
	map<PERSON, set<PERSON > >::iterator itm;
	set<PERSON >::iterator itp;
	#define SP set<PERSON >
	#define ADM map<PERSON,SP >
	SP *tempset;
	ADM *tempadm;
	tempadm = new ADM;
	for (itm = adj.begin(); itm != adj.end();itm++) {
		if(studentMap.find(itm->first) == studentMap.end()){
			(*tempadm).insert(*itm);
		}else if(studentMap[itm->first]->year <= 4){
			(*tempadm).insert(*itm);
		}
	}
	adj.clear();
	adj = *tempadm;
	for (itm = adj.begin(); itm != adj.end();itm++) {
		itt = studentMap.find(itm->first);
		if (itt != studentMap.end()) {
			if ((itt->second)->year > 4) {
				(itm->second).clear();
				adj.erase(itm);
				continue;
			}

		}
		tempset = new SP;
		for (itp = (itm->second).begin(); itp != (itm->second).end();itp++) {
			if(studentMap.find(*itp) == studentMap.end()){
				(*tempset).insert(*itp);
			} else if(studentMap[*itp]->year <= 4){
				(*tempset).insert(*itp);
			}
		}
		(itm->second).clear();
		itm->second = *tempset;
	}
	map<PERSON, Student*>::iterator its;
	for (iter = students.begin(); iter != students.end();) {
		if ((*iter)->year > 4) {
			students.erase(iter);
			continue;
		}
		iter++;
	}
}

void printStudents() {
	cout << students.size() << endl;
	for (unsigned int i = 0; i < students.size(); i++) {
		cout << i << " " << students[i]->getStudentId() << " "
				<< students[i]->getName() << " " << students[i]->courses.size()
				<< endl;
	}
}

