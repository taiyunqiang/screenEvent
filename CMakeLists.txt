cmake_minimum_required(VERSION 2.8)

project(screenEvent)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_CXX_STANDARD 11)
FIND_PACKAGE(Qt5 COMPONENTS Core Gui Widgets Qml Quick REQUIRED)

set(SOURCE_FILES
    main.cpp
    xcbeventhandle.cpp
    )

set(kwin_QT_LIBS
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Core_LIBRARIES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(screenEvent ${kwin_QT_LIBS})
target_link_libraries(screenEvent
    -lxcb
    -lxcb-randr
    )
install(TARGETS screenEvent DESTINATION /usr/bin/)


