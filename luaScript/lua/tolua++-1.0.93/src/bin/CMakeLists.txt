set(EXE_NAME tolua++.bin) 
 
include_directories(../../include ../../../lua-5.1.5/src) 
link_directories(../../lib /usr/local/lib)
 
set(DIR_SRCS tolua.c toluabind.c) 
add_executable(${EXE_NAME} ${DIR_SRCS}) 
target_link_libraries(${EXE_NAME} tolua++ lua m dl) 
set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


