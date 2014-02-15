/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINEDITOR_H_A5624E04__
#define __PLUGINEDITOR_H_A5624E04__

#include "JuceHeader.h"
#include "JucePluginCharacteristics.h"
#include "PluginProcessor.h"
#include "Knob.h"
#include "BackgroundImage.h"
#include "MIDIButton.h"


//==============================================================================
/**
*/
class ThePilgrimAudioProcessorEditor  : public AudioProcessorEditor,
										public Slider::Listener,
										public Button::Listener,
										public Timer

{
public:
    ThePilgrimAudioProcessorEditor (ThePilgrimAudioProcessor* ownerFilter);
    ~ThePilgrimAudioProcessorEditor();

    //==============================================================================
    // This is just a standard Juce paint method...
    void paint (Graphics& g);
	void resized ();
	void sliderValueChanged (Slider *slider);
	void timerCallback();
	void buttonClicked(Button *buttonThatWasClicked);
	void actionListenerCallback (const String &message);
	
	ThePilgrimAudioProcessor* getProcessor() const
    {
        return static_cast <ThePilgrimAudioProcessor*> (getAudioProcessor());
    }
	
private:
	Knob filterSlider;
	Knob mixSlider;
	Image bgImage;
	//Label contNo;
	//Label contVal;
	MIDIButton learnButton;
	

};


#endif  // __PLUGINEDITOR_H_A5624E04__