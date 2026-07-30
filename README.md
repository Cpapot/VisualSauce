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

The plugin targets are generated as VST3 and Standalone.