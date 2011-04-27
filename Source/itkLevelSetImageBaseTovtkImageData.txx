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

#ifndef __itkLevelSetImageBaseTovtkImageData_txx
#define __itkLevelSetImageBaseTovtkImageData_txx

#include "vtkImageData.h"
#include "itkLevelSetImageBaseTovtkImageData.h"

namespace itk
{
template< class TImage >
LevelSetImageBaseTovtkImageData< TImage >
::LevelSetImageBaseTovtkImageData()
{
  m_Converter = ConverterType::New();
}

template< class TImage >
void
LevelSetImageBaseTovtkImageData< TImage >
::SetInput( const LevelSetType* iLevelSet )
{
  if( iLevelSet == NULL )
    {
    itkGenericExceptionMacro( <<"iLevelSet is NULL" );
    }
  if( iLevelSet->GetImage() == NULL )
    {
    itkGenericExceptionMacro( <<"iLevelSet->GetImage() is NULL" );
    }
  m_Converter->SetInput( iLevelSet->GetImage() );
}

template< class TImage >
vtkImageData*
LevelSetImageBaseTovtkImageData< TImage >
::GetOutput() const
{
  return m_Converter->GetOutput();
}

template< class TImage >
void
LevelSetImageBaseTovtkImageData< TImage >
::Update()
{
  m_Converter->Update();
}
}
#endif // __itkLevelSetImageBaseTovtkImageData_txx
