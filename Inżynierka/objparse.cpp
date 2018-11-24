#include "objparse.h"
#include<ctime>
using namespace std;


objparse::objparse(istream& objfile, vector<vertex*> &Vertexes)
{
	clock_t time = clock();
	string line;
	while (objfile.good()) {
		getline(objfile, line);

		if (line == "*Node")
		{
			while (1)
			{
				getline(objfile, line);
				if (line.find("*Element") == string::npos)
					parseNode(line);
				else
					break;

			}

			while (1) {

				getline(objfile, line);
				if (line.find("*Elset") == string::npos)
					parseElement(line);
				else
					break;
			}
		}
		if (line.find("*Elset") != string::npos)
		{
			while (true) {
				vector<int> v;
				while (true) {
					getline(objfile, line);
					if (line.find("*Elset") == string::npos && line.find("*Nset") == string::npos)
						elsetParse(line, v);
					else {
						Elset.push_back(v);
						break;
					}
				}
				if (line.find("*Nset") != string::npos)
					break;
			}
			break;
		}
	}
	findVertex(this->Elset, this->Elset_v);
	checkVertexes(this->Elset_v);

	time = (clock() - time) / 1000;
	cout << "Czas parsowania: " <<" m: " << (int)(time / 60.0) << " s: " << time  % 60 << endl;

	Vertexes = verteces;
}


objparse::~objparse()
{
}

void objparse::parseNode(string line)
{
	vertex *v = new vertex();

	float x, y, z, id;
	sscanf_s(line.c_str(), "%f,	%f,	%f,	%f", &id, &x, &y, &z);
	v->loc = Vector3f(x, y, z);
	v->id = id;

	this->temp_verteces.push_back(v);
	//verteces.push_back(v);
}

void objparse::parseElement(string line)
{
	int id;
	int tab[4];
	sscanf_s(line.c_str(), "%d,\t%d,\t%d,\t%d,\t%d", &id, &tab[0], &tab[1], &tab[2], &tab[3]);

	//float max = tab[0];
	//int  j = 0;
	//for (int i = 1; i < 4; i++)
	//{
	//	if (tab[i] > max) {
	//		max = tab[i];
	//		j = i;
	//	}
	//}
	struct objface f;
	f.id = objfaces.size() + 1;

	for (unsigned int i = 0; i < 4; i++) {
		//if (i != j)
		f.vids.push_back(tab[i]);
	}

	this->objfaces.push_back(f);

}

vector<int> objparse::elsetParse(string line, vector<int>& v)
{
	int tab[10];
	sscanf_s(line.c_str(), "%d,	%d,	%d,	%d, %d, %d, %d, %d, %d, %d", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5], &tab[6], &tab[7], &tab[8], &tab[9]);

	for (int i = 0; i < 10; i++) {
		if (tab[i] > 0)
			v.push_back(tab[i]);

	}
	return v;
}

void objparse::findVertex(list<vector<int>> elset, list<vector<vertex*>>& Elset_v)
{
	bool equal;
	for (auto & e : elset) {
		vector<vertex*> vec;
		for (auto & elem : e) {
			objface obj = this->objfaces[elem - 1];
			for (auto & elem2 : obj.vids) {
				equal = false;
				vertex  *v = this->temp_verteces[elem2 - 1];

				for (auto & vert : vec) {
					if (v == vert) {
						equal = true;
						break;
					}
				}
				if (equal == false)
					vec.push_back(v);
			}
		}
		Elset_v.push_back(vec);
	}
}

void objparse::checkVertexes(list<vector<vertex*>> Elset_v)
{
	//int index = 0;
	//int i = 0;
	//int smallest;
	//for (list<vector<vertex*>>::iterator iter_v = Elset_v.begin(); iter_v != Elset_v.end(); iter_v++) {
	//	vector<vertex*> v = *iter_v;
	//	if (i == 0)
	//		smallest = v.size();
	//	else if (v.size() < smallest)
	//	{
	//		smallest = v.size();
	//		index = i;
	//	}
	//	i++;
	//}

	//i = 0;
	//for (list<vector<vertex*>>::iterator iter_v = Elset_v.begin(); iter_v != Elset_v.end(); iter_v++) {
	//	vector<vertex*> v = *iter_v;
	//	if (i == index)
	//	{
	//		vector<vertex*> v = *iter_v;
	//		for (auto & elem : v) {
	//			this->verteces.push_back(elem);
	//		}
	//	}
	//	i++;
	//}

	for (auto & elset : Elset_v) {

		for (auto &vert : temp_verteces) {
			if (vert->cout < 2) {
				for (auto & elset_elem : elset)
				{
					if (vert->id == elset_elem->id)
					{
						vert->cout = vert->cout + 1; 
						//cout << "Inc v : " << vert->id << endl;
						break;
					}
				}
			}
		}
	}

	for (auto & vert : temp_verteces) {
		if (vert->cout >= 2)
		{
			this->verteces.push_back(vert);
		}
	}
	/*bool exist;
	bool go_back = false;
	for (auto & list_el : Elset_v) {
		for (int i = 0; i < verteces.size(); i++) {

			exist = false;
			for (auto & elem : list_el) {
				if (verteces[i] == elem)
					exist = true;
			}
			if (exist == false) {
				this->verteces.erase(verteces.begin() + i);
				i--;
			}
		}
	}*/
}

