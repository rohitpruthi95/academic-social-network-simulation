all:
	g++ containers.cpp courses.cpp environment.cpp faculty.cpp friend.cpp globals.cpp graphml.cpp logger.cpp main.cpp namesAccessor.cpp parser.cpp student.cpp -pthread -std=c++0x -o generator
	g++ solve.cpp -o solve
	chmod +x *
