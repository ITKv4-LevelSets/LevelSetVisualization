#ifndef __itkLevelSetImageBaseTovtkImageData_h
#define __itkLevelSetImageBaseTovtkImageData_h

#include "itkProcessObject.h"
#include "itkLevelSetImageBase.h"
#include "itkImageToVTKImageFilter.h"

namespace itk
{
template< class TImage >
class LevelSetImageBaseTovtkImageData : public ProcessObject
{
public:
  typedef LevelSetImageBaseTovtkImageData Self;
  typedef ProcessObject                   Superclass;
  typedef SmartPointer< Self >            Pointer;
  typedef SmartPointer< const Self >      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageToVTKImageFilter, ProcessObject);

  typedef TImage                          ImageType;

  typedef LevelSetImageBase< ImageType >  LevelSetType;

  typedef ImageToVTKImageFilter< ImageType >  ConverterType;
  typedef typename ConverterType::Pointer     ConverterPointer;

  void SetInput( const LevelSetType* iLevelSet );

  vtkImageData* GetOutput() const;

  void Update();

protected:
  LevelSetImageBaseTovtkImageData();
  ~LevelSetImageBaseTovtkImageData();

private:
  LevelSetImageBaseTovtkImageData( const Self& );
  void operator = ( const Self& );

  ConverterPointer m_Converter;
};
}

#include "itkLevelSetImageBaseTovtkImageData.txx"
#endif // __itkLevelSetImageBaseTovtkImageData_h
