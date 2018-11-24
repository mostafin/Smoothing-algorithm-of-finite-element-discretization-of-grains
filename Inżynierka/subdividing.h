#pragma once
#include <sstream>
#include<iostream>
#include<fstream>

#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkSurfaceReconstructionFilter.h>
#include <vtkProgrammableSource.h>
#include <vtkContourFilter.h>
#include <vtkReverseSense.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include<vtkVertexGlyphFilter.h>
#include<vtkPoints.h>
#include<vtkActor.h>
#include<vtkTriangleFilter.h>
#include<vtkLinearSubdivisionFilter.h>
#include<vtkLoopSubdivisionFilter.h>
#include<vtkButterflySubdivisionFilter.h>
#include "vertex.h"
#include "vizualization.h"
#include "vtkAutoInit.h" 
#include<vtkInteractorStyleTrackballCamera.h>
#include "dataExport.h"
//VTK_MODULE_INIT(vtkRenderingOpenGL);

using namespace std;

class subdividing
{
public:
	subdividing(vector<vertex*> v,string path);

	vtkSmartPointer<vtkPoints> parse(vector<vertex*> v);
	vtkSmartPointer<vtkSurfaceReconstructionFilter> surfReconstruction();
	void Subdivivde(int number);

	~subdividing();

	static int numberOfSubdivisions;
	vtkSmartPointer<vtkRenderWindow> renderWindow;
	vtkSmartPointer<vtkPolyData> originalMesh;
	vtkSmartPointer<vtkPoints> input;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkSurfaceReconstructionFilter> surf;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	//vizualization *viz;
	vtkSmartPointer<vtkPolyDataMapper> map;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style;
	dataExport *data;
	string path;
	vector<vertex*> v;

	int NumberOfPointsToExtract;
};

