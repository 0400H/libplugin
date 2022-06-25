file(GLOB SOURCES_AND_HEADERS "*/*.hpp" "*/*.h")

install(FILES ${SOURCES_AND_HEADERS}
        DESTINATION include/${PROJECT_NAME})
