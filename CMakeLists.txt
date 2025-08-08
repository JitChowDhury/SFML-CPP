# 1. Minimum version of CMake required
cmake_minimum_required(VERSION 3.16)

# 2. Name of your project and the programming language it uses
project(MySFMLProject LANGUAGES CXX)

# 3. Tell CMake to use modern C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 4. Point CMake to the SFML config file
# Replace this path with where YOU extracted SFML
set(SFML_DIR "H:/Downloads/SFML-2.6.2-windows-vc17-64-bit/SFML-2.6.2/lib/cmake/SFML")

# 5. Ask CMake to find SFML and load its components
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 6. Add your source file (src/main.cpp)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp
    src/Ball.cpp
    src/GameObject.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Animation.cpp
    src/PowerUp.cpp


    include/Game.h
    include/Ball.h
    include/GameObject.h
    include/Player.h
    include/Enemy.h
    include/Animation.h
    include/PowerUp.h
)

# 7. Link SFML libraries to your executable
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-network
    sfml-audio
)

# 8. Optional: Make sure SFML include directories are added
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SFML_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
