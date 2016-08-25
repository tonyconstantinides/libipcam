cmake_minimum_required(VERSION 3.3)

set(CMAKE_XCODE_ORGANIZATIONNAME "EVA Automation, Inc.")

project(ipcam)

list(
    APPEND SOURCE_FILES
    src/ArgumentParsing.cpp
    src/IPCamService.cpp
    src/IPCamSearch.cpp
    src/PortScanner.cpp
)

list(
    APPEND HEADER_FILES
    src/Common.hpp
    src/osx_compat.hpp
    src/ArgumentParsing.hpp
    src/IPCamService.hpp
    src/IPCamSearch.hpp
    src/PortScanner.hpp
    src/CamNotificationDefs.hpp	
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wno-unknown-pragmas -Wno-unused-variable")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    find_library(LIBBLOCKSRUNTIME BlocksRuntime REQUIRED)
    target_link_libraries(${PROJECT_NAME} ${LIBBLOCKSRUNTIME})
endif()

find_library(LIBFOUNDATION jetpack_foundation REQUIRED)
find_path(FOUNDATION_INCLUDE_DIR foundation/foundation.hpp PATH_SUFFIXES jetpack)
target_link_libraries(${PROJECT_NAME} ${LIBFOUNDATION})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${FOUNDATION_INCLUDE_DIR})

# evartp
find_library(LIBEVARTP evartp REQUIRED)
find_path(EVARTP_INCLUDE_DIR evartp/RtspManager.hpp PATH_SUFFIXES evartp)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${EVARTP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}  ${LIBEVARTP})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include/ipcam)


set (EXT_PROJECTS_DIR src/thirdparty)
add_subdirectory(${EXT_PROJECTS_DIR}/catch)
include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
enable_testing(true)