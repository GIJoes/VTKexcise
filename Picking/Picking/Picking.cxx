//#include <vtkVersion.h>
//#include <vtkSmartPointer.h>
//#include <vtkActor.h>
//#include<vtkCubeSource.h>
//#include <vtkRendererCollection.h>
//#include <vtkCellArray.h>
//#include <vtkInteractorStyleTrackballCamera.h>
//#include <vtkObjectFactory.h>
//#include <vtkPlaneSource.h>
//#include <vtkPoints.h>
//#include <vtkPolyData.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkPropPicker.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkRenderer.h>
//#include<vtkProperty.h>
//#include "build/NewInteractor.h"
//#include<vtkBoxWidget.h>
//#include <vtkCommand.h>
//#include <vtkTransform.h>
//// Handle mouse events
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
//
//class MouseInteractorStyle2 : public vtkInteractorStyleTrackballCamera
//{
//  public:
//    static MouseInteractorStyle2* New();
//    vtkTypeMacro(MouseInteractorStyle2, vtkInteractorStyleTrackballCamera);
//
//    virtual void OnLeftButtonDown()
//    {
//      int* clickPos = this->GetInteractor()->GetEventPosition();
//	  cout << "clickPos:" << clickPos[0] << "  " << clickPos[1] << "  " << clickPos[2] << endl;
//      // Pick from this location.
//      vtkSmartPointer<vtkPropPicker>  picker =
//        vtkSmartPointer<vtkPropPicker>::New();
//      picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
//
//	  if (!picker->GetActor())
//	  {
//		  cout << "Pick NULL!!" << endl;
//	  }
//
//      double* pos = picker->GetPickPosition();
//	  cout << "pos[0] = " << pos[0] << ",pos[1] = " << pos[1] << ",pos[2] = " << pos[2] << endl;
//
//      //Create a cube
//      vtkSmartPointer<vtkCubeSource> cubeSource =
//        vtkSmartPointer<vtkCubeSource>::New();
//	  cubeSource->SetCenter(pos[0], pos[1], pos[2]);
//	  cubeSource->SetXLength(0.1);
//	  cubeSource->SetYLength(0.1);
//	  cubeSource->SetZLength(0.1);
//
//      //Create a mapper and actor
//      vtkSmartPointer<vtkPolyDataMapper> mapper =
//        vtkSmartPointer<vtkPolyDataMapper>::New();
//      mapper->SetInputConnection(cubeSource->GetOutputPort());
//
//      vtkSmartPointer<vtkActor> actor =
//        vtkSmartPointer<vtkActor>::New();
//      actor->SetMapper(mapper);
//	  actor->GetProperty()->SetColor(0.5,0,0.5);
//
//
//      //this->GetInteractor()->GetRenderWindow()->GetRenderers()->GetDefaultRenderer()->AddActor(actor);
//      this->GetDefaultRenderer()->AddActor(actor);
//      // Forward events
//	vtkSmartPointer<vtkBoxWidget> boxWidget =
//	vtkSmartPointer<vtkBoxWidget>::New();
//	boxWidget->SetInteractor(this->Interactor);
//
//	boxWidget->SetProp3D(this->GetDefaultRenderer()->GetActors()->GetLastActor());
//	boxWidget->SetPlaceFactor(1.25); // Make the box 1.25x larger than the actor
//	boxWidget->PlaceWidget();
//
//	vtkSmartPointer<vtkMyCallback> callback =
//	vtkSmartPointer<vtkMyCallback>::New();
//	boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
//
//	boxWidget->On();
//
//      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
//    }
//
//  private:
//
//};
//
//vtkStandardNewMacro(MouseInteractorStyle2);
//
//// Execute application.za
//int main(int, char *[])
//{
//  vtkSmartPointer<vtkPlaneSource> planeSource =
//    vtkSmartPointer<vtkPlaneSource>::New();
//  planeSource->Update();
//
//  // Create a polydata object
//  vtkPolyData* polydata = planeSource->GetOutput();
//
//  // Create a mapper
//  vtkSmartPointer<vtkPolyDataMapper> mapper =
//    vtkSmartPointer<vtkPolyDataMapper>::New();
//#if VTK_MAJOR_VERSION <= 5
//  mapper->SetInput ( polydata );
//#else
//  mapper->SetInputData ( polydata );
//#endif
//
//  // Create an actor
//  vtkSmartPointer<vtkActor> actor =
//    vtkSmartPointer<vtkActor>::New();
//  actor->SetMapper ( mapper );
//
//  std::cout << "Actor address: " << actor << std::endl;
//
//  // A renderer and render window
//  vtkSmartPointer<vtkRenderer> renderer =
//    vtkSmartPointer<vtkRenderer>::New();
//  vtkSmartPointer<vtkRenderWindow> renderWindow =
//    vtkSmartPointer<vtkRenderWindow>::New();
//  renderWindow->AddRenderer ( renderer );
//
//  // An interactor
//  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//    vtkSmartPointer<vtkRenderWindowInteractor>::New();
//  renderWindowInteractor->SetRenderWindow ( renderWindow );
//
//  // Set the custom stype to use for interaction.
//  vtkSmartPointer<MouseInteractorStyle2> style =
//    vtkSmartPointer<MouseInteractorStyle2>::New();
//  style->SetDefaultRenderer(renderer);
//
//  renderWindowInteractor->SetInteractorStyle( style );
//
//  // Add the actors to the scene
//  renderer->AddActor ( actor );
//  renderer->SetBackground ( 0,0,1 );
//
//  //vtkSmartPointer<vtkBoxWidget> boxWidget =
//	 // vtkSmartPointer<vtkBoxWidget>::New();
//  //boxWidget->SetInteractor(renderWindowInteractor);
//
//  //boxWidget->SetProp3D(renderer->GetActors()->GetLastActor());
//  //boxWidget->SetPlaceFactor(1.25); // Make the box 1.25x larger than the actor
//  //boxWidget->PlaceWidget();
//
//  //vtkSmartPointer<vtkMyCallback> callback =
//	 // vtkSmartPointer<vtkMyCallback>::New();
//  //boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
//
//  //boxWidget->On();
//  // Render and interact
//  renderWindow->Render();
//  renderWindowInteractor->Initialize();
//  renderWindowInteractor->Start();
//
//  return EXIT_SUCCESS;
//}
