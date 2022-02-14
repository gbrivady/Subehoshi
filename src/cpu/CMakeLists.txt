add_executable(appCPU main.c
                   vector2d.c
                   update.c
                   ../body.c
                   ../display.c)

find_package(SDL2 REQUIRED)

target_include_directories(appCPU PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(appCPU PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/cpu)
target_link_libraries(appCPU ${SDL2_LIBRARIES})