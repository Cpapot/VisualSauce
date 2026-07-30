if(NOT PLUGIN_CONFIG STREQUAL "Release")
    if(EXISTS "${PLUGIN_DEST}")
        file(REMOVE_RECURSE "${PLUGIN_DEST}")
    endif()
    return()
endif()

if(NOT EXISTS "${PLUGIN_SOURCE}")
    message(FATAL_ERROR "VST3 bundle not found at ${PLUGIN_SOURCE}")
endif()

get_filename_component(plugin_dest_parent "${PLUGIN_DEST}" DIRECTORY)
file(MAKE_DIRECTORY "${plugin_dest_parent}")
file(REMOVE_RECURSE "${PLUGIN_DEST}")

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${PLUGIN_SOURCE}" "${PLUGIN_DEST}"
    RESULT_VARIABLE copy_result
    OUTPUT_VARIABLE copy_output
    ERROR_VARIABLE copy_output)

if(copy_result)
    message(FATAL_ERROR "Failed to copy VST3 bundle to ${PLUGIN_DEST}\n${copy_output}")
endif()