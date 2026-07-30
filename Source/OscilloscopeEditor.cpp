#include "OscilloscopeEditor.h"

#include <algorithm>

OscilloscopeEditor::OscilloscopeEditor(VisualSauceAudioProcessor& processor)
    : audioProcessor(processor)
{
    startTimerHz(60);
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
    const auto availableSamples = audioProcessor.abstractFifo.getNumReady();

    if (availableSamples <= 0)
    {
        samplesInScope = 0;
        repaint();
        return;
    }

    samplesInScope = std::min(availableSamples, (int) localData.size());
    std::fill(localData.begin(), localData.end(), 0.0f);
    readFromFifo(localData.data(), samplesInScope);

    repaint();
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

    for (int i = 0; i < samplesInScope; i++)
    {
        float x = juce::jmap ((float) i,
                      0.0f, (float) (samplesInScope - 1), // Plage de départ
                      0.0f, (float) width);                // Plage d'arrivée

        float y = juce::jmap((float) localData[i], -1.0f, 1.0f, (float) height, 0.0f);

        if (i == 0)
            oscilloscopePath.startNewSubPath (x, y);
        else
            oscilloscopePath.lineTo (x, y);
    }
    g.setColour (juce::Colours::limegreen);
    g.strokePath (oscilloscopePath, juce::PathStrokeType (2.0f));

}