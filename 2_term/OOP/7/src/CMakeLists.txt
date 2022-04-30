cmake_minimum_required(VERSION 3.5)

project(datastructure LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(dir ${CMAKE_CURRENT_SOURCE_DIR} "build")
# set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
# set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
# set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
# set(CMAKE_BUILD_DIRECTORY ${dir})
# set(CMAKE_BINARY_DIR ${dir})
# set(EXECUTABLE_OUTPUT_PATH ${dir})
# set(LIBRARY_OUTPUT_PATH ${dir}lib)
# set(CMAKE_CACHEFILE_DIR ${dir})

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(
  PROJECT_SOURCES
  main.cpp
  widget.cpp
  widget.h
  customdeque.cpp
  customdeque.h
  deque.cpp
  deque.h
  node.h
)

# list(TRANSFORM PROJECT_SOURCES PREPEND "src/")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(
    datastructure
    ${PROJECT_SOURCES}
  )
else()
  if(ANDROID)
    add_library(
      datastructure SHARED
      ${PROJECT_SOURCES}
    )
  else()
    add_executable(
      datastructure
      ${PROJECT_SOURCES}
    )
  endif()
endif()

target_link_libraries(datastructure PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
