#include "PluginEditor.h"

VisualSauceAudioProcessorEditor::VisualSauceAudioProcessorEditor(VisualSauceAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    juce::ignoreUnused(audioProcessor);
    audioProcessor.setEditorOpen(true);
    addAndMakeVisible (MyOscilloscope);

    setSize(audioProcessor.getEditorWidth(), audioProcessor.getEditorHeight());
    setResizable(false, true);
    setResizeLimits(400, 300, 4000, 3000);

}

VisualSauceAudioProcessorEditor::~VisualSauceAudioProcessorEditor()
{
    audioProcessor.setEditorOpen(false);
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
    audioProcessor.setEditorSize(getWidth(), getHeight());
    MyOscilloscope.setBounds (10, 10, getWidth() - 20, getHeight() - 20);
}
