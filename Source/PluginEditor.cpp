#include "PluginEditor.h"

VisualSauceAudioProcessorEditor::VisualSauceAudioProcessorEditor(VisualSauceAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    juce::ignoreUnused(audioProcessor);
    audioProcessor.setEditorOpen(true);
    addAndMakeVisible (MyOscilloscope);
    addAndMakeVisible (glowSlider);
    addAndMakeVisible (gainSlider);
    addAndMakeVisible (intensitySlider);

    glowSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    gainSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    intensitySlider.setSliderStyle (juce::Slider::LinearHorizontal);

    glowSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    intensitySlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);

    setSize(audioProcessor.getEditorWidth(), audioProcessor.getEditorHeight());
    setResizable(false, true);
    setResizeLimits(400, 300, 4000, 3000);

    auto& apvts = audioProcessor.apvts;
    glowAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "glow", glowSlider);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "gain", gainSlider);
    intensityAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "intensity", intensitySlider);

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

    constexpr int margin = 10;
    constexpr int spacing = 16;
    constexpr int sliderHeight = 55;

    auto sliderWidth = juce::jlimit (90, 220, (getWidth() - (margin * 2) - (spacing * 2)) / 3);
    auto groupWidth = (sliderWidth * 3) + (spacing * 2);
    auto startX = (getWidth() - groupWidth) / 2;
    auto bottomY = getHeight() - sliderHeight - margin;

    glowSlider.setBounds (startX, bottomY, sliderWidth, sliderHeight);
    gainSlider.setBounds (startX + sliderWidth + spacing, bottomY, sliderWidth, sliderHeight);
    intensitySlider.setBounds (startX + (sliderWidth + spacing) * 2, bottomY, sliderWidth, sliderHeight);

    MyOscilloscope.setBounds (margin, margin, getWidth() - (margin * 2), bottomY - (margin * 2));
}
