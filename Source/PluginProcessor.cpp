#include "PluginProcessor.h"
#include "PluginEditor.h"

VisualSauceAudioProcessor::VisualSauceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
#endif
{
}

void VisualSauceAudioProcessor::prepareToPlay(double, int)
{
}

void VisualSauceAudioProcessor::releaseResources()
{
}

bool VisualSauceAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#ifndef JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
}

void VisualSauceAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const auto totalNumInputChannels = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* VisualSauceAudioProcessor::createEditor()
{
    return new VisualSauceAudioProcessorEditor(*this);
}

bool VisualSauceAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String VisualSauceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VisualSauceAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool VisualSauceAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool VisualSauceAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double VisualSauceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VisualSauceAudioProcessor::getNumPrograms()
{
    return 1;
}

int VisualSauceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VisualSauceAudioProcessor::setCurrentProgram(int)
{
}

const juce::String VisualSauceAudioProcessor::getProgramName(int)
{
    return {};
}

void VisualSauceAudioProcessor::changeProgramName(int, const juce::String&)
{
}

void VisualSauceAudioProcessor::getStateInformation(juce::MemoryBlock&)
{
}

void VisualSauceAudioProcessor::setStateInformation(const void*, int)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VisualSauceAudioProcessor();
}
