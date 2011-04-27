project( LevelSetVisualization )

cmake_minimum_required( VERSION 2.8 )

find_package( ITK REQUIRED )
if( ITK_FOUND )
  include( ${ITK_USE_FILE} )
endif()

find_package( VTK REQUIRED )
if( VTK_FOUND )
  include( ${VTK_USE_FILE} )
endif()

add_subdirectory( Examples )
add_subdirectory( Testing )
