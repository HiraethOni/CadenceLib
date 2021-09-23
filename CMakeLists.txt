cmake_minimum_required(VERSION 3.14)

project(CadenceLibQML LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Sql REQUIRED)

set(TS_FILES resource/CadenceLibQML_zh_CN.ts)

set(PROJECT_SOURCES
        ${TS_FILES}
        ./resource/qml.qrc
)

AUX_SOURCE_DIRECTORY(./src PROJECT_SOURCES)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/spdlog)
include_directories("${PROJECT_SOURCE_DIR}/3rdparty/spdlog/include")

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D_DEBUG)
    add_definitions(-DQT_QML_DEBUG)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    必须在add_executable里面加入头文件路径
#    不然Q_OBJEC这个宏无法宏展开,然后报错:undefined reference 'vtable for xxx'
    file(GLOB_RECURSE HEADER_FILES include/*.h)
    qt_add_executable(CadenceLibQML
        ${PROJECT_SOURCES} ${HEADER_FILES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(CadenceLibQML SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(CadenceLibQML
          ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(CadenceLibQML
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(CadenceLibQML
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql spdlog)
