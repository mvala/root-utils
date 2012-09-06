
set(SRCS
TPeacVerifierSel.cxx
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
ROOT_GENERATE_DICTIONARY( G__PeacUtils ${HDRS} LINKDEF PeacUtilsLinkDef.h)
list(APPEND SRCS G__PeacUtils.cxx)
  
add_library(PeacUtils SHARED ${SRCS} ${HDRS})
target_link_libraries(PeacUtils ${ROOT_LIBRARIES} ${ALIEN_LIB} ${APPMON_LIB})

install(TARGETS PeacUtils
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION lib COMPONENT RUNTIME
ARCHIVE DESTINATION lib COMPONENT DEVELOPMENT)

add_par(PeacUtils)
