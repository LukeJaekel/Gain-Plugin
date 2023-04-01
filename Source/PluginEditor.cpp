/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainPluginAudioProcessorEditor::GainPluginAudioProcessorEditor (GainPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);
    
    // Creates DAW automation parameter for plugin
    sliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (processor.treeState, GAIN_ID, gainSlider);
    
    // Sets slider to vertical orientation
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    
    // Creates a text box below slider to represent dB value
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    
    // Sets the slider range from -40dB to 0dB
    gainSlider.setRange(-40.0f, 0.0f);
    
    // Links the slider to volume
    gainSlider.addListener(this);
    
    // Makes the slider visible on the screen
    addAndMakeVisible(gainSlider);
}

GainPluginAudioProcessorEditor::~GainPluginAudioProcessorEditor()
{
}

//==============================================================================
void GainPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void GainPluginAudioProcessorEditor::resized()
{
    // Sets slider size to size of screen
    gainSlider.setBounds(getLocalBounds());
}

void GainPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    // Links the slider to the volume and matches it accordingly
    if (slider == &gainSlider)
    {
        processor.rawVolume = pow(10, gainSlider.getValue() / 20);
    }
}
