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




        static constexpr int    step = 5;
        static constexpr int    scopeSize = 512;
        int findTriggerIndex (int numSamplesToDraw, int numValidSamples);

        int                             historyWriteIndex = 0;
        int                             samplesInScope = 0;
        int                             historySamples = 0;
        static constexpr int            historySize = scopeSize * 8;
        std::array<float, scopeSize>    localData {};
        std::array<float, historySize>  tempBuffer {};
        std::array<float, historySize>  historyBuffer {};

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscilloscopeEditor)
};