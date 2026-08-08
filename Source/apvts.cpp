#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout 
	VisualSauceAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 2.0f, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("glow", "Glow", 0.0f, 1.0f, 0.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("intensity", "Intensity", 0.0f, 1.0f, 0.5f));

    return { params.begin(), params.end() };
}

void		VisualSauceAudioProcessor::updateParameters()
{
    glow = *apvts.getRawParameterValue("glow");
    gain = *apvts.getRawParameterValue("gain");
    intensity = *apvts.getRawParameterValue("intensity");
}
