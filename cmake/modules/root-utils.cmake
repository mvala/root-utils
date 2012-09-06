function(add_par PACKAGE)
  if(PACKAGE)
  message(STATUS "Generating ${PACKAGE}")
  add_custom_target(${PACKAGE}.par
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/pars
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} tar --exclude=.svn -czhf ${CMAKE_SOURCE_DIR}/pars/${PACKAGE}.par ${PACKAGE}
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "${PACKAGE}.par has been created in ${CMAKE_SOURCE_DIR}/pars"
#    DEPENDS ${PARSRCS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
  
  add_dependencies(par-all ${PACKAGE}.par)
  
  endif(PACKAGE)
endfunction(add_par PACKAGE)