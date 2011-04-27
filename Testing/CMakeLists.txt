set( SRC
  HeaderTest.cxx
)

foreach( var ${SRC} )
  add_executable( ${var} ${var}.cxx )
endforeach()

