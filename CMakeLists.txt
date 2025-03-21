cmake_minimum_required(VERSION 3.30)
project(TowerDefRedone)

set(CMAKE_CXX_STANDARD 20)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add raylib support
set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Getting ${LIB1} from Github")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${LIB1}")
endif()

add_executable(TowerDefRedone main.cpp
        Tile.h
        Tile.cpp
        GameGrid.h
        GameGrid.cpp
        Pathfinding.h
        Pathfinding.cpp
        Enemy.h
        Enemy.cpp
        Controls.h
        Controls.cpp
        Spawning.h
        Spawning.cpp
        Level.h
        Level.cpp
        UI.h
        UI.cpp
)

# set the include directory
target_include_directories(TowerDefRedone PRIVATE ${raylib_INCLUDE_DIRS})

# link all libraries to the project
target_link_libraries(TowerDefRedone PRIVATE ${LIB1})
