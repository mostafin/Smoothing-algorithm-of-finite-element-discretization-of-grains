#pragma once
#include<vtkPolyDataAlgorithm.h>
#include<vtkPointData.h>
#include<fstream>
#include<vtkSmartPointer.h>
#include<list>
#include<sstream>
#include"vertex.h"
using namespace std;
class dataExport
{
public:
	dataExport(vtkSmartPointer<vtkPolyDataAlgorithm> obj,int count,string path, vector<vertex*> v);
	~dataExport();

	void changeVertex(string& line);
	vtkSmartPointer<vtkPolyData> polydata;
	int iterator;
	int count;
	vector<vertex*> v;
	
};

