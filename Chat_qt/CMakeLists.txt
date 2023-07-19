cmake_minimum_required(VERSION 3.16)

project(Chat_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appChat_qt
    main.cpp
)

qt_add_qml_module(appChat_qt
    URI Chat_qt
    VERSION 1.0
    QML_FILES
            ConversationPage.qml
            ContactPage.qml
            Main.qml
    RESOURCES
           "images/Albert_Einstein.png"
           "images/Albert_Einstein@2x.png"
           "images/Albert_Einstein@3x.png"
           "images/Albert_Einstein@4x.png"
           "images/Ernest_Hemingway.png"
           "images/Ernest_Hemingway@2x.png"
           "images/Ernest_Hemingway@3x.png"
           "images/Ernest_Hemingway@4x.png"
           "images/Hans_Gude.png"
           "images/Hans_Gude@2x.png"
           "images/Hans_Gude@3x.png"
           "images/Hans_Gude@4x.png"
)

set_target_properties(appChat_qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appChat_qt
    PRIVATE Qt6::Quick
)

install(TARGETS appChat_qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
