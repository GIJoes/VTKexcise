#pragma once
#include <vtkInteractorStyleTrackballCamera.h>


//// Handle mouse events
//class MouseInteractorStyle2 : public vtkInteractorStyleTrackballCamera
//{
//public:
//	static MouseInteractorStyle2* New();
//	vtkTypeMacro(MouseInteractorStyle2, vtkInteractorStyleTrackballCamera);
//
//	virtual void OnLeftButtonDown();
	//{
	//	int* clickPos = this->GetInteractor()->GetEventPosition();
	//	cout << "clickPos:" << clickPos[0] << "  " << clickPos[1] << "  " << clickPos[2] << endl;
	//	// Pick from this location.
	//	vtkSmartPointer<vtkPropPicker>  picker =
	//		vtkSmartPointer<vtkPropPicker>::New();
	//	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

	//	if (!picker->GetActor())
	//	{
	//		cout << "Pick NULL!!" << endl;
	//	}

	//	double* pos = picker->GetPickPosition();
	//	cout << "pos[0] = " << pos[0] << ",pos[1] = " << pos[1] << ",pos[2] = " << pos[2] << endl;

	//	//Create a cube
	//	vtkSmartPointer<vtkCubeSource> cubeSource =
	//		vtkSmartPointer<vtkCubeSource>::New();
	//	cubeSource->SetCenter(pos[0], pos[1], pos[2]);
	//	cubeSource->SetXLength(0.1);
	//	cubeSource->SetYLength(0.1);
	//	cubeSource->SetZLength(0.1);

	//	//Create a mapper and actor
	//	vtkSmartPointer<vtkPolyDataMapper> mapper =
	//		vtkSmartPointer<vtkPolyDataMapper>::New();
	//	mapper->SetInputConnection(cubeSource->GetOutputPort());

	//	vtkSmartPointer<vtkActor> actor =
	//		vtkSmartPointer<vtkActor>::New();
	//	actor->SetMapper(mapper);
	//	actor->GetProperty()->SetColor(0.5, 0, 0.5);


	//	//this->GetInteractor()->GetRenderWindow()->GetRenderers()->GetDefaultRenderer()->AddActor(actor);
	//	this->GetDefaultRenderer()->AddActor(actor);
	//	// Forward events
	//	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	//}
//
//private:
//
//};

