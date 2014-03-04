file(GLOB_RECURSE SOURCES_C "*.c")
file(GLOB_RECURSE SOURCES_CPP "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SC_MACHINE_ROOT}/bin/extensions)

add_library (scp_interpreter SHARED ${SOURCES_CPP} ${SOURCES_C} ${HEADERS})

include_directories("${SCP_MACHINE_ROOT}/scp_lib/src" "${SCP_MACHINE_ROOT}/scp_interpreter/src" ${SC_MEMORY_SRC} ${GLIB2_INCLUDE_DIRS})
add_dependencies(scp_interpreter scp_lib sc-memory)

target_link_libraries(scp_interpreter scp_lib)

#install_targets("/lib/sc-memory/extensions" scp_interpreter)
