cmake_minimum_required(VERSION 3.26.4)
project(QtReadELF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5Widgets REQUIRED)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(PROJECT_FILES
        main.cpp
        testui.cpp
        testui.h
        TestUI.ui
)


if (APPLE)
    add_executable(QtReadELF MACOSX_BUNDLE
            ${PROJECT_FILES}
    )

    set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
    target_link_libraries(QtReadELF
            ${QT5_LIBRARIES}
    )
    add_custom_command(TARGET QtReadELF POST_BUILD
            COMMAND /usr/local/opt/qt@5/bin/macdeployqt ${CMAKE_BINARY_DIR}/QtReadELF.app -dmg)
elseif (UNIX)
    add_executable(QtReadELF
            ${PROJECT_FILES}
    )
    set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
    target_link_libraries(QtReadELF
            ${QT5_LIBRARIES}
    )
    add_custom_command(TARGET QtReadELF POST_BUILD
            COMMAND /usr/local/opt/qt@5/bin/macdeployqt ${CMAKE_BINARY_DIR}/QtReadELF.app -dmg)
elseif (WIN32)
    add_executable(QtReadELF
            ${PROJECT_FILES}
    )
    set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
    target_link_libraries(QtReadELF
            ${QT5_LIBRARIES}
    )

endif ()