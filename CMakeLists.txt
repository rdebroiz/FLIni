cmake_minimum_required(VERSION 2.8)

project(florent)

# Qt
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
set(CMAKE_AUTOMOC ON)

# Find includes in corresponding build directories
 include_directories(
     model
     presenter
     view
     )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(${PROJECT_NAME}_CPP
    main.cpp
    MainWindow.cpp
    model/IniDocumentModel.cpp
    presenter/IniDocumentPresenter.cpp
    view/MainWidget.cpp
    view/ServiceDescriptionWidget.cpp
    view/FieldDescriptionWidget.cpp
    view/FieldListWidget.cpp
    view/DocumentPreviewWidget.cpp
    view/CommandWidget.cpp
    )

set(${PROJECT_NAME}_H
    MainWindow.h
    model/IniDocumentModel.h
    model/IniDocumentIO.h
    presenter/IniDocumentPresenter.h
    view/MainWidget.h
    view/FieldListWidget.h
    view/ServiceDescriptionWidget.h
    view/FieldDescriptionWidget.h
    view/DocumentPreviewWidget.h
    view/CommandWidget.h
    )

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_CPP}
    ${${PROJECT_NAME}_H}
    )

target_link_libraries(${PROJECT_NAME}
    ${QT_LIBRARIES}
    )
