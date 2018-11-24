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
#include "vtkAutoInit.h" 
#include<vtkInteractorStyleTrackballCamera.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL);


class vizualization
{
public:
	vizualization(vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter, vtkSmartPointer<vtkPolyDataMapper> map, vtkSmartPointer<vtkRenderWindow> &renderWindow, unsigned iterator);

	void mapSet(vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter);
	void actorSet(vtkSmartPointer<vtkPolyDataMapper> map);
	void renderSet(vtkSmartPointer<vtkRenderWindow> &renderWindow, unsigned iterator);

	~vizualization();



	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	vtkSmartPointer<vtkRenderWindow> renderWindow;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style;


	const static char* windowName;
};

