#pragma once

#include "PluginProcessor.h"
#include "OscilloscopeEditor.h"

class VisualSauceAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit VisualSauceAudioProcessorEditor(VisualSauceAudioProcessor&);
    ~VisualSauceAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    VisualSauceAudioProcessor&  audioProcessor;
    OscilloscopeEditor          MyOscilloscope { audioProcessor };
};
