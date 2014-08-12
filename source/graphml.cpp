#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>

#include "globals.h"
#include "graphml.h"
#include "student.h"
#include "faculty.h"
#include "containers.h"
#include "logger.h"

#define mp make_pair
#define pb push_back
#define PERSON pair<string,int>
static int id = 0;
vector<PERSON > arr;
map<PERSON, int> idx;
vector<pair<int, int> > edge;
ofstream f;

void extendMap() {
	for (unsigned int i = 0; i < faculties.size(); i++) {
		adj[mp(faculties[i]->university, faculties[i]->getFacultyId())];
	}
	for (unsigned int i = 0; i < students.size(); i++) {
		adj[mp(students[i]->university, students[i]->getStudentId())];
	}
}

int getNode(PERSON x) {
	if (idx.find(x) == idx.end()) {
		arr.pb(x);
		return idx[x] = id++;
	}
	return idx[x];
}
void writeNodes() {
	for (int i = 0; i < id; i++) {
		f << "<node id=\"" << i << "\" ";
		f << "univ=\"" << arr[i].first << "\" ";
		f << "uid=\"" << arr[i].second << "\" ";
		f << "/>\n";
	}
}
void writeEdges() {
	for (int i = 0; i < edge.size(); i++) {
		f << "<edge source=\"" << edge[i].first << "\" ";
		f << "target=\"" << edge[i].second << "\" ";
		f << "/>\n";
	}
}
void writeHeader() {
	f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	f << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n";
	f << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
	f << "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n";
	f << "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
	f << "<graph id=\"G\" edgedefault=\"undirected\">\n";
}
void writeFooter() {
	f << "</graph>\n";
	f << "</graphml>";
}
void makeGraph() {
	extendMap();
	f.open("graph.graphml");
	map<PERSON, set<PERSON > >::iterator it;
	set<PERSON >::iterator itt;
	int id1, id2;
	for (it = adj.begin(); it != adj.end(); it++) {
		id1 = getNode(it->first);
		for (itt = (it->second).begin(); itt != (it->second).end(); itt++) {
			id2 = getNode(*itt);
			log((it->first).first + (itt->first));
			if (id1 < id2)
				edge.pb(mp(id1, id2));
		}
	}
	writeHeader();
	writeNodes();
	writeEdges();
	writeFooter();
	f.close();
}
