/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "Common/PluginLookAndFeel.cpp"


//==============================================================================
TremoloAudioProcessorEditor::TremoloAudioProcessorEditor (TremoloAudioProcessor* ownerFilter_)
    : AudioProcessorEditor (ownerFilter_),
      ownerFilter (ownerFilter_)
{
    Desktop::getInstance().setDefaultLookAndFeel (&customLookAndFeel);
    
	// create the sliders and their labels
	for (int i = 0; i < Parameters::numParameters; i++)
	{
		sliders.add (new Slider ());
		addAndMakeVisible (sliders[i]);
		
		String labelName = ownerFilter->getParameterName (i);
		labels.add (new Label (String::empty, labelName));
		addAndMakeVisible (labels[i]);
		labels[i]->setJustificationType (Justification::left);
		labels[i]->attachToComponent (sliders[i], false);
        
		sliders[i]->addListener (this);
		ownerFilter->getParameterObject (i)->setupSlider (*sliders[i]);
		
		sliders[i]->getValueObject().referTo (ownerFilter->getParameterValueObject (i));
        sliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 60, 18);
//		sliders[i]->setColour (Slider::thumbColourId, Colours::grey);
//		sliders[i]->setColour (Slider::textBoxTextColourId, Colour (0xff78f4ff));
//		sliders[i]->setColour (Slider::textBoxBackgroundColourId, Colours::black);
//		sliders[i]->setColour (Slider::textBoxOutlineColourId, Colour (0xff0D2474));
	}
    
	sliders[Parameters::rate]->setSliderStyle (Slider::RotaryVerticalDrag);
//	sliders[Parameters::rate]->setColour (Slider::rotarySliderFillColourId, Colours::grey);
	sliders[Parameters::rate]->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 18);
	labels[Parameters::rate]->attachToComponent (sliders[Parameters::rate], false);
	labels[Parameters::rate]->setJustificationType (Justification::centred);
	sliders[Parameters::depth]->setSliderStyle (Slider::RotaryVerticalDrag);
//	sliders[Parameters::depth]->setColour (Slider::rotarySliderFillColourId, Colours::grey);
	sliders[Parameters::depth]->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 18);
	labels[Parameters::depth]->attachToComponent (sliders[Parameters::depth], false);
	labels[Parameters::depth]->setJustificationType (Justification::centred);
	
//    ownerFilter->getParameterValueObject (Parameters::depth).addListener (this);
//    ownerFilter->getParameterValueObject (Parameters::shape).addListener (this);
//    ownerFilter->getParameterValueObject (Parameters::phase).addListener (this);
    
	// create the buffer views
	addAndMakeVisible (bufferViewL = new TremoloBufferView (ownerFilter->getTremoloBuffer (0).getData(),
                                                            ownerFilter->getTremoloBuffer (0).getSize()));
	bufferViewL->setInterceptsMouseClicks (false, false);
	addAndMakeVisible (bufferViewLLabel = new Label ("lLabel", "L:"));
	bufferViewLLabel->attachToComponent (bufferViewL, true);
	bufferViewLLabel->setFont (Font (30, Font::plain));
    //	bufferView1Label->setColour(Label::textColourId, Colours::white);
	
	addAndMakeVisible (bufferViewR = new TremoloBufferView (ownerFilter->getTremoloBuffer (1).getData(),
                                                            ownerFilter->getTremoloBuffer (1).getSize()));
	bufferViewR->setInterceptsMouseClicks (false, false);
	addAndMakeVisible (bufferViewRLabel = new Label ("rLabel", "R:"));
	bufferViewRLabel->attachToComponent (bufferViewR, true);
	bufferViewRLabel->setFont (Font (30, Font::plain));
    //	bufferView2Label->setColour(Label::textColourId, Colours::white);
    
    
	if (ownerFilter->getNumInputChannels() == 1)
		setSize (360, 170);
	else
		setSize (360, 210);
    
	// if plugin is mono set up the accordingly
	if (ownerFilter->getNumInputChannels() < 2)
	{
		sliders[Parameters::phase]->setVisible (false);
		bufferViewR->setVisible (false);		
	}
    
    ownerFilter->addChangeListener (this);
}

TremoloAudioProcessorEditor::~TremoloAudioProcessorEditor()
{
    ownerFilter->removeChangeListener (this);
    
	for (int i = 0; i < Parameters::numParameters; i++)
    {
        sliders[i]->removeListener (this);
    }
    
//    ownerFilter->getParameterValueObject (Parameters::depth).removeListener (this);
//    ownerFilter->getParameterValueObject (Parameters::shape).removeListener (this);
//    ownerFilter->getParameterValueObject (Parameters::phase).removeListener (this);    
}

//==============================================================================
void TremoloAudioProcessorEditor::paint (Graphics& g)
{
	// just clear the window
    PluginLookAndFeel::drawPluginBackgroundBase (g, *this);
    
    const int verticalLineX = sliders[Parameters::shape]->getRight() + 10;
	PluginLookAndFeel::drawInsetLine (g, 0, 115, verticalLineX, 115, 2);
	PluginLookAndFeel::drawInsetLine (g, verticalLineX, 0, verticalLineX, 210, 2);

    Rectangle<int> bevel (bufferViewL->getBounds().expanded (2, 2));
    LookAndFeel_V2::drawBevel (g, bevel.getX(), bevel.getY(), bevel.getWidth(), bevel.getHeight(), 2,
                               Colour (0xFF455769).darker (0.5f), Colour (0xFF455769).brighter (0.3f),
                               false, true);
    
    if (getAudioProcessor()->getNumInputChannels() > 1)
    {
        bevel  = bufferViewR->getBounds().expanded (2, 2);
        LookAndFeel_V2::drawBevel (g, bevel.getX(), bevel.getY(), bevel.getWidth(), bevel.getHeight(), 2,
                                   Colour (0xFF455769).darker (0.5f), Colour (0xFF455769).brighter (0.3f),
                                   false, true);
    }
    
    PluginLookAndFeel::drawPluginBackgroundHighlights (g, *this);
}

void TremoloAudioProcessorEditor::resized()
{
    const int w = getWidth();
    const int h = getHeight();
    
    sliders[Parameters::rate]->setBounds (20, 35, 70, 70);
	sliders[Parameters::depth]->setBounds (105, 35, 70, 70);
	sliders[Parameters::shape]->setBounds (5, 140, w - 170, 20);
	sliders[Parameters::phase]->setBounds (5, 180, w - 170, 20);
    
	if (getAudioProcessor()->getNumInputChannels() > 1)
	{
		bufferViewL->setBounds (w - 125, 20,
								115, ((h - 15) * 0.5f) - 14);
		bufferViewR->setBounds (w - 125, ((h - 15) * 0.5f) + 15 + 2,
								115, ((h - 15) * 0.5f) - 14);
	}
	else if (getAudioProcessor()->getNumInputChannels() == 1)
    {
		bufferViewL->setBounds (w - 150, 20,
								140, (h - 15 - 15));	
    }
}

//void TremoloAudioProcessorEditor::valueChanged (Value& value)
//{
//    bufferViewL->refreshBuffer();
//    bufferViewR->refreshBuffer();
//}

void TremoloAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* /*source*/)
{
    bufferViewL->refreshBuffer();
    bufferViewR->refreshBuffer();
}

void TremoloAudioProcessorEditor::sliderValueChanged (Slider* /*slider*/)
{
}

void TremoloAudioProcessorEditor::sliderDragStarted (Slider* slider)
{
    for (int i = 0; i < Parameters::numParameters; i++)
    {
        if (slider == sliders[i])
        {
            getAudioProcessor()->beginParameterChangeGesture (i);
        }
    }
}

void TremoloAudioProcessorEditor::sliderDragEnded (Slider* slider)
{
    for (int i = 0; i < Parameters::numParameters; i++)
    {
        if (slider == sliders[i])
        {
            getAudioProcessor()->endParameterChangeGesture (i);
        }
    }    
}