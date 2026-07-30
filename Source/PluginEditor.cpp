#include "PluginEditor.h"

VisualSauceAudioProcessorEditor::VisualSauceAudioProcessorEditor(VisualSauceAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    juce::ignoreUnused(audioProcessor);
    setSize(800, 450);
}

void VisualSauceAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(24.0f);
    g.drawFittedText("Hello World", getLocalBounds(), juce::Justification::centred, 1);
}

void VisualSauceAudioProcessorEditor::resized()
{
}
