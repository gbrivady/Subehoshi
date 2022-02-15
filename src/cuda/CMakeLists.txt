add_executable(appCUDA main.cu
                       vector2d.cu
                       update.cu
                       ../body.c
                       display_cu.c
)
target_include_directories(appCUDA PRIVATE 
${CMAKE_SOURCE_DIR}/inc 
${CMAKE_SOURCE_DIR}/inc/cuda
)

enable_language(CUDA)
set_target_properties(appCUDA
    PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON
)
set_target_properties(appCUDA PROPERTIES CUDA_ARCHITECTURES "70")

find_package(SDL2 REQUIRED)
target_include_directories(appCUDA PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(appCUDA ${SDL2_LIBRARIES})