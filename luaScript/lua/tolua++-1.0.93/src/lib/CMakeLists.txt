set(LIB_NAME tolua++) 
 
include_directories(../../../lua-5.1.5/src ../../include) 
 
aux_source_directory(. DIR_SRCS) 
add_library(${LIB_NAME} STATIC ${DIR_SRCS}) 
set_target_properties(${LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}../../../../build)


