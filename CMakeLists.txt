cmake_minimum_required(VERSION 3.26.4)
project(QtReadELF)

set(EXENAME QtReadELF)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# windos 需要设置环境变量 Qt6_DIR=C:\Qt\6.6.1\mingw_64

set(PROJECT_FILES
        main.cpp
        testui.cpp
        testui.h
        TestUI.ui
)


if (UNIX)
    if (APPLE)
        find_package(Qt6Widgets REQUIRED)
        find_package(Qt6 COMPONENTS
                Core
                Gui
                Widgets
                REQUIRED)
        add_executable(${EXENAME} MACOSX_BUNDLE
                ${PROJECT_FILES}
        )

        set(QT6_LIBRARIES Qt6::Core Qt6::Gui Qt6::Widgets)
        target_link_libraries(${EXENAME}
                ${QT6_LIBRARIES}
        )
        # 假如mac安装了 binutils 后，里面的strip工具会和 xcode的工具重名，导致打包冲突，需要修改 binutils的strip名字为其他名字才行
        set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
        add_custom_command(TARGET ${EXENAME} POST_BUILD
                COMMAND /usr/local/opt/qt@6/bin/macdeployqt ${CMAKE_BINARY_DIR}/${EXENAME}.app -dmg)
    else ()
        find_package(Qt5Widgets REQUIRED)
        find_package(Qt5 COMPONENTS
                Core
                Gui
                Widgets
                REQUIRED)
        add_executable(${EXENAME}
                ${PROJECT_FILES}
        )
        set(QT5_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
        target_link_libraries(${EXENAME}
                ${QT5_LIBRARIES}
        )
        file(WRITE "${CMAKE_BINARY_DIR}/default.desktop" "[Desktop Entry]\nType=Application\nName=${EXENAME}\nExec=AppRun %F\nIcon=default\nComment=Edit this default file\nTerminal=true\nCategories=Application;\n")

        add_custom_target(PackUbuntu${EXENAME}WithQtEnv ALL
                COMMAND ${CMAKE_BINARY_DIR}/../linux-pack/linuxdeployqt-continuous-x86_64.AppImage ${CMAKE_BINARY_DIR}/${EXENAME} -appimage
                COMMAND /bin/bash -c "mv ${EXENAME}-*.AppImage ${EXENAME}-WithQtEnv.AppImage"
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                VERBATIM
        )

        add_dependencies(PackUbuntu${EXENAME}WithQtEnv ${EXENAME})

    endif ()
elseif (WIN32)
    find_package(Qt6Widgets REQUIRED)
    find_package(Qt6 COMPONENTS
            Core
            Gui
            Widgets
            REQUIRED)
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