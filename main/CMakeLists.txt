file(GLOB SOURCE_FILES src/*.cpp)

idf_component_register(SRCS "${SOURCE_FILES}"
                    INCLUDE_DIRS "include"
                    REQUIRES lvgl_cpp)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++20)
