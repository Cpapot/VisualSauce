#include "PluginProcessor.h"
#include "PluginEditor.h"

VisualSauceAudioProcessor::VisualSauceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
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
    if (!layouts.getMainInputChannelSet().isDisabled()
        && layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
}

void VisualSauceAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    if (buffer.getNumChannels() == 0)
        return;

    updateParameters();

    const auto totalNumInputChannels = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    if (!isEditorOpen())
        return;

    juce::AudioBuffer<float> visualBuffer;
    visualBuffer.makeCopyOf (buffer);
    visualBuffer.applyGain(gain);
    pushBuffer(visualBuffer);
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
    return "VisualSauce";
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

void VisualSauceAudioProcessor::pushBuffer(const juce::AudioBuffer<float>& buffer)
{
    if (buffer.getNumChannels() == 0 || buffer.getNumSamples() == 0)
        return;

    const float* channelData = buffer.getReadPointer(0);
    int numSamples = buffer.getNumSamples();

    int start1, size1, start2, size2;
    abstractFifo.prepareToWrite(numSamples, start1, size1, start2, size2);

    if (size1 > 0)
    {
        std::copy(channelData, 
                  channelData + size1, 
                  audioFifo.begin() + start1);
    }

    if (size2 > 0)
    {
        std::copy(channelData + size1, 
                  channelData + size1 + size2, 
                  audioFifo.begin() + start2);
    }

    abstractFifo.finishedWrite(size1 + size2);
    //copy audio buff inside the class to draw it
}