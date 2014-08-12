#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include "containers.h"
#include "globals.h"
#include "environment.h"
#include "friend.h"
#include "logger.h"
PERSON randomPerson(std::vector<PERSON> personList);
void handleRequest(PERSON _randomSender, PERSON _randomReceiver);

void generateRequest(int _friendSeed) {
	stringstream logstream;
	srand(_friendSeed);
	PERSON randomSender, randomReceiver;
	float out_probability;
	int fs = faculties.size();
	int ss = students.size();
	int num = rand() % (fs + ss);
	if (num >= fs) {
		Student* _student = students[num - fs];
		randomSender = make_pair(_student->university,
				_student->getStudentId());
		logstream << randomSender.first << ":" << randomSender.second
				<< " sent a friend request to ";
		out_probability =
				_student->getDepartment()->getUniversity()->getOpenness();
		if (rand() * 100 < (int) (100 * out_probability)) {
			num = rand() % (fs + ss);
			if (num >= fs) { //idx = num - fs (student)
				Student* _student = students[num - fs];
				randomReceiver = make_pair(_student->university,
						_student->getStudentId());
			} else {
				Faculty* _faculty = faculties[num];
				randomReceiver = make_pair(_faculty->university,
						_faculty->getFacultyId());
			}
			logstream << randomReceiver.first << ":" << randomReceiver.second
					<< " since he/she is open to outside options!";
		} else {
			int k;
			k = rand() % 4;
			if (k == 0) {
				std::vector<string> _courses;
				_courses = _student->courses;
				if (_student->courses.size() == 0)
					return;
				int j = rand() % _courses.size();
				randomReceiver = randomPerson(
						courseMap[make_pair(_student->university,
								_student->courses[j])]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common course "
						<< _student->courses[j] << ".";
			} else if (k == 1) {
				randomReceiver = randomPerson(
						departmentMap[make_pair(_student->university,
								_student->dept)]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common department "
						<< _student->dept << ".";
			} else if (k == 2) {
				randomReceiver =
						randomPerson(
								homeMap[make_pair(_student->university,
										_student->home)]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common hostel : " << _student->home
						<< ".";
			} else {
				std::vector<string> _interest;
				_interest = _student->getInterest();
				int j = rand() % _interest.size();
				randomReceiver = randomPerson(interestMap[_interest[j]]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common interest in "
						<< _interest[j] << ".";
			}
		}
	} else {
		//idx = num (faculty)
		Faculty* _faculty = faculties[num];
		randomSender = make_pair(_faculty->university,
				_faculty->getFacultyId());
		logstream << randomSender.first << ":" << randomSender.second
				<< " sent a friend request to ";
		out_probability =
				_faculty->getDepartment()->getUniversity()->getOpenness();
		if (rand() * 100 < (int) (100 * out_probability)) {
			num = rand() % (fs + ss);
			if (num >= fs) {
				Student* _student = students[num - fs];
				randomReceiver = make_pair(_student->university,
						_student->getStudentId());
			} else {
				Faculty* _faculty = faculties[num];
				randomReceiver = make_pair(_faculty->university,
						_faculty->getFacultyId());
			}
			logstream << randomReceiver.first << ":" << randomReceiver.second
					<< " since he/she is open to outside options!";
		} else {

			int k;

			k = rand() % 4;
			if (k == 0) {
				std::vector<string> _courses;
				_courses = _faculty->courses;
				if (_courses.size() == 0)
					return;
				int j = rand() % _courses.size();
				randomReceiver = randomPerson(
						courseMap[make_pair(_faculty->university,
								_faculty->courses[j])]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common course "
						<< _faculty->courses[j] << ".";
			} else if (k == 1) {
				randomReceiver = randomPerson(
						departmentMap[make_pair(_faculty->university,
								_faculty->dept)]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common department "
						<< _faculty->dept << ".";
			} else if (k == 2) {
				randomReceiver =
						randomPerson(
								homeMap[make_pair(_faculty->university,
										_faculty->home)]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common house : " << _faculty->home
						<< ".";
			} else {
				std::vector<string> _interest;
				_interest = _faculty->getInterest();
				int j = rand() % _interest.size();
				randomReceiver = randomPerson(interestMap[_interest[j]]);
				logstream << randomReceiver.first << ":"
						<< randomReceiver.second
						<< " as they share a common interest in "
						<< _interest[j] << ".";
			}
		}
	}
	log(logstream.str());
	float recip_prob;
	if (facultyMap[randomReceiver] != NULL) {
		recip_prob =
				facultyMap[randomReceiver]->getDepartment()->getUniversity()->getFriendliness();
	} else {
		recip_prob =
				studentMap[randomReceiver]->getDepartment()->getUniversity()->getFriendliness();
	}
	if ((rand() % 100) < (int) (recip_prob * 100))
		handleRequest(randomSender, randomReceiver);
}

PERSON randomPerson(std::vector<PERSON> _personList) {

	PERSON myRandomPerson;
	int randomNum = rand() % _personList.size();
	myRandomPerson = _personList[randomNum];

	return myRandomPerson;

}

void handleRequest(PERSON _randomSender, PERSON _randomReceiver) {
	if(_randomSender != _randomReceiver) {
		if(adj[_randomSender].find(_randomReceiver)==adj[_randomSender].end()) {
				adj[_randomSender].insert(_randomReceiver);
				adj[_randomReceiver].insert(_randomSender);
				stringstream ss;
				ss << "Friend Request Accepted! " << _randomSender.first << ":" << _randomSender.second << " and " <<_randomReceiver.first << ":" << _randomReceiver.second << " are now friends!";
				log(ss.str());
			}
		}
	}

