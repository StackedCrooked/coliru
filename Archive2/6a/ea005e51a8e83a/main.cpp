VTKViewer::VTKViewer(QWidget *parent) : QWidget(parent)
{
  QVTKWidget *qvtkwidget = new QVTKWidget;
  qvtkwidget->setSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::MinimumExpanding);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  vtkRenderWindow *renderWindow = qvtkwidget->GetRenderWindow();
  renderWindow->AddRenderer(renderer);

  auto axes = vtkSmartPointer<vtkAxesActor>::New();
  axes->SetXAxisLabelText("x");
  axes->SetYAxisLabelText("y");
  axes->SetZAxisLabelText("z");

  auto orientationMarker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  orientationMarker->SetInteractor(qvtkwidget->GetInteractor());
  orientationMarker->SetOrientationMarker(axes);
  orientationMarker->SetEnabled(1);
}