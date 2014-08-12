#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include "containers.h"
#include "globals.h"
#include "environment.h"

map<Department*, std::vector<Course*> > departmentCourseMap;
void addRandomDepCourse(Student*, Department*);
void clearCourses();

void generateCourses(std::vector<University*> _universities,
		int _courseRandom) {
	clearCourses();
	srand(_courseRandom);
	std::vector<Department*> _departments;
	for (unsigned int i = 0; i < _universities.size(); i++) {
		_departments = _universities[i]->getDepartment();
		std::vector<Course*> allCourses;
		// Float Courses
		for (unsigned int j = 0; j < _departments.size(); j++) {
			allCourses = _departments[j]->getCourse();
			for (unsigned int k = 0; k < allCourses.size(); k++) {
				if (rand() * 100
						< (int) (allCourses[k]->getFrequencyPerYear() * 50)) {
					departmentCourseMap[_departments[j]].push_back(
							allCourses[k]);
				}
			}
		}
		// Assign to Students
		int m;
		for (unsigned int j = 0; j < _departments.size(); j++) {
			std::vector<PERSON> personList = departmentMap[make_pair(
					_universities[i]->getName(), _departments[j]->getName())];
			std::vector<Student *> studentList;
			for (unsigned int h = 0; h < personList.size(); h++) {
				if (studentMap.find(personList[h]) != studentMap.end())
					studentList.push_back(studentMap[personList[h]]);
			}
			for (unsigned int k = 0; k < studentList.size(); k++) {
				for (unsigned int l = 0;
						l < (unsigned int) (_departments[j]->getDeptCourses());
						l++) {
					addRandomDepCourse(studentList[k], _departments[j]);
				}
				if (rand() * 100
						< (int) ((_departments[j])->getDeptCourses()
								- (100
										* (int) (_departments[j])->getDeptCourses()))) {
					addRandomDepCourse(studentList[k], _departments[j]);
				}
				for (unsigned int l = 0;
						l
								< (unsigned int) (_departments[j]->getNonDeptCourses());
						l++) {
					m = rand() % _departments.size();
					while (m == (int) j)
						m = rand() % _departments.size();
					addRandomDepCourse(studentList[k], _departments[m]);
				}
				if (rand() * 100
						< (int) ((_departments[j])->getDeptCourses()
								- (100
										* (int) (_departments[j])->getNonDeptCourses()))) {
					m = rand() % _departments.size();
					while (m == (int) j)
						m = rand() % _departments.size();
					addRandomDepCourse(studentList[k], _departments[m]);
				}
			}
		}

		for (unsigned int j = 0; j < _departments.size(); j++) {
			std::vector<PERSON> personList = departmentMap[make_pair(
					_universities[i]->getName(), _departments[j]->getName())];
			std::vector<Faculty *> facultyList;
			for (unsigned int h = 0; h < personList.size(); h++) {
				if (facultyMap[personList[h]] != NULL)
					facultyList.push_back(facultyMap[personList[h]]);
			}
			for (unsigned int l = 0; l < facultyList.size(); l++) {
				unsigned int k;
				k = (roundRobinCounter + l) % facultyList.size();
				if (l < departmentCourseMap[_departments[j]].size()) {
					facultyList[k]->courses.push_back(
							departmentCourseMap[_departments[j]][l]->getName());
					courseMap[make_pair(_universities[i]->getName(),
							departmentCourseMap[_departments[j]][l]->getName())].push_back(
							make_pair(_universities[i]->getName(),
									facultyList[k]->getFacultyId()));
				}
			}
		}
	}
}

void addRandomDepCourse(Student* _student, Department* _department) {
	int j = rand() % departmentCourseMap[_department].size();
	while ((std::find((_student->courses.begin()), (_student->courses.end()),
			(departmentCourseMap[_department][j]->getName())))
			!= (_student->courses.end())) {
		j = rand() % departmentCourseMap[_department].size();
	}
	courseMap[make_pair(_department->getUniversity()->getName(),
			departmentCourseMap[_department][j]->getName())].push_back(
			make_pair(_department->getUniversity()->getName(),
					_student->getStudentId()));
	_student->courses.push_back(departmentCourseMap[_department][j]->getName());
}

void printCourses(std::vector<Department*> _departments) {
	std::vector<PERSON> all211;
	all211 = courseMap[make_pair("IITD", "CSL201")];
	cout << all211.size() << endl;
	for (unsigned int i = 0; i < all211.size(); i++) {
		cout << i << " " << all211[i].second << endl;
	}
}

void clearCourses() {
	for (unsigned int i = 0; i < students.size(); i++) {
		students[i]->courses.clear();
	}
	for (unsigned int i = 0; i < faculties.size(); i++) {
		faculties[i]->courses.clear();
	}
	courseMap.clear();
	roundRobinCounter++;
}
