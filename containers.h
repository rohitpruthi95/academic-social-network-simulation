#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <string>
#include <map>
#include <vector>
#include <string>
using namespace std;
class Course;
class Department;
class University;
class Course {
	string name;
	float frequencyPerYear;
	Department *department;
public:
	Course(string, float, Department*);
	~Course();
	string getName() const;
	float getFrequencyPerYear() const;
	Department* getDepartment() const;


};

class Department {
	string name;
	int noOfStudentsPerYear;
	int numFaculty;
	std::vector<Course*> course;
	University *university;
	float deptCourses;
	float nonDeptCourses;
public:
	Department(string, int, int, float, float, University*);
	~Department();
	void addCourse(Course*);
	string getName() const;
	int getNoOfStudentsPerYear() const;
	int getNumFaculty() const;
	University* getUniversity() const;
	float getDeptCourses() const;
	float getNonDeptCourses() const;
	std::vector<Course*> getCourse() const;

};

class University {
	string name;
	std::vector<Department*> department;
	std::vector<pair<string, float> > interest;
	std::vector<string> hostel;
	std::vector<string> house;
	float friendshipRate;
	float friendliness;
	float openness;
public:
	University (string);
	~University();
	void addInterest(string, float);
	void addHostel(string);
	void addHouse(string);
	void addDepartment(Department*);
	void setFriendshipRate(float);
	void setFriendliness(float);
	void setOpenness(float);
	int sId;

	string getName() const;
	std::vector<Department*> getDepartment() const;
	std::vector<pair<string, float> > getInterest() const;
	std::vector<string> getHostel() const;
	std::vector<string> getHouse() const;
	float getFriendshipRate() const;
	float getFriendliness() const;
	float getOpenness() const;

};

#endif
