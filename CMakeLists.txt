cmake_minimum_required(VERSION 3.26.4)
project(QtReadELF)

set(EXENAME QtReadELF)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# windos 需要设置环境变量 Qt6_DIR=C:\Qt\6.6.1\mingw_64

find_package(Qt6 COMPONENTS
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
            ${UI_HEADERS}
    )
    set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
    target_link_libraries(QtReadELF
            ${QT5_LIBRARIES}
    )
elseif (WIN32)
    add_executable(${EXENAME}
            ${PROJECT_FILES}
    )
    set(QT6_LIBRARIES Qt6::Core Qt6::Gui Qt6::Widgets)
    target_link_libraries(${EXENAME}
            ${QT6_LIBRARIES}
    )
    message("copy ${CMAKE_BINARY_DIR}/${EXENAME}.exe ${CMAKE_BINARY_DIR}/${EXENAME}")
    add_custom_command(
            TARGET ${EXENAME}
            POST_BUILD
            COMMAND $ENV{Qt6_DIR}/bin/windeployqt.exe --dir ${CMAKE_BINARY_DIR}/${EXENAME} ${CMAKE_BINARY_DIR}/${EXENAME}.exe
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${EXENAME}.exe" "${CMAKE_BINARY_DIR}/${EXENAME}"
            COMMAND powershell -Command "Compress-Archive -Path '${CMAKE_BINARY_DIR}/${EXENAME}' -DestinationPath '${CMAKE_BINARY_DIR}/${EXENAME}_With_QTEnv.zip'"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

endif ()