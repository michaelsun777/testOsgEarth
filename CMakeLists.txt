cmake_minimum_required(VERSION 3.21)
project(testOsgearth)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

# C standard
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)


# find_package(Boost REQUIRED COMPONENTS thread chrono)
# if(Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIR})
#     message(STATUS "Boost_FOUND")
# endif()

find_package(X11 REQUIRED)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)

SET(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES}
        ${Qt5Network_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5WebEngineWidgets_LIBRARIES} )

INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS})



#SET(CEF_ROOT 3rd/cef/code/) #${CMAKE_CURRENT_SOURCE_DIR}/
#message(STATUS "CEF_ROOT=${CEF_ROOT}")
#INCLUDE_DIRECTORIES(${CEF_ROOT}/include)
#INCLUDE_DIRECTORIES(${CEF_ROOT})
#

INCLUDE_DIRECTORIES(3rd/Osg/include)
INCLUDE_DIRECTORIES(3rd/Osg)
INCLUDE_DIRECTORIES(3rd/osgearth/src/osgEarth/)
INCLUDE_DIRECTORIES(3rd/osgearth/src/)
#INCLUDE_DIRECTORIES(3rd/osgQt/include/osgQOpenGL)
#INCLUDE_DIRECTORIES(3rd/osgQt/include)

INCLUDE_DIRECTORIES(src/UI)
INCLUDE_DIRECTORIES(/usr/local/include)
INCLUDE_DIRECTORIES(/usr/include)


#添加连接库路径

#link_directories(3rd/cef/lib)
link_directories(/usr/lib/x86_64-linux-gnu)
link_directories(/usr/local/lib/)
link_directories(/usr/local/lib64)
#link_directories(3rd/Osg/build/lib)
#link_directories(${QT_LIBRARIES})
#link_directories(/home/amplesky/osg/packages/Osg/OpenSceneGraph/build/lib)



add_subdirectory(3rd/osgearth)
# add_subdirectory(3rd/osgQt)

add_executable(testOsgearth
main.cpp
src/GisManager.cpp
src/GisContainer.cpp
#src/ViewerWidget.cpp
#src/GraphicsWindowQt.cpp
src/UI/mainwindow.cpp
src/UI/osggisdlg.cpp
#src/UI/mmwindow.cpp
src/UI/windowmain.cpp
#src/QtOsgEarthWidget.cpp
# src/earthwnd.cpp
# src/earthWidget.cpp
# src/AdapterWidget.cpp
# src/pickEventHandler.cpp
#3rd/cef/code/simple_app.cc

#3rd/cef/code/simple_handler.cc
#3rd/cef/code/simple_handler_linux.cc
#src/UI/mainwindow.cpp
)


target_link_libraries(testOsgearth PRIVATE
pthread
-losg -losgViewer -losgDB -losgGA
-losgEarth
-lOpenGL
-lOpenThreads
-lGL
-lglut
-losgQOpenGL
#-lcef -lEGL -lGLESv2 -lvk_swiftshader -lvulkan -lX11
# 【CEF】cef相关库链接
#-lcef
#libcef_dll_wrapper.a
# -lX11

#-ldl
${QT_LIBRARIES}
# ${Boost_LIBRARIES}
)
