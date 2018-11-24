#include "dataExport.h"


dataExport::dataExport(vtkSmartPointer<vtkPolyDataAlgorithm> obj, int count,string path, vector<vertex*> v)
{
	this->iterator = 1;
	this->count = count;
	this->polydata = obj->GetOutput();
	this->v = v;

	/*for (vtkIdType i = 0; i < polydata->GetNumberOfPoints(); i++)
	{
		double pointCoordinates[3];
		polydata->GetPoint(i, pointCoordinates);
		cout << "Point " << i << " : (" << pointCoordinates[0] << " " << pointCoordinates[1] << " " << pointCoordinates[2] << ")" <<endl;
	}*/

	string line;
	ifstream seek1;
	ofstream  seek2;

	seek1.open("Data/" + path);
	seek2.open("../Output/"+path, fstream::in | fstream::out | fstream::ate | ios::trunc);

	while (seek1.good()) {
		getline(seek1, line);
		if (line == "*Node")
		{
			seek2 << line << endl;
			while (1)
			{
				getline(seek1, line);
				if (line.find("*Element") == string::npos)
				{
					changeVertex(line);
					seek2 << line << endl;
				}
				else
					break;
			}
		}
		seek2 << line << endl;
	}
	seek1.close();
	seek2.close();
}

dataExport::~dataExport()
{
}
void dataExport::changeVertex(string &line)
{
	float id;
	sscanf_s(line.c_str(), "%f", &id);
	stringstream newline;

	/*for (auto &elem : this->v) {
		if (id == elem->id && iterator <= this->count) {

			double pointCoorodinates[3];
			this->polydata->GetPoint(iterator - 1, pointCoorodinates);
			newline << '\t' << id << ",\t" << pointCoorodinates[0] << ",\t" << pointCoorodinates[1] << ",\t" << pointCoorodinates[2] << '@';
			this->iterator++;
		}
	}*/
	if (iterator <= this->count) {
		int index = 0;
		for (auto & elem : this->v) {
			if (elem->id == id)
			{
				double pointCoorodinates[3];
				this->polydata->GetPoint(index, pointCoorodinates);
				newline << '\t' << id << ",\t" << pointCoorodinates[0] << ",\t" << pointCoorodinates[1] << ",\t" << pointCoorodinates[2];
				this->iterator++;
				line = newline.str();
				break;
			}
			index++;
		}
	}
}
