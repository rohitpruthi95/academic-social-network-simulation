#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "faculty.h"
#include "globals.h"
#include "namesAccessor.h"
#define mp make_pair
#define pb push_back
using namespace std;

//Faculty def
Faculty::Faculty(int _facultyId, string _name, Department* _department,
		string _house, std::vector<string> _interest) {
	facultyId = _facultyId;
	name = _name;
	department = _department;
	home = _house;
	interest = _interest;
}
Faculty::~Faculty() {
	delete this;
}

Department* Faculty::getDepartment() const {
	return department;
}
int Faculty::getFacultyId() const {
	return facultyId;
}
string Faculty::getHouse() const {
	return home;
}
std::vector<string> Faculty::getInterest() const {
	return interest;
}
string Faculty::getName() const {
	return name;
}

void generateFaculties(std::vector<University*> _universities,
		int _facultySeed) {
	srand(_facultySeed);
	loadNamesList("faculty.txt");
	std::vector<Department*> _departments;
	for (unsigned int i = 0; i < _universities.size(); i++) {
		_departments = _universities[i]->getDepartment();
		for (unsigned int j = 0; j < _departments.size(); j++) {
			for (int k = 0; k < _departments[j]->getNumFaculty(); k++) {
				generateFaculty(_universities[i], _departments[j],
						_universities[i]->sId++);
			}
		}
	}
	destroyNamesList();
}

void generateFaculty(University* _university, Department* _department,
		int _facultyId) {

	string _name;
	_name = getRandomName();
	Faculty* _faculty;
	vector<string> _interest;
	string uni = _university->getName();
	departmentMap[mp(uni, _department->getName())].pb(mp(uni, _facultyId));
	for (unsigned int i = 0; i < _university->getInterest().size(); i++) {
		if (rand() % 100 < (int) (_university->getInterest()[i].second * 100)) {
			interestMap[_university->getInterest()[i].first].pb(
					mp(uni, _facultyId));
			_interest.push_back(_university->getInterest()[i].first);
		}
	}
	int j = rand() % _university->getHouse().size(); //random number
	string _house;
	_house = _university->getHouse()[j];
	homeMap[mp(uni, _house)].pb(mp(uni, _facultyId));
	_faculty = new Faculty(_facultyId, _name, _department, _house, _interest);
	_faculty->university = _university->getName();
	_faculty->dept = _department->getName();
	facultyMap[make_pair(_university->getName(), _facultyId)] = _faculty;
	faculties.push_back(_faculty);
}

void printFaculties() {
	cout << faculties.size() << endl;
	for (unsigned int i = 0; i < faculties.size(); i++) {
		cout << faculties[i]->getFacultyId() << " " << faculties[i]->getName()
				<< " " << faculties[i]->getInterest()[0] << endl;
	}
}
