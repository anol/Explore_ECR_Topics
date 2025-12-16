cmake_minimum_required(VERSION 4.1)
project(Explore_ECR_Topics)

set(CMAKE_CXX_STANDARD 20)

set(MY_DATA_DIR "${CMAKE_SOURCE_DIR}/data")
set(MY_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory("src/Variant/Target/${PROJECT_NAME}")

