file(GLOB SOURCE_FILES src/*.cpp)

idf_component_register(SRCS "${SOURCE_FILES}"
                    INCLUDE_DIRS "include"
                    ) 