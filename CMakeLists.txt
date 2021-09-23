cmake_minimum_required(VERSION 3.14)

project(CadenceLibQML LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_VERSION_MAJOR 1.0.0)
# 不翻译Qt文件, Qt Creator更新后这货耗费的时间太大
# 而且还傻乎乎的不检查文件是否修改一股脑的翻译
set(NO_CREATE_TS_FILE TRUE)

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

include_directories("${PROJECT_SOURCE_DIR}/3rdparty/spdlog/include")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(spdlog_cxx spdlog)
    add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/spdlog)
else()
    set(spdlog_cxx spdlog_shared_lib)
    add_library(spdlog_shared_lib SHARED "")
    target_include_directories(spdlog_shared_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/spdlog/include)
    target_sources(spdlog_shared_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/spdlog/include/spdlog/spdlog.h)
    set_target_properties(spdlog_shared_lib
         PROPERTIES
            # -fPIC 生成位置无关代码
            POSITION_INDEPENDENT_CODE 1
            # 设置库版本号为工程主版本号
            SOVERSION ${PROJECT_VERSION_MAJOR}
            # 修改输出文件名字
            OUTPUT_NAME "spdlog_shared"
            # 为Debug模式下生成的库添加后缀
            DEBUG_POSTFIX "_d"
            )
    target_compile_options(spdlog_shared_lib PRIVATE -std=c++11)
endif()

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

    if(!NO_CREATE_TS_FILE)
        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
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
    if(!NO_CREATE_TS_FILE)
        qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
endif()

target_compile_definitions(CadenceLibQML
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(CadenceLibQML
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql ${spdlog_cxx})
