cmake_minimum_required(VERSION 3.3)
project(ipcam_test)


list(
    APPEND SOURCE_FILES
    main.cpp
    IPCamServiceTest_main.cpp
    IPCamSearchTest.cpp
    ../ArgumentParsing.cpp
    ../IPCamService.cpp
    ../IPCamSearch.cpp
    ../MultiThread.cpp
    ../PortScanner.cpp    
)

list(
    APPEND HEADER_FILES
    catch.hpp
    catch_wth_main.hp
    ../Common.hpp
    ../CamNotificationDefs.hpp
    ../ArgumentParsing.hpp
    ../IPCamService.hpp
    ../IPCamSearch.hpp
    ../MultiThread.hpp
    ../PortScanner.hpp
    ../osx_compat.hpp  
)

add_executable(${PROJECT_NAME}  ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wno-unknown-pragmas -Wno-unused-variable")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

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

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_library(LIBDISPATCH dispatch REQUIRED)
    target_link_libraries(${PROJECT_NAME} ${LIBDISPATCH})
    target_link_libraries(${PROJECT_NAME} -lBlocksRuntime)
endif()

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
)
