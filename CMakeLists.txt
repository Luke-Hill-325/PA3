cmake_minimum_required(VERSION 3.10)  # Specify minimum CMake version

project(PA3)  # Set the project name

# Specify the C++ standard you want to use
set(CMAKE_CXX_STANDARD 17)

# Add an executable target
add_executable(PA3 PA3_Luke_Hill.cpp) 

target_link_libraries(PA3 ${PostgreSQL_LIBRARIES} cgraph gvc)
