cmake_minimum_required(VERSION 3.16)

project(FileSystemWatcher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 COMPONENTS Quick Network REQUIRED)


set(PROJECT_SOURCES
    main.cpp
    controller.h controller.cpp
    event.h event.cpp
    mywatcher.h mywatcher.cpp
    eventtablemodel.h eventtablemodel.cpp)

qt_add_executable(appFileSystemWatcher WIN32
    ${PROJECT_SOURCES}
)

qt_add_qml_module(appFileSystemWatcher
    URI FileSystemWatcher
    VERSION 1.0
    QML_FILES main.qml 
)

target_compile_definitions(appFileSystemWatcher
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appFileSystemWatcher
    PRIVATE Qt6::Quick Qt6::Network)
