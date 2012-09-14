
set(SRCS
Event.cxx
TAnaEventInputHandler.cxx
TAnaEventTaskExample.cxx
)

set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/ParallelTasks
  ${CMAKE_SOURCE_DIR}/Analysis
  ${ROOT_INCLUDE_DIR}
)
include_directories( ${INCLUDE_DIRECTORIES})


set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
link_directories( ${LINK_DIRECTORIES})

String(REPLACE ".cxx" ".h" HDRS "${SRCS}")
ROOT_GENERATE_DICTIONARY( G__EventAnalysis ${HDRS} LINKDEF EventAnalysisLinkDef.h)
list(APPEND SRCS G__EventAnalysis.cxx)
  
add_library(EventAnalysis SHARED ${SRCS} ${HDRS})
target_link_libraries(EventAnalysis ${ROOT_LIBRARIES} ${ALIEN_LIB} ${APPMON_LIB})

install(TARGETS EventAnalysis
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION lib COMPONENT RUNTIME
ARCHIVE DESTINATION lib COMPONENT DEVELOPMENT)

add_par(EventAnalysis)
