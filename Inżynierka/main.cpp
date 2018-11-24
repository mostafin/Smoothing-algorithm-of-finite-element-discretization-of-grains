
#include<iostream>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include "objparse.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "Eigen/Dense"
#include "vtkAutoInit.h" 
#include "vertex.h"
#include "subdividing.h"
VTK_MODULE_INIT(vtkRenderingOpenGL);

using namespace std;
using namespace Eigen;
int main() {


	vector<vertex*> Vertexes;
	//string path = "sphere_25_r5_4um.inp";
	string path = "duzy.inp";
	ifstream objFile("Data/"+path);
	objparse *obj = new objparse(objFile, Vertexes);
	//cout << "punkt pierwszy : " << Vertexes[0]->loc.x() << "\t" << Vertexes[0]->loc.y() << "\t" << Vertexes[0]->loc.z() << endl;
	subdividing *subd = new subdividing(Vertexes,path);

	return  EXIT_SUCCESS;
}
