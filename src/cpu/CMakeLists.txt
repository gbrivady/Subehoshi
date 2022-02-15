add_executable(appCPU main.c
                   vector2d.c
                   update.c
                   ../body.c
                   ../display.c)

target_include_directories(appCPU PRIVATE 
${CMAKE_SOURCE_DIR}/inc 
${CMAKE_SOURCE_DIR}/inc/cpu
)
set_target_properties(appCPU PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
target_include_directories(appCPU PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(appCPU ${SDL2_LIBRARIES})