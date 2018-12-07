
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
	string path = "sphere_200_r40_0-5um.inp";
	//string path = "sphere_50_r10_2um.inp";
	//string path = "duzy.inp";
	//string path = "sphere_25_r5_4um.inp";
	//string path = "sphere_250_r25_1um.inp";
	//string path = "APTv3-300kVersion2_out.inp";
	//string path = "50x50x50 31% 56 new grains periodic_lm.inp";
	//string path = "sphere_100_r20_1um.inp";
	ifstream objFile("Data/"+path);
	objparse *obj = new objparse(objFile, Vertexes);
	subdividing *subd = new subdividing(Vertexes,path, obj);

	return  EXIT_SUCCESS;
}
