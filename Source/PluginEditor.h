#pragma once

#include <memory>

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
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> glowAttachment, gainAttachment, intensityAttachment;
    juce::Slider glowSlider, gainSlider, intensitySlider;


    VisualSauceAudioProcessor&  audioProcessor;
    OscilloscopeEditor          MyOscilloscope { audioProcessor };
};
