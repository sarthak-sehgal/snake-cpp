find_library(SDL2_LIB SDL2 REQUIRED)

add_executable(snake main.cpp food.cpp game.cpp snake.cpp)

target_link_libraries(snake ${SDL2_LIB})
