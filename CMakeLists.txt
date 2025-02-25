cmake_minimum_required(VERSION 3.20)

project(DoxygenPlugin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QtCreator REQUIRED COMPONENTS Core ProjectExplorer CppEditor TextEditor)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Add a CMake option that enables building your plugin with tests.
# You don't want your released plugin binaries to contain tests,
# so make that default to 'NO'.
# Enable tests by passing -DWITH_TESTS=ON to CMake.
option(WITH_TESTS "Builds with tests" NO)

if(WITH_TESTS)
  # Look for QtTest
  find_package(Qt6 REQUIRED COMPONENTS Test)

  # Tell CMake functions like add_qtc_plugin about the QtTest component.
  set(IMPLICIT_DEPENDS Qt::Test)

  # Enable ctest for auto tests.
  enable_testing()
endif()

add_qtc_plugin(DoxygenPlugin
  LONG_DESCRIPTION_MD README.md
  PLUGIN_DEPENDS
    QtCreator::Core
    QtCreator::ProjectExplorer
    QtCreator::CppEditor
    QtCreator::TextEditor
  DEPENDS
    Qt::Widgets
    QtCreator::ExtensionSystem
    QtCreator::Utils
  SOURCES
   doxygen.cpp doxygen.h
   doxygen.qrc
   doxygen_global.h
   doxygenconstants.h
   doxygenfilesdialog.cpp doxygenfilesdialog.h doxygenfilesdialog.ui
   doxygenplugin.cpp doxygenplugin.h
   doxygensettings.cpp doxygensettings.h
   doxygensettingsstruct.cpp doxygensettingsstruct.h
   doxygensettingswidget.cpp doxygensettingswidget.h doxygensettingswidget.ui
)
