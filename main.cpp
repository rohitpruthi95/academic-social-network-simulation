#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sstream>
#include <queue>
#include <iostream>
#include "globals.h"
#include "environment.h"
#include "containers.h"
#include "faculty.h"
#include "friend.h"
#include "student.h"
#include "logger.h"
#include "parser.h"
#include "graphml.h"
#include "courses.h"

#define YEAR 31622400
#define HOUR 3600
#define SEC 1
#define DAY 24*HOUR
#define WEEK 7*DAY
#define SEM  15811200
#define MIN  60

#define mp make_pair
#define pb push_back
using namespace std;
int MAXTIME = 14*YEAR;
struct ms {
	long int type;
	int Time;
	int tid;
	ms() {
		type = 11;
	}
};
typedef pair<int, int> PI;
class mycomparison {
	bool reverse;
public:
	mycomparison(const bool &revparam = false) {
		reverse = revparam;
	}
	bool operator()(const PI &lhs, const PI &rhs) const {
		if (reverse)
			return (lhs > rhs);
		else
			return (lhs < rhs);
	}
};
int ts, tc, tf, gt, tg;
priority_queue<PI, vector<PI>, greater<PI> > q;

int currentTime;
float rrq;
void *c_thread(void*);
void *s_thread(void*);
void *f_thread(void*);
void sendRequest(int Time, int tid);
ms recAlarm(int);
void Timekeeper();
int main(int argc, char* argv[]) {
	cout << "Simulation Started\n";
	if(argc>=3) {
		int tim;
		tim = atoi(argv[3]);
		if(argv[2][1] == 'd')
			MAXTIME = tim * DAY;
		if(argv[2][1] == 'm')
			MAXTIME = tim * MIN;
		if(argv[2][1] == 'y')
			MAXTIME = tim * YEAR;
		if(argv[2][1] == 'h')
			MAXTIME = tim * HOUR;
		if(argv[2][1] == 'w')
			MAXTIME = tim * WEEK;
		if(argv[2][1] == 's')
			MAXTIME = tim * SEC;
	}
	clearlog();
	ts = msgget(1, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | IPC_CREAT);
	tc = msgget(3, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | IPC_CREAT);
	tf = msgget(4, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | IPC_CREAT);
	gt = msgget(2, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | IPC_CREAT);
	tg = msgget(5, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | IPC_CREAT);
	pid_t pid = fork();
	if (pid != 0) //generator
			{
		startlog();
		setEnvironment(argv[1]);
		generateFaculties(universities, facultyRandom);
		int num;
		for (num = 0, rrq = 0; num < universities.size(); num++) {
			rrq += universities[num]->getFriendshipRate();
		}
		rrq /= (num * 10);
		sendRequest(1, 1);
		sendRequest(1, 2);
		sendRequest(1, 3);
		void* status;
		pthread_t st, ft, ct;
		pthread_mutex_init(&mutex, NULL);
		pthread_create(&st, NULL, s_thread, NULL);
		pthread_create(&ct, NULL, c_thread, NULL);
		pthread_create(&ft, NULL, f_thread, NULL);
		ms m;
//		msgrcv(tg, &m, 16, 11, 0);
		pthread_mutex_destroy(&mutex);
		pthread_join(st, NULL);
		pthread_join(ft, NULL);
		pthread_join(ct, NULL);
		makeGraph();
		endlog();
		studentMap.clear();
		adj.clear();
		courseMap.clear();
		departmentMap.clear();
		interestMap.clear();
		homeMap.clear();
		facultyMap.clear();
		faculties.clear();
		students.clear();
		namesList.clear();
		stringToDepartment.clear();
		universities.clear();
		courses.clear();
		departments.clear();
		msgctl(ts, IPC_RMID, NULL);
		msgctl(tc, IPC_RMID, NULL);
		msgctl(tf, IPC_RMID, NULL);
		msgctl(gt, IPC_RMID, NULL);
		msgctl(tg, IPC_RMID, NULL);
		pthread_exit(NULL);
	} else //Time KEEPER
	{
		startlog();
		currentTime = 0;
		Timekeeper();
		endlog();
	}
}
void sendRequest(int Time, int tid) {
	ms m;
	m.Time = Time;
	m.tid = tid;
	msgsnd(gt, &m, 16, 0);
//	cout << "SENT REQ: " << m.Time << " " << m.tid << endl;
}
//Time KEEPER
void Timekeeper() {
	ms m;
	int fcount = 0;
	bool flage, pause = false;
	PI p;
	int prevTime = 0;
	int newTime = 0;
	while (currentTime < MAXTIME) {
		newTime = currentTime / YEAR;
		if (newTime > prevTime) {
			cout << newTime << endl;
			prevTime = newTime;
		}
		//RECEIVER
		msgrcv(gt, &m, 16, 11, 0);
		if (m.tid == 3)
			fcount++;
		if (m.Time >= currentTime || m.Time == -1) {
			q.push(mp(m.Time, m.tid));
		}
		//SENDER
		flage = false;
		if (!q.empty()) {
			p = q.top();
			if (fcount > 0) {
				q.pop();
				flage = true;
			}
		}
		if (flage && !pause) {
			m.Time = p.first;
			m.tid = p.second;
			currentTime = m.Time;
//			switch (m.tid) {
//			case 1:
//				log("T:S");
//				break;
//			case 2:
//				log("T:C");
//				break;
//			case 3:
//				log("T:F");
//				break;
//			}
			if (m.tid == 1)
				msgsnd(ts, &m, 16, 0);
			else if (m.tid == 2)
				msgsnd(tc, &m, 16, 0);
			else if (m.tid == 3)
				fcount--, msgsnd(tf, &m, 16, 0);
		}
	}
	m.Time = MAXTIME + 1;
	m.tid = 1;
	int err = msgsnd(ts, &m, 16, 0);
	m.tid = 2;
	msgsnd(tc, &m, 16, 0);
	m.tid = 3;
	msgsnd(tf, &m, 16, 0);
}
//Time KEEPER COMPLETE	

//GENERATOR
void *s_thread(void*) {
	ms m;
	while (1) {
		msgrcv(ts, &m, 16, 11, 0);
		log("Students Generated");
		if (m.Time == MAXTIME + 1) {
			break;
		}
		pthread_mutex_lock(&mutex);
		generateStudents(universities, studentRandom);
		pthread_mutex_unlock(&mutex);
		studentRandom = rand();
		m.Time = m.Time + YEAR;
		sendRequest(m.Time, 1);
	}
}

void *c_thread(void*) {
	ms m;
	while (1) {
		msgrcv(tc, &m, 16, 11, 0);
		log("Courses Generated");
		if (m.Time == MAXTIME + 1) {
			break;
		}
		pthread_mutex_lock(&mutex);
		generateCourses(universities, courseRandom);
		pthread_mutex_unlock(&mutex);
		courseRandom = rand();
		m.Time = m.Time + SEM;
		sendRequest(m.Time, 2);
	}
}

void *f_thread(void*) {
	ms m;
	void* status;
	default_random_engine generator(friendRandom);
	exponential_distribution<double> distribution(rrq);
	while (1) {
		msgrcv(tf, &m, 16, 11, 0);
		if (m.Time == MAXTIME + 1) {
			break;
		}
		m.Time = m.Time + (MIN * distribution(generator)); //CHANGE WITH EXPONENTIAL DISTRIBUTION
		sendRequest(m.Time, 3); // SEND REQUEST TO TimeKEEPER FOR NEXT FREIND REQ
		friendRandom = rand();
		generateRequest(friendRandom);
	}
}
//GEN COMPLETE

