
set(SRCS
TAnalysisTask.cxx
TAnalysisSelector.cxx
TAnalysisManager.cxx
TAnaInputHandler.cxx
TAnaTaskExample.cxx
)

set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/ParallelTasks
  ${ROOT_INCLUDE_DIR}
)
include_directories( ${INCLUDE_DIRECTORIES})


set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
link_directories( ${LINK_DIRECTORIES})

String(REPLACE ".cxx" ".h" HDRS "${SRCS}")
ROOT_GENERATE_DICTIONARY( G__Analysis ${HDRS} LINKDEF AnalysisLinkDef.h)
list(APPEND SRCS G__Analysis.cxx)
  
add_library(Analysis SHARED ${SRCS} ${HDRS})
target_link_libraries(Analysis ${ROOT_LIBRARIES} ${ALIEN_LIB} ${APPMON_LIB})

install(TARGETS Analysis
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION lib COMPONENT RUNTIME
ARCHIVE DESTINATION lib COMPONENT DEVELOPMENT)

add_par(Analysis)
