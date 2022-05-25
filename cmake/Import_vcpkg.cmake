add_library(sdl2::includes INTERFACE IMPORTED)
set_target_properties(sdl2::includes PROPERTIES 
    INTERFACE_INCLUDE_DIRECTORIES "${VCPKG_DIR}/installed/${VCPKG_TARGET_TRIPLET}/include/SDL2")
