# Variables
set(SOURCES
    vector.c
)
set(HEADERS
    vector.h
)

# Main library
add_library(laughing_train STATIC ${SOURCES} ${HEADERS})

# Install targets
Install(TARGETS laughing_train DESTINATION lib)
Install(FILES ${HEADERS} DESTINATION include/laughing_train)
