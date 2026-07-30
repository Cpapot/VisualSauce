# VisualSauce

JUCE-based VST3/Standalone plugin skeleton for audio visualization.

## Project layout

```
VisualSauce/
├── JUCE/                  # JUCE submodule
├── assets/                # Images/fonts/other resources
├── Source/                # Plugin source code
├── .gitmodules            # JUCE submodule declaration
└── CMakeLists.txt         # CMake build entrypoint
```

## Setup

1. Initialize JUCE submodule:

```bash
git submodule update --init --recursive
```

2. Configure and build:

```bash
cmake -S . -B build
cmake --build build
```

If you are using a multi-config generator such as Visual Studio, omit `CMAKE_BUILD_TYPE` during configure and select the config at build time, for example:

```bash
cmake --build build --config Release
```

The plugin targets are generated as VST3 and Standalone.