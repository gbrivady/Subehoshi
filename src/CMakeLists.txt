add_executable(app main.c
                   vector2d.c
                   update.c
                   body.c
                   display.c)

find_package(SDL2 REQUIRED)

target_include_directories(app PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(app ${SDL2_LIBRARIES})
