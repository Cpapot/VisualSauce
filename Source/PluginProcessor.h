#pragma once

#include <array>
#include <atomic>

#include <juce_audio_processors/juce_audio_processors.h>

class VisualSauceAudioProcessor final : public juce::AudioProcessor
{
    public:
        VisualSauceAudioProcessor();
        ~VisualSauceAudioProcessor() override = default;

        void prepareToPlay(double sampleRate, int samplesPerBlock) override;
        void releaseResources() override;
        bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
        void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

        juce::AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override;

        const juce::String getName() const override;
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        bool isMidiEffect() const override;
        double getTailLengthSeconds() const override;

        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram(int index) override;
        const juce::String getProgramName(int index) override;
        void changeProgramName(int index, const juce::String& newName) override;

        void getStateInformation(juce::MemoryBlock& destData) override;
        void setStateInformation(const void* data, int sizeInBytes) override;

        void pushBuffer(const juce::AudioBuffer<float>& buffer);
        static constexpr int        fifoSize = 8192;           //prealocated size
        std::array<float, fifoSize> audioFifo {};       //preallocated audio buffer to draw the oscilloscope
        juce::AbstractFifo          abstractFifo { fifoSize };   //abstract fifo to manage the audio buffer

        void setEditorOpen(bool isOpen) { editorOpen.store(isOpen, std::memory_order_release); }
        bool isEditorOpen() const { return editorOpen.load(std::memory_order_acquire); }

        void    setEditorSize(int newWidth, int newHeight) { editorWidth = newWidth; editorHeight = newHeight; }
        int     getEditorWidth() const { return editorWidth; }
        int     getEditorHeight() const { return editorHeight; }
    private:
        std::atomic<bool> editorOpen { false };
        int editorWidth = 800;
        int editorHeight = 450;
};
