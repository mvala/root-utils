
set(SRCS
TTaskThread.cxx
TTaskParallel.cxx
TTaskManager.cxx
TTaskStress.cxx
TTaskMonitor.cxx
)

set(INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
)
include_directories( ${INCLUDE_DIRECTORIES})


set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
link_directories( ${LINK_DIRECTORIES})

String(REPLACE ".cxx" ".h" HDRS "${SRCS}")
ROOT_GENERATE_DICTIONARY( G__ParallelTasks ${HDRS} LINKDEF ParallelTasksLinkDef.h)
list(APPEND SRCS G__ParallelTasks.cxx)
  
add_library(ParallelTasks SHARED ${SRCS} ${HDRS})
target_link_libraries(ParallelTasks ${ROOT_LIBRARIES} ${ALIEN_LIB} ${APPMON_LIB})

install(TARGETS ParallelTasks
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION lib COMPONENT RUNTIME
ARCHIVE DESTINATION lib COMPONENT DEVELOPMENT)
