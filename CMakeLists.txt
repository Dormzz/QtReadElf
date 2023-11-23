cmake_minimum_required(VERSION 3.26.4)
project(QtReadELF)

set(TOOL_NAME QtReadELF)

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


if (UNIX)
    if (APPLE)
        add_executable(${TOOL_NAME} MACOSX_BUNDLE
                ${PROJECT_FILES}
        )

        set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
        target_link_libraries(${TOOL_NAME}
                ${QT5_LIBRARIES}
        )
        add_custom_command(TARGET ${TOOL_NAME} POST_BUILD
                COMMAND /usr/local/opt/qt@5/bin/macdeployqt ${CMAKE_BINARY_DIR}/${TOOL_NAME}.app -dmg)
    else ()
        add_executable(${TOOL_NAME}
                ${PROJECT_FILES}
        )
        set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
        target_link_libraries(${TOOL_NAME}
                ${QT5_LIBRARIES}
        )
        file(WRITE "${CMAKE_BINARY_DIR}/default.desktop" "[Desktop Entry]\nType=Application\nName=${TOOL_NAME}\nExec=AppRun %F\nIcon=default\nComment=Edit this default file\nTerminal=true\nCategories=Application;\n")

        add_custom_target(PackUbuntu${TOOL_NAME}WithQtEnv ALL
                COMMAND ${CMAKE_BINARY_DIR}/../linux-pack/linuxdeployqt-continuous-x86_64.AppImage ${CMAKE_BINARY_DIR}/${TOOL_NAME} -appimage
                COMMAND /bin/bash -c "mv ${TOOL_NAME}-*.AppImage ${TOOL_NAME}-WithQtEnv.AppImage"
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                VERBATIM
        )

        add_dependencies(PackUbuntu${TOOL_NAME}WithQtEnv ${TOOL_NAME})

    endif ()
elseif (WIN32)
    add_executable(${TOOL_NAME}
            ${PROJECT_FILES}
    )
    set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
    target_link_libraries(${TOOL_NAME}
            ${QT5_LIBRARIES}
    )

endif ()