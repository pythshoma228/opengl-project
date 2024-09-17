cmake_minimum_required(VERSION 3.29)
#TODO
#Build Debug and Release dirs 

set(PROJECT_NAME app)
project(${PROJECT_NAME} LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20) 

set( LOCAL_PATH "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${LOCAL_PATH}/bin")
set( RESOURCES_DIR "${LOCAL_PATH}")
file(COPY "res" DESTINATION ${RESOURCES_DIR})

set(SOURCE "src/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCE})

find_package(SFML 2.6.1 COMPONENTS window REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-window)

find_package(OpenGL REQUIRED)
include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})


find_package(GLEW REQUIRED)
include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})

find_package(glm CONFIG REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM})

find_package(Stb REQUIRED)
include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
add_library(stb_image STATIC  "src/stb_image.cpp")
target_link_libraries(${PROJECT_NAME} stb_image)