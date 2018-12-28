//#include <vtkVersion.h>
//#include <vtkSmartPointer.h>
//#include <vtkActor.h>
//#include<vtkCubeSource.h>
//#include <vtkRendererCollection.h>
//#include <vtkCellArray.h>
//#include <vtkObjectFactory.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkPropPicker.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkRenderer.h>
//#include<vtkProperty.h>
//#include"NewInteractor.h"
//#include<vtkBoxWidget.h>
//
//
//
//class vtkMyCallback : public vtkCommand
//{
//public:
//	static vtkMyCallback *New()
//	{
//		return new vtkMyCallback;
//	}
//	virtual void Execute(vtkObject *caller, unsigned long, void*)
//	{
//		// Here we use the vtkBoxWidget to transform the underlying coneActor
//		// (by manipulating its transformation matrix).
//		vtkSmartPointer<vtkTransform> t =
//			vtkSmartPointer<vtkTransform>::New();
//		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
//		widget->GetTransform(t);
//		widget->GetProp3D()->SetUserTransform(t);
//	}
//};
//
//
// //Handle mouse events
//vtkStandardNewMacro(MouseInteractorStyle2);
//
//void MouseInteractorStyle2::OnLeftButtonDown()
//{
//	int* clickPos = this->GetInteractor()->GetEventPosition();
//
//	// Pick from this location.
//	vtkSmartPointer<vtkPropPicker>  picker =
//		vtkSmartPointer<vtkPropPicker>::New();
//	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
//
//	double* pos = picker->GetPickPosition();
//
//	//Create a cube
//	vtkSmartPointer<vtkCubeSource> cubeSource =
//		vtkSmartPointer<vtkCubeSource>::New();
//	cubeSource->SetCenter(pos[0], pos[1], pos[2]);
//	cubeSource->SetXLength(0.1);
//	cubeSource->SetYLength(0.1);
//	cubeSource->SetZLength(0.1);
//
//	//Create a mapper and actor
//	vtkSmartPointer<vtkPolyDataMapper> mapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//	mapper->SetInputConnection(cubeSource->GetOutputPort());
//
//	vtkSmartPointer<vtkActor> actor =
//		vtkSmartPointer<vtkActor>::New();
//	actor->SetMapper(mapper);
//	actor->GetProperty()->SetColor(1, 0, 1);
//
//
//	//this->GetInteractor()->GetRenderWindow()->GetRenderers()->GetDefaultRenderer()->AddActor(actor);
//	this->GetDefaultRenderer()->AddActor(actor);
//	// Forward events
//	vtkSmartPointer<vtkBoxWidget> boxWidget =
//		vtkSmartPointer<vtkBoxWidget>::New();
//	boxWidget->SetInteractor(this->Interactor);
//
//	boxWidget->SetProp3D(actor);
//	boxWidget->SetPlaceFactor(1.25); // Make the box 1.25x larger than the actor
//	boxWidget->PlaceWidget();
//
//	vtkSmartPointer<vtkMyCallback> callback =
//		vtkSmartPointer<vtkMyCallback>::New();
//	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
//
//	boxWidget->On();
//
//
//
//
//	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
//}
//
////vtkStandardNewMacro(MouseInteractorStyle2);



#include <vtkVersion.h>

#include <vtkSmartPointer.h>

#include <vtkMath.h>

#include <vtkActor.h>

#include <vtkProperty.h>

#include <vtkSphereSource.h>

#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkObjectFactory.h>

#include <vtkSphereSource.h>

#include <vtkPolyDataMapper.h>

#include <vtkPropPicker.h>

#include <vtkRenderWindow.h>

#include <vtkRenderWindowInteractor.h>

#include <vtkRenderer.h>


#include<vtkBoxWidget.h>
#include <vtkCommand.h>
#include <vtkTransform.h>

//// Handle mouse events
class vtkMyCallback : public vtkCommand
{
public:
	static vtkMyCallback *New()
	{
		return new vtkMyCallback;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		// Here we use the vtkBoxWidget to transform the underlying coneActor
		// (by manipulating its transformation matrix).
		vtkSmartPointer<vtkTransform> t =
			vtkSmartPointer<vtkTransform>::New();
		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		widget->GetTransform(t);
		widget->GetProp3D()->SetUserTransform(t);
	}
};

// Handle mouse events

class MouseInteractorHighLightActor : public vtkInteractorStyleTrackballCamera

{

public:

	static MouseInteractorHighLightActor* New();

	vtkTypeMacro(MouseInteractorHighLightActor, vtkInteractorStyleTrackballCamera);



	MouseInteractorHighLightActor()

	{

		LastPickedActor = NULL;

		LastPickedProperty = vtkProperty::New();

	}

	virtual ~MouseInteractorHighLightActor()

	{

		LastPickedProperty->Delete();

	}

	virtual void OnLeftButtonDown()

	{

		int* clickPos = this->GetInteractor()->GetEventPosition();



		// Pick from this location.

		vtkSmartPointer<vtkPropPicker>  picker =

			vtkSmartPointer<vtkPropPicker>::New();

		picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());



		// If we picked something before, reset its property

		if (this->LastPickedActor)

		{

			this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);

		}

		this->LastPickedActor = picker->GetActor();

		if (this->LastPickedActor)

		{

			// Save the property of the picked actor so that we can

			// restore it next time

			this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());

			// Highlight the picked actor by changing its properties

			this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);

			this->LastPickedActor->GetProperty()->SetDiffuse(1.0);

			this->LastPickedActor->GetProperty()->SetSpecular(0.0);

		}

		vtkSmartPointer<vtkBoxWidget> boxWidget =
		vtkSmartPointer<vtkBoxWidget>::New();
		boxWidget->SetInteractor(this->Interactor);
		boxWidget->SetProp3D(this->LastPickedActor);

		/*if (this->LastPickedActor)
		{
			boxWidget->SetProp3D(this->LastPickedActor);
		}
		else
		{
			boxWidget->SetProp3D(this->GetDefaultRenderer()->GetActors()->GetLastActor());

		}*/
		boxWidget->SetPlaceFactor(1.25); // Make the box 1.25x larger than the actor
		boxWidget->PlaceWidget();

		vtkSmartPointer<vtkMyCallback> callback =
		vtkSmartPointer<vtkMyCallback>::New();
		boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

		boxWidget->On();

		//this->Interactor->Initialize();
		// Forward events

		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();

		printf("down");
	}


private:

	vtkActor    *LastPickedActor;

	vtkProperty *LastPickedProperty;

};



vtkStandardNewMacro(MouseInteractorHighLightActor);



// Execute application.
vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =

vtkSmartPointer<vtkRenderWindowInteractor>::New();

vtkSmartPointer<MouseInteractorHighLightActor> style =

vtkSmartPointer<MouseInteractorHighLightActor>::New();
int main(int argc, char *argv[])

{

	int numberOfSpheres = 10;

	if (argc > 1)

	{

		numberOfSpheres = atoi(argv[1]);

	}

	// A renderer and render window

	vtkSmartPointer<vtkRenderer> renderer =

		vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderWindow> renderWindow =

		vtkSmartPointer<vtkRenderWindow>::New();

	renderWindow->AddRenderer(renderer);



	// An interactor

	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =

	//	vtkSmartPointer<vtkRenderWindowInteractor>::New();

	renderWindowInteractor->SetRenderWindow(renderWindow);



	// Set the custom type to use for interaction.

	//vtkSmartPointer<MouseInteractorHighLightActor> style =

	//	vtkSmartPointer<MouseInteractorHighLightActor>::New();

	style->SetDefaultRenderer(renderer);



	renderWindowInteractor->SetInteractorStyle(style);

	vtkSmartPointer<vtkBoxWidget> boxWidget =
		vtkSmartPointer<vtkBoxWidget>::New();
	boxWidget->SetInteractor(renderWindowInteractor);

	for (int i = 0; i < numberOfSpheres; ++i)

	{

		vtkSmartPointer<vtkSphereSource> source =

			vtkSmartPointer<vtkSphereSource>::New();

		double x, y, z, radius;

		x = vtkMath::Random(-5, 5);

		y = vtkMath::Random(-5, 5);

		z = vtkMath::Random(-5, 5);

		radius = vtkMath::Random(.5, 1.0);

		source->SetRadius(radius);

		source->SetCenter(x, y, z);

		source->SetPhiResolution(11);

		source->SetThetaResolution(21);

		vtkSmartPointer<vtkPolyDataMapper> mapper =

			vtkSmartPointer<vtkPolyDataMapper>::New();

		mapper->SetInputConnection(source->GetOutputPort());

		vtkSmartPointer<vtkActor> actor =

			vtkSmartPointer<vtkActor>::New();

		actor->SetMapper(mapper);

		double r, g, b;

		r = vtkMath::Random(.4, 1.0);

		g = vtkMath::Random(.4, 1.0);

		b = vtkMath::Random(.4, 1.0);

		actor->GetProperty()->SetDiffuseColor(r, g, b);

		actor->GetProperty()->SetDiffuse(.8);

		actor->GetProperty()->SetSpecular(.5);

		actor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);

		actor->GetProperty()->SetSpecularPower(30.0);

		renderer->AddActor(actor);

			
		if (i==2)
		{
			boxWidget->SetProp3D(actor);
			boxWidget->SetPlaceFactor(1.25); // Make the box 1.25x larger than the actor
			boxWidget->PlaceWidget();
		}
		/*else
		{
			boxWidget->SetProp3D(this->GetDefaultRenderer()->GetActors()->GetLastActor());

		}*/
		

		

	}

	vtkSmartPointer<vtkMyCallback> callback =
		vtkSmartPointer<vtkMyCallback>::New();
	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

	boxWidget->On();


	renderer->SetBackground(.3, .4, .5);



	//	vtkSmartPointer<vtkBoxWidget> boxWidget =
	//		vtkSmartPointer<vtkBoxWidget>::New();
	//	boxWidget->SetInteractor(renderWindowInteractor);
	//	/*if (this->LastPickedActor)
	//	{*/
	//		boxWidget->SetProp3D(renderer->GetActors()->GetLastActor());
	///*	}
	//	else
	//	{
	//		boxWidget->SetProp3D(this->GetDefaultRenderer()->GetActors()->GetLastActor());

	//	}*/
	//	boxWidget->SetPlaceFactor(1.25); // Make the box 1.25x larger than the actor
	//	boxWidget->PlaceWidget();

	//	vtkSmartPointer<vtkMyCallback> callback =
	//		vtkSmartPointer<vtkMyCallback>::New();
	//	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

	//	boxWidget->On();

	// Render and interact

	renderWindow->Render();

	renderWindowInteractor->Initialize();

	renderWindowInteractor->Start();

	getchar();

	return EXIT_SUCCESS;

}
