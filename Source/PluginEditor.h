#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class VisualSauceAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit VisualSauceAudioProcessorEditor(VisualSauceAudioProcessor&);
    ~VisualSauceAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    VisualSauceAudioProcessor& audioProcessor;
};
