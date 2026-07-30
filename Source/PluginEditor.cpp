#include "PluginEditor.h"

VisualSauceAudioProcessorEditor::VisualSauceAudioProcessorEditor(VisualSauceAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    juce::ignoreUnused(audioProcessor);
    addAndMakeVisible (MyOscilloscope);

    setSize(800, 450);
    setResizable(true, true);
    setResizeLimits(400, 300, 4000, 3000);

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
    MyOscilloscope.setBounds (10, 10, getWidth() - 20, getHeight() - 20);
}
