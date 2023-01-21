cmake_minimum_required(VERSION 3.22)
project(libps3)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC 
        "src/*.h" , 
        "src/*.hpp" , 
        "src/*.c" , 
        "src/*.cpp" , 
        "src/**/*.h" , 
        "src/**/*.hpp" , 
        "src/**/*.c" , 
        "src/**/*.cpp" , 
        "src/*.cpp" , 
        "src/*.h" ,
)

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/project")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/project/cheat")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/project/dependencies")