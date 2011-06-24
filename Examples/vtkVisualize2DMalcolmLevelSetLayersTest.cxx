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

#include "vtkVisualize2DMalcolmLevelSetLayers.h"

#include "itkMalcolmSparseLevelSetBase.h"
#include "itkBinaryImageToMalcolmSparseLevelSetAdaptor.h"

#include "itkNumericSeriesFileNames.h"
#include "itkImageFileReader.h"

#include "itkImage.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionIteratorWithIndex.h"


int main( int argc, char* argv[] )
{
  typedef unsigned char PixelType;
  const unsigned int Dimension = 2;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::NumericSeriesFileNames NameGeneratorType;

  NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
  nameGenerator->SetSeriesFormat( "/home/ajg23/Kishore/Malcolm/%d.png" );
  nameGenerator->SetStartIndex( 0 );
  nameGenerator->SetEndIndex( 50 );
  nameGenerator->SetIncrementIndex( 1 );

  typedef double LevelSetOutputType;

  typedef itk::BinaryImageToMalcolmSparseLevelSetAdaptor< ImageType >
      BinaryToSparseAdaptorType;

  typedef BinaryToSparseAdaptorType::LevelSetType           SparseLevelSetType;


  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader2 = ReaderType::New();
  reader2->SetFileName( "/home/ajg23/Kishore/cells2D.png" );
  reader2->Update();

  typedef vtkVisualize2DMalcolmLevelSetLayers< ImageType, Dimension >
      VisualizationType;
  VisualizationType::Pointer viewer = VisualizationType::New();
  viewer->SetScreenCapture( true );

  for( int i = 0; i < 50; i++ )
  {
    ReaderType::Pointer temp_reader = ReaderType::New();
    temp_reader->SetFileName( nameGenerator->GetFileNames()[i] );
    temp_reader->Update();

    BinaryToSparseAdaptorType::Pointer adaptor = BinaryToSparseAdaptorType::New();
    adaptor->SetInputImage( temp_reader->GetOutput() );
    adaptor->Initialize();

    SparseLevelSetType::Pointer LevelSet = adaptor->GetSparseLevelSet();

    viewer->SetInputImage( reader2->GetOutput() );
    viewer->SetLevelSet( LevelSet );
    viewer->Update();
  }


  return EXIT_SUCCESS;
}
