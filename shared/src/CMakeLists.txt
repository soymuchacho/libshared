CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET( INCLUDE_PATH
	${PROJECT_SOURCE_DIR}/
)

INCLUDE_DIRECTORIES( ${INCLUDE_PATH} )
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../build)
AUX_SOURCE_DIRECTORY(./ LIB_SRC)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${LIB_SRC})

ADD_DEFINITIONS(-D__LINUX__ -Dlinux -Wno-deprecated  -std=c++11)

INSTALL( TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/../../build
)
