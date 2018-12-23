cmake_minimum_required(VERSION 3.5)
project(OOP_Basic)

set(CMAKE_CXX_STANDARD 11)
aux_source_directory(. DIREXE)
include_directories(./Basic ./StanfordCPPLib ./StanfordCPPLib/private)

add_subdirectory(Basic)
add_subdirectory(StanfordCPPLib)
add_executable(code Basic/Basic.cpp)
target_link_libraries(code BasicSrc CPPLib )
