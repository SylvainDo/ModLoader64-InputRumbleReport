set(NODE_DIR "${NDK_DIR}" CACHE STRING "Node development files")
set(NODE_ADDON_DIR "${NDK_ADDON_DIR}" CACHE STRING "Node addon development files")
set(HOST_BINARY "NODE.EXE" CACHE STRING "Delay load host binary")

set(TARGET_ARCH ${CMAKE_CXX_COMPILER})
cmake_path(GET TARGET_ARCH PARENT_PATH TARGET_ARCH)
cmake_path(GET TARGET_ARCH STEM TARGET_ARCH)

list(APPEND COMPILE_DEFINITIONS "NAPI_VERSION=8")
list(APPEND COMPILE_DEFINITIONS "NAPI_CPP_EXCEPTIONS")
list(APPEND COMPILE_DEFINITIONS "HOST_BINARY=\"${HOST_BINARY}\"")

list(APPEND INCLUDE_DIRECTORIES "${NODE_DIR}/include")
list(APPEND INCLUDE_DIRECTORIES "${NODE_DIR}/include/node")
list(APPEND INCLUDE_DIRECTORIES "${NODE_ADDON_DIR}")

list(APPEND LINK_LIBRARIES "${NODE_DIR}/lib/${TARGET_ARCH}/node.lib")
list(APPEND LINK_LIBRARIES "delayimp.lib")

add_library(node-addon-api INTERFACE IMPORTED)
set_target_properties(node-addon-api PROPERTIES 
    INTERFACE_COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS}"
    INTERFACE_INCLUDE_DIRECTORIES "${INCLUDE_DIRECTORIES}"
    INTERFACE_LINK_LIBRARIES "${LINK_LIBRARIES}"
    INTERFACE_LINK_OPTIONS "/DELAYLOAD:${HOST_BINARY}"
    INTERFACE_SOURCES "${NODE_DIR}/src/win_delay_load_hook.cc")

function(configure_node_module target)
    target_link_libraries(${target} PRIVATE node-addon-api)
    set_target_properties(${target} PROPERTIES
        PREFIX ""
        SUFFIX ".node")
endfunction()
