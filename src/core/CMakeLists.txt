include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(NOT "${SRC_HEADER_DIRS}" MATCHES "${CMAKE_CURRENT_SOURCE_DIR}")
    set(SRC_HEADER_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR};${SRC_HEADER_DIRS}"
        CACHE
        STRING
        "change SRC_HEADER_DIRS"
        FORCE)
endif()

include_directories(AFTER SYSTEM ${SRC_HEADER_DIRS})

add_subdirectory(logger)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/logger)

add_subdirectory(library)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/library)

add_subdirectory(factory)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/factory)

add_subdirectory(register)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/register)

add_subdirectory(container)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/container)
