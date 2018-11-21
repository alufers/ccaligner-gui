cmake_minimum_required(VERSION 3.1.0)

project(ccaligner-gui)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Concurrent CONFIG REQUIRED)


if(UNIX)
    set (EXTRA_FLAGS ${EXTRA_FLAGS} -lpthread)
endif(UNIX)

# Populate a CMake variable with the sources
set(ccaligner-gui_SRCS
    mainwindow.ui
    mainwindow.cpp
    progressdialog.cpp
    ccaligneroptions.cpp
    progressdialog.ui
    fileselector.ui
    fileselector.cpp
    aboutdialog.ui
    aboutdialog.cpp
    main.cpp
)
# Tell CMake to create the helloworld executable
add_executable(ccaligner-gui ${ccaligner-gui_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(ccaligner-gui Qt5::Widgets Qt5::Concurrent ${EXTRA_FLAGS})
