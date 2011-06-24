add_executable( Whitaker vtkVisualize2DWhitakerLevelSetLayersTest.cxx )
target_link_libraries( Whitaker ${ITK_LIBRARIES} ${VTK_LIBRARIES} )

add_executable( Shi vtkVisualize2DShiLevelSetLayersTest.cxx )
target_link_libraries( Shi ${ITK_LIBRARIES} ${VTK_LIBRARIES} )

add_executable( Malcolm vtkVisualize2DMalcolmLevelSetLayersTest.cxx )
target_link_libraries( Malcolm ${ITK_LIBRARIES} ${VTK_LIBRARIES} )
