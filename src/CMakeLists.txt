add_executable(app main.c
                   vector2d.c)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/inc)
