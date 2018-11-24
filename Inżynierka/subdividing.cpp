
#include "subdividing.h"

int subdividing::numberOfSubdivisions = 2;
subdividing::subdividing(vector<vertex*> v, string path)
{	
	this->path = path;
	this->v = v;
	this->renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(600 * 2, 600); //(width, height)

	parse(v);
	surfReconstruction();
	this->renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	this->renderWindow = renderWindow;
	renderWindowInteractor->SetRenderWindow(this->renderWindow);
	Subdivivde(this->numberOfSubdivisions);
	
	this->style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->Start();
}

vtkSmartPointer<vtkPoints> subdividing::parse(vector<vertex*> v)
{
	this->input = vtkSmartPointer<vtkPoints>::New();

	for (auto & elem : v) {
		this->input->InsertNextPoint(elem->loc.x(), elem->loc.y(), elem->loc.z());
	}
	return input;
}

vtkSmartPointer<vtkSurfaceReconstructionFilter> subdividing::surfReconstruction()
{
	this->polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(this->input);


	// Construct the surface and create isosurface.	
	this->surf = vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
#if VTK_MAJOR_VERSION <= 5
	surf->SetInput(this->polydata);
#else
	surf->SetInputData(this->polydata);
#endif

	

	vtkSmartPointer<vtkContourFilter> cf =
		vtkSmartPointer<vtkContourFilter>::New();
	cf->SetInputConnection(surf->GetOutputPort());
	cf->SetValue(0, 0.0);

	// Sometimes the contouring algorithm can create a volume whose gradient
	// vector and ordering of polygon (using the right hand rule) are
	// inconsistent. vtkReverseSense cures this problem.
	vtkSmartPointer<vtkReverseSense> reverse =
		vtkSmartPointer<vtkReverseSense>::New();
	reverse->SetInputConnection(cf->GetOutputPort());
	reverse->ReverseCellsOn();
	reverse->ReverseNormalsOn();

	this->map = vtkSmartPointer<vtkPolyDataMapper>::New();
	this->map->SetInputConnection(reverse->GetOutputPort());
	this->map->ScalarVisibilityOff();


	// Subdivision filters only work on triangles
	vtkSmartPointer<vtkTriangleFilter> triangles =
		vtkSmartPointer<vtkTriangleFilter>::New();
	triangles->SetInputConnection(reverse->GetOutputPort());
	triangles->Update();
	this->originalMesh = triangles->GetOutput();

	
	/*for (vtkIdType i = 0; i < originalMesh->GetNumberOfPoints(); i++)
	{
		double pointCoordinates[3];
		originalMesh->GetPoint(i, pointCoordinates);
		cout << "Point " << i << " : (" << pointCoordinates[0] << " " << pointCoordinates[1] << " " << pointCoordinates[2] << ")" << endl;
	}*/
	this->NumberOfPointsToExtract = originalMesh->GetNumberOfPoints();

	std::cout << "Before subdivision" << std::endl;
	std::cout << "    There are " << this->originalMesh->GetNumberOfPoints()
		<< " points." << std::endl;
	std::cout << "    There are " << this->originalMesh->GetNumberOfPolys()
		<< " triangles." << std::endl;



	return vtkSmartPointer<vtkSurfaceReconstructionFilter>();
}

void subdividing::Subdivivde(int number)
{	this->numberOfSubdivisions = number;
	for (unsigned i = 0; i < 1; i++)
	{
		vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter;
		switch (i)
		{
		case 0:
			subdivisionFilter = vtkSmartPointer<vtkLoopSubdivisionFilter>::New();
			dynamic_cast<vtkLoopSubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(this->numberOfSubdivisions);
			break;

		/*case 1:
			subdivisionFilter = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
			dynamic_cast<vtkLinearSubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(this->numberOfSubdivisions);
			break;*/
		default:
			break;
		}

#if VTK_MAJOR_VERSION <= 5
		subdivisionFilter->SetInputConnection(originalMesh->GetProducerPort());
#else
		subdivisionFilter->SetInputData(this->originalMesh);
#endif
		subdivisionFilter->Update();

		vizualization *viz = new vizualization(subdivisionFilter, this->map, this->renderWindow, i);

		if (i == 0)
			this->data = new dataExport(subdivisionFilter,this->NumberOfPointsToExtract,this->path,this->v);
	}
}




subdividing::~subdividing()
{
}
