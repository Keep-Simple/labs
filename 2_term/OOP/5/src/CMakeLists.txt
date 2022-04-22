cmake_minimum_required(VERSION 3.5)

project(lab5 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(
  PROJECT_SOURCES
  main.cpp
  triangle.cpp
  triangle.h
  trianglesides.h
  triangleangles.h
  triangleheights.h
  widget.cpp
  widget.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(
    lab5
    ${PROJECT_SOURCES}
  )
else()
  if(ANDROID)
    add_library(
      lab5 SHARED
      ${PROJECT_SOURCES}
    )
  else()
    add_executable(
      lab5
      ${PROJECT_SOURCES}
    )
  endif()
endif()

target_link_libraries(lab5 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
