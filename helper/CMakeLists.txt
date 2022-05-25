find_package(SFML COMPONENTS audio CONFIG REQUIRED)

set(SRC 
    "src/main.cpp"
    "src/sdl2_loader.cpp"
    )

add_library(helper SHARED ${SRC})
configure_node_module(helper)
target_link_libraries(helper PRIVATE sdl2::includes sfml-audio)
