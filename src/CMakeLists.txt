add_subdirectory(card)
add_subdirectory(structure)
add_subdirectory(utils)

add_library(${PROJECT_NAME}_MAIN OBJECT
    main.cpp
)
