#include "OscilloscopeEditor.h"

#include <algorithm>
#include <numeric>

OscilloscopeEditor::OscilloscopeEditor(VisualSauceAudioProcessor& processor)
    : audioProcessor(processor)
{
    startTimerHz(60);
    setOpaque (true);
}

OscilloscopeEditor::~OscilloscopeEditor()
{}

void OscilloscopeEditor::readFromFifo(float* destinationBuffer, int numSamplesToRead)
{
    int startIndex1, blockSize1, startIndex2, blockSize2;

    audioProcessor.abstractFifo.prepareToRead(numSamplesToRead, startIndex1, blockSize1, startIndex2, blockSize2);

    if (blockSize1 > 0)
    {
        std::copy(audioProcessor.audioFifo.begin() + startIndex1, 
                  audioProcessor.audioFifo.begin() + startIndex1 + blockSize1, 
                  destinationBuffer);
    }

    if (blockSize2 > 0)
    {
        std::copy(audioProcessor.audioFifo.begin() + startIndex2, 
                  audioProcessor.audioFifo.begin() + startIndex2 + blockSize2, 
                  destinationBuffer + blockSize1); 
    }

    audioProcessor.abstractFifo.finishedRead(blockSize1 + blockSize2);
}

void OscilloscopeEditor::timerCallback()
{
    int availableSamples = audioProcessor.abstractFifo.getNumReady();
    if (availableSamples >= tempBuffer.size())
    {
        std::fill(tempBuffer.begin(), tempBuffer.end(), 0.0f);
        readFromFifo(tempBuffer.data(), (int) tempBuffer.size());

        int triggerIndex = findTriggerIndex(scopeSize * step);

        int requiredSamples = scopeSize * step;
        if (triggerIndex + requiredSamples < tempBuffer.size())
        {
            for (int i = 0; i < scopeSize; ++i)
            {
                localData[i] = tempBuffer[triggerIndex + (i * step)];
            }
        }
        samplesInScope = scopeSize;

        repaint();
    }
}

void OscilloscopeEditor::paint(juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

    if (samplesInScope <= 0)
    {
        g.setColour(juce::Colours::darkgrey);
        g.drawLine(0.0f, getHeight() / 2.0f, (float) getWidth(), getHeight() / 2.0f, 1.0f);
        return;
    }

    juce::Path oscilloscopePath;

    auto width = getWidth();
    auto height = getHeight();

    for (int i = 0; i < std::min(samplesInScope, scopeSize); i++)
    {
        float x = juce::jmap ((float) i, 0.0f, (float) (samplesInScope - 1), 0.0f, (float) width);

        float y = juce::jmap((float) localData[i], -1.0f, 1.0f, (float) height, 0.0f);

        if (i == 0)
            oscilloscopePath.startNewSubPath (x, y);
        else
            oscilloscopePath.lineTo (x, y);
    }
    g.setColour (juce::Colours::limegreen);
    g.strokePath (oscilloscopePath, juce::PathStrokeType (2.0f));

}

int OscilloscopeEditor::findTriggerIndex (int numSamplesToDraw)
{
    int searchLimit = (int) tempBuffer.size() - numSamplesToDraw;
    if (searchLimit <= 0) return 0;

    float sum = std::accumulate (tempBuffer.begin(), 
                             tempBuffer.begin() + searchLimit, 
                             0.0f);
    float average = sum / (float) searchLimit;

    for (int i = 1; i < searchLimit; ++i)
    {
        if (tempBuffer[i - 1] < average && tempBuffer[i] >= average)
        {
            return i;
        }
    }
    return 0;
}