set(M64_APIDIR "${CMAKE_CURRENT_SOURCE_DIR}/m64p-api")

set(SRC
    "src/autoconfig.c"
    "src/autoconfig.h"
    "src/config.c"
    "src/config.h"
    "src/osal_dynamiclib_win32.c"
    "src/osal_dynamiclib.h"
    "src/osal_preproc.h"
    "src/plugin.c"
    "src/plugin.h"
    "src/sdl_key_converter.c"
    "src/sdl_key_converter.h"
    "src/version.h"
    "src/sdl2_loader.cpp"
    )

add_library(InputPlugin SHARED ${SRC})
target_include_directories(InputPlugin PRIVATE ${M64_APIDIR})
target_link_libraries(InputPlugin PRIVATE sdl2::includes)
set_target_properties(InputPlugin PROPERTIES OUTPUT_NAME "mupen64plus-input-sdl-rr")
