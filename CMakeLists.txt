# cmake最低版本依赖
cmake_minimum_required(VERSION 3.15)

# 设置工程名称
project(DzTools)

# 使用c++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加宏定义
add_definitions(-D_HAS_STD_BYTE=0)

# 添加三方库
# 添加qt{需要配置环境变量}
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if("${CMAKE_CXX_COMPILE_ID}" STREQUAL "GUN")
    set(Qt5_DIR $ENV{QT_GCC_DIR})
elseif("${CMAKE_CXX_COMPILE_ID}" STREQUAL "MSVC")
    set(Qt5_DIR $ENV{QT_MSVC_DIR})
endif ()

find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)
SET(QT_LIBS Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network)
list(APPEND LINK_LIBS ${QT_LIBS})

message(STATUS "qtPath:${Qt5_DIR}")

# 添加opencv{需要配置环境变量}
set(OpenCV_DIR $ENV{OPENCV48_DIR})
message(STATUS "opencvPath: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIR})
    message(STATUS "opencvIncludeDir: ${OpenCV_INCLUDE_DIR}")
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GUN" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
        list(APPEND LINK_LIBS ${OpenCV_LIBS})
    else ()
        list(APPEND LINK_LIBS "opencv_world")
    endif ()
endif ()

# 结束添加三方库

# 收集源文件、头文件、UI文件、资源文件等
# 添加源文件到变量SRC中
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)

# 添加头文件在变量INC中
file(GLOB INC ${PROJECT_SOURCE_DIR}/*.h)

# 添加UI文件在变量UI中
#set(UI ${PROJECT_SOURCE_DIR}/planWidget.ui)

# 添加头文件包括
include_directories(${PROJECT_SOURCE_DIR})

# 添加资源文件到变量RES中
#set(RES ${PROJECT_SOURCE_DIR}/res.qrc)

# 结束收集源文件、头文件、UI文件、资源文件

# 生成目标文件
# 设置二进制文件输出目录
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# 生成dll
add_library(${PROJECT_NAME}
        ${SRC}
        ${INC}
        Tools/LogBox/LogBox.cpp
        Tools/LogBox/LogBox.h
        Tools/CrashHandle/CrashHandle.h
        #${UI}
        #${RES}
)

# 设置lib和dll文件输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
# 生成目标文件结束

# 链接
link_directories(${CMAKE_SOURCE_DIR}/Lib/${CMAKE_BUILD_TYPE})

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBS})
# 链接结束

# 设置调试版本城市的可执行文件后缀包含“d”
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX d)

# release调试生成pdb
if (CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif ()

# 打印工程CMAKE信息
message(STATUS "${PROJECT_NAME} 工程CMAKE信息")
message(STATUS "===========================================================")
message(STATUS "    操作系统:    ${CMAKE_SYSTEM}")
message(STATUS "    CPU架构:    ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "    构建类型:    ${CMAKE_BUILD_TYPE}")
message(STATUS "    依赖库:      ${LINK_LIBS}")
message(STATUS "    源文件:      ${SRC}")
message(STATUS "    头文件:      ${INC}")
message(STATUS "    UI文件:     ${UI}")
message(STATUS "    资源文件:    ${RES}")
message(STATUS "    exe输出路径: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "============================================================")