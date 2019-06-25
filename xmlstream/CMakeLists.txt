# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.1)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /usr/share/qt4)

set (CMAKE_PREFIX_PATH "/usr/share/qt4/")
SET(QT_QMAKE_EXECUTABLE /usr/lib/qt4/bin/qmake)
SET(QT_BINARY_DIR   /usr/lib/qt4/bin/)

set(incprefix "/usr/include/qt4/")
set(libprefix "/usr/lib/")

SET(QT_CORE_INCLUDE_DIR ${incprefix}/QtCore/)
SET(QT_CORE_LIBRARY ${libprefix}/libQtCore.so)

SET(QT_WIDGET_INCLUDE_DIR ${incprefix}/QtGui)


SET(QT_GUI_INCLUDE_DIR ${incprefix}/QtGui/)
SET(QT_GUI_LIBRARY ${libprefix}/libQtGui.so)

SET(QT_SVG_INCLUDE_DIR ${incprefix}/QtSvg)
SET(QT_SVG_LIBRARY ${libprefix}/libQtSvg.so)

SET(QT_XML_INCLUDE_DIR ${incprefix}/QtXml)
SET(QT_XML_LIBRARY ${libprefix}/libQtXml.so)

SET(QT_TEST_INCLUDE_DIR ${incprefix}/QtTest)
SET(QT_TEST_LIBRARY ${libprefix}/libQtTest.so)

include_directories(
  ${incprefix}
  ${incprefix}/Qt/
  ${incprefix}/QtGui/
  ${incprefix}/QtCore/
  ${incprefix}/QtSvg/
  ${incprefix}/QtTest/
  ${incprefix}/QtXml
  )


# 生成的最后文件的名称
set(APP xmlstream)
# 项目信息
project (${APP})
set(TARGET_NAME ${APP})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")

# set(QT Core Gui Widget )
set(QT Core Gui Svg Xml)
find_package(Qt4 REQUIRED ${QT})
set(QTLib ${QT_QTCORE_LIBRARY} ${QT_GUI_LIBRARY} ${QT_SVG_LIBRARY} ${QT_XML_LIBRARY} )
link_libraries(${QTLib} )


# 查找当前目录下的所有源文件 # 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(${APP} ${DIR_SRCS})
