/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __vtkVisualize2DWhitakerLevelSetLayers_h
#define __vtkVisualize2DWhitakerLevelSetLayers_h

#include "itkLightObject.h"

#include "itkWhitakerSparseLevelSetBase.h"

#include "itkImageToVTKImageFilter.h"
#include "itkWhitakerLevelSetTovtkImageData.h"

#include "vtkImageData.h"
#include "vtkMarchingSquares.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkImageActor.h"
#include "vtkScalarBarActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkImageShiftScale.h"

#include "vtkCaptureScreen.h"
#include "vtkPNGWriter.h"

template< class TInputImage, typename TOutput, unsigned int VDimension >
class vtkVisualize2DWhitakerLevelSetLayers : public itk::LightObject
{
public:
  typedef vtkVisualize2DWhitakerLevelSetLayers  Self;
  typedef LightObject                           Superclass;
  typedef itk::SmartPointer< Self >             Pointer;
  typedef itk::SmartPointer< const Self >       ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(vtkVisualize2DWhitakerLevelSetLayers, LightObject);

  typedef TInputImage     InputImageType;
  typedef itk::WhitakerSparseLevelSetBase< TOutput, VDimension > LevelSetType;

  void SetInputImage( const InputImageType * iImage )
    {
    m_ImageConverter->SetInput( iImage );
    try
      {
      m_ImageConverter->Update();
      }
    catch( itk::ExceptionObject& e )
      {
      std::cout << e << std::endl;
      return;
      }

    m_Count = 0;
    }

  void SetLevelSet( LevelSetType *f )
    {
    m_LevelSetConverter->SetInput( f );
    m_Count = 0;
    }

  void SetScreenCapture( const bool& iCapture )
    {
    m_ScreenCapture = iCapture;
    }

  void SetNumberOfLevels( const unsigned int& iLevel )
    {
    if( iLevel > 0 )
      {
      m_NumberOfLevels = iLevel;
      }
    }

  void SetLevelLimit( double iLimit )
    {
    if( iLimit > 0. )
      {
      m_LevelLimit = iLimit;
      }
    }

  void Update()
    {
    try
      {
      m_LevelSetConverter->Update();
      }
    catch( itk::ExceptionObject& e )
      {
      std::cout << e << std::endl;
      return;
      }

    vtkSmartPointer< vtkMarchingSquares > contours =
      vtkSmartPointer< vtkMarchingSquares >::New();
    contours->SetInput( m_LevelSetConverter->GetOutput() );
    contours->GenerateValues( m_NumberOfLevels, - m_LevelLimit, m_LevelLimit );
    contours->Update();

    vtkSmartPointer< vtkPolyDataMapper > mapper =
        vtkSmartPointer< vtkPolyDataMapper >::New();
    mapper->SetInputConnection( contours->GetOutputPort() );
    mapper->SetScalarRange( - m_LevelLimit, m_LevelLimit );

    vtkSmartPointer< vtkActor > ContourActor =
        vtkSmartPointer< vtkActor >::New();
    ContourActor->SetMapper( mapper );
    ContourActor->GetProperty()->SetLineWidth( 2. );
    ContourActor->GetProperty()->SetColor( 1, 0, 0 );
    //ContourActor->GetProperty()->SetOpacity( 1.0 );

    vtkSmartPointer< vtkImageShiftScale > shift =
        vtkSmartPointer< vtkImageShiftScale >::New();
    shift->SetInput( m_ImageConverter->GetOutput() );
    shift->SetOutputScalarTypeToUnsignedChar();
    shift->Update();

    vtkSmartPointer< vtkImageActor > input_Actor =
        vtkSmartPointer< vtkImageActor >::New();
    input_Actor->SetInput( shift->GetOutput() );

    vtkSmartPointer< vtkScalarBarActor > scalarbar =
        vtkSmartPointer< vtkScalarBarActor >::New();
    scalarbar->SetLookupTable( mapper->GetLookupTable() );
    scalarbar->SetTitle( "Level Set Values" );
    scalarbar->SetNumberOfLabels( m_NumberOfLevels );

    vtkSmartPointer< vtkRenderer > ren =
        vtkSmartPointer< vtkRenderer >::New();
    ren->SetBackground( 0.5, 0.5, 0.5 );

    vtkSmartPointer< vtkRenderWindowInteractor > iren =
        vtkSmartPointer< vtkRenderWindowInteractor >::New();

    vtkSmartPointer< vtkRenderWindow > renWin =
        vtkSmartPointer< vtkRenderWindow >::New();

    ren->AddActor ( input_Actor );
    ren->AddActor ( ContourActor );
    ren->AddActor2D( scalarbar );

    iren->SetRenderWindow( renWin );

    renWin->AddRenderer( ren );
    renWin->Render();

    if( m_ScreenCapture )
      {
      std::string filename;
      std::stringstream yo;
      yo << "snapshot_" << m_Count;
      filename = yo.str();
      filename.append ( ".png" );

      vtkCaptureScreen< vtkPNGWriter > capture ( renWin );
      // begin mouse interaction
//      iren->Start();
      capture( filename );
      ++m_Count;
      }
    else
      {
      iren->Start();
      }
    }

protected:
  vtkVisualize2DWhitakerLevelSetLayers() : Superclass(),
    m_Count( 0 ),
    m_NumberOfLevels( 1 ),
    m_LevelLimit( 0 ),
    m_ScreenCapture( false )
    {
    m_ImageConverter = ImageConverterType::New();
    m_LevelSetConverter = LevelSetConverterType::New();
    }

  ~vtkVisualize2DWhitakerLevelSetLayers()
    {}

private:
  vtkVisualize2DWhitakerLevelSetLayers ( const Self& );
  void operator = ( const Self& );

  ImageConverterPointer     m_ImageConverter;
  LevelSetConverterPointer  m_LevelSetConverter;

  itk::IdentifierType m_Count;
  unsigned int        m_NumberOfLevels;
  double              m_LevelLimit;
  bool                m_ScreenCapture;

};
#endif
