set( SRC
  HeaderTest
)

foreach( var ${SRC} )
  add_executable( ${var} ${var}.cxx )
endforeach()

