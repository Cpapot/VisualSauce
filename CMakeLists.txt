cmake_minimum_required(VERSION 3.15)

project(VisualSauce VERSION 0.0.1)

if(DEFINED JUCE_DIR)
    set(_juce_path "${JUCE_DIR}")
else()
    set(_juce_path "${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
endif()

if(NOT EXISTS "${_juce_path}/CMakeLists.txt")
    message(FATAL_ERROR
        "JUCE not found at '${_juce_path}'.\n"
        "Initialize submodules with:\n"
        "  git submodule update --init --recursive\n"
        "or set -DJUCE_DIR=/path/to/JUCE")
endif()

add_subdirectory("${_juce_path}" JUCE)

juce_add_plugin(VisualSauce
    COMPANY_NAME "VisualSauce"
    PLUGIN_MANUFACTURER_CODE Vsce
    PLUGIN_CODE Vsau
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PRODUCT_NAME "VisualSauce"
    FORMATS VST3 Standalone
)

target_sources(VisualSauce PRIVATE
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp
    Source/apvts.cpp
    Source/OscilloscopeEditor.cpp
    Source/OscilloscopeEditor.h
)

target_compile_definitions(VisualSauce
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(VisualSauce
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

if(WIN32 AND TARGET VisualSauce_VST3)
    add_custom_command(TARGET VisualSauce_VST3 POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            "-DPLUGIN_SOURCE=${CMAKE_CURRENT_BINARY_DIR}/VisualSauce_artefacts/$<CONFIG>/VST3/VisualSauce.vst3"
            "-DPLUGIN_DEST=C:/Program Files/Common Files/VST3/VisualSauce.vst3"
            "-DPLUGIN_CONFIG=$<CONFIG>"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/copy_vst3_to_system.cmake"
        VERBATIM)
endif()
