set( SRC
  HeaderTest
  vtkVisualize2DLevelSetImageBaseTest
  vtkVisualize2DWhitakerLevelSetTest
)

foreach( var ${SRC} )
  add_executable( ${var} ${var}.cxx )
  target_link_libraries( ${var} ${ITK_LIBRARIES} ${VTK_LIBRARIES} )
endforeach()

