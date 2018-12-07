#pragma once
#include<iostream>
#include<list>
#include<vector>
#include<fstream>
#include<iterator>
#include<cstdio>
#include<sstream>
#include "vertex.h"
using namespace std;
class objparse
{
	struct objface {
		unsigned int id;
		vector<unsigned int> vids;
		vector<unsigned int> nids;
		int sum;
	};

public:
	objparse(istream& objfile, vector<vertex*> &Vertexes);
	~objparse();

	void parseNode(string line);
	void parseElement(string line);

	vector<int> elsetParse(string line, vector<int> &v);
	void findVertex(list<vector<int>> elset, list<vector<vertex*>> &Elset_v);
	void checkVertexes(list<vector<vertex*>>Elset_v);
	void createFaces();

	vector<vertex*> verteces;
	vector<vertex*> temp_verteces;
	vector<vertex*> surface_verteces;
	vector<struct objface> objfaces;
	vector<struct objface> inner_objfaces;
	list <vector<int>> Elset;
	list < vector<vertex*>> Elset_v;
};

