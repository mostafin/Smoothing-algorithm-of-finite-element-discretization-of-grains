#include "vizualization.h"


const char* vizualization::windowName = "Subdivide algorithm";
vizualization::vizualization(vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter, vtkSmartPointer<vtkPolyDataMapper> map, vtkSmartPointer<vtkRenderWindow> &renderWindow, unsigned iterator)
{
	renderSet(renderWindow, iterator);
	mapSet(subdivisionFilter);
	actorSet(map);

	renderer->AddActor(this->actor);
	renderer->ResetCamera();
	renderer->SetBackground(.2, .3, .4);

	renderWindow->Render();
	renderWindow->SetWindowName(vizualization::windowName);
}

void vizualization::mapSet(vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter)
{
	this->mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	this->mapper->SetInputConnection(subdivisionFilter->GetOutputPort());
}

void vizualization::actorSet(vtkSmartPointer<vtkPolyDataMapper> map)
{
	this->actor = vtkSmartPointer<vtkActor>::New();
	this->actor->SetMapper(this->mapper);
	
}

void vizualization::renderSet(vtkSmartPointer<vtkRenderWindow> &renderWindow, unsigned iterator)
{
	this->renderer = vtkSmartPointer<vtkRenderer>::New();
	this->renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(this->renderWindow);


	renderWindow->AddRenderer(renderer);
	renderer->SetViewport(static_cast<double>(iterator) / 1, 0, static_cast<double>(iterator + 1) / 1, 1);
}


vizualization::~vizualization()
{
}
