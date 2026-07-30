#pragma once

#include <array>

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "PluginProcessor.h"

class OscilloscopeEditor : public juce::Component, public juce::Timer
{
    public:
        explicit OscilloscopeEditor(VisualSauceAudioProcessor& processor);
        ~OscilloscopeEditor() override;

        void timerCallback() override;
        void paint(juce::Graphics& g) override;
        void readFromFifo(float* destinationBuffer, int numSamplesToRead);
    private:
        VisualSauceAudioProcessor& audioProcessor;

        static constexpr int scopeSize = 512;
        int samplesInScope = 0;
        std::array<float, scopeSize> localData {};


        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscilloscopeEditor)
};