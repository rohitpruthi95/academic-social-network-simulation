#include <string>
#include <map>
#include <vector>
#include <string>

#include "containers.h"
using namespace std;

//Course def
Course::Course(string _name, float _frequencyPerYear,
		Department* _department) {
	name = _name;
	frequencyPerYear = _frequencyPerYear;
	department = _department;
}
Course::~Course() {
	delete this;
}

Department* Course::getDepartment() const {
	return department;
}

float Course::getFrequencyPerYear() const {
	return frequencyPerYear;
}

string Course::getName() const {
	return name;
}

//Department def
Department::Department(string _name, int num1, int num2, float num3, float num4,
		University* _univ) {
	name = _name;
	noOfStudentsPerYear = num2;
	numFaculty = num1;
	deptCourses = num3;
	nonDeptCourses = num4;
	university = _univ;
}
Department::~Department() {
	course.clear();
	delete this;
}
void Department::addCourse(Course *_course) {
	course.push_back(_course);
}
std::vector<Course*> Department::getCourse() const {
	return course;
}

float Department::getDeptCourses() const {
	return deptCourses;
}

string Department::getName() const {
	return name;
}

float Department::getNonDeptCourses() const {
	return nonDeptCourses;
}

int Department::getNoOfStudentsPerYear() const {
	return noOfStudentsPerYear;
}

int Department::getNumFaculty() const {
	return numFaculty;
}

University* Department::getUniversity() const {
	return university;
}

//University def

University::University(string _name) {
	name = _name;
	sId = 0;
}
University::~University() {
	department.clear();
	interest.clear();
	hostel.clear();
	house.clear();
	delete this;
}

void University::addDepartment(Department* _department) {
	department.push_back(_department);
}

void University::setFriendliness(float friendliness) {
	this->friendliness = friendliness;
}

void University::setFriendshipRate(float friendshipRate) {
	this->friendshipRate = friendshipRate;
}

void University::addHostel(string _hostel) {
	hostel.push_back(_hostel);
}

void University::addHouse(string _house) {
	house.push_back(_house);
}

void University::addInterest(string _name, float _popularity) {
	interest.push_back(make_pair(_name, _popularity));
}

void University::setOpenness(float openness) {
	this->openness = openness;
}

std::vector<Department*> University::getDepartment() const {
	return department;
}

float University::getFriendliness() const {
	return friendliness;
}

float University::getFriendshipRate() const {
	return friendshipRate;
}

std::vector<string> University::getHostel() const {
	return hostel;
}

std::vector<string> University::getHouse() const {
	return house;
}

std::vector<pair<string, float> > University::getInterest() const {
	return interest;
}

string University::getName() const {
	return name;
}

float University::getOpenness() const {
	return openness;
}

