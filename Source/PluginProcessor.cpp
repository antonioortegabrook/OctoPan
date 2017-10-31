/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
OctoPanAudioProcessor::OctoPanAudioProcessor()	:	parameters(*this, nullptr)

	#ifndef JucePlugin_PreferredChannelConfigurations
		: AudioProcessor (BusesProperties()
		#if ! JucePlugin_IsMidiEffect
			#if ! JucePlugin_IsSynth
				  .withInput  ("Input",  AudioChannelSet::stereo(), true)
			#endif
			.withOutput ("Output", AudioChannelSet::stereo(), true)
		#endif
		  )
	#endif

{
	//--- add parameters
	parameters.createAndAddParameter("azimuth",				// parameter ID
					 "Azimuth",				// parameter name
					 String(),				// parameter label (suffix)
					 NormalisableRange<float> (-180, 180),	// parameter range
					 0,					// default value
					 nullptr,				// value to text function
					 nullptr);				// text to value function
	
	parameters.createAndAddParameter("spread",
					 "Spread",
					 String(),
					 NormalisableRange<float> (0, 100),
					 0,
					 nullptr,
					 nullptr);
	
	parameters.createAndAddParameter("shape",
					 "Shape",
					 String(),
					 NormalisableRange<float> (-10, 10),
					 0,
					 nullptr,
					 nullptr);
	
	parameters.createAndAddParameter("offset",
					 "Offset",
					 String(),
					 NormalisableRange<float> (0, 1),
					 1,
					 nullptr,
					 nullptr);
	
	parameters.state = ValueTree(Identifier("OctoPan"));
	
	/*
		Terminar de resolver cuánto de esto hacemos en el constructor,
		cuánto en prepareToPlay y cuánto en setStateInformation
	 */
	
	nspeakers = 8;
	
}

OctoPanAudioProcessor::~OctoPanAudioProcessor()
{
}

//==============================================================================
const String OctoPanAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool OctoPanAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool OctoPanAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

double OctoPanAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int OctoPanAudioProcessor::getNumPrograms()
{
	return 1;	// NB: some hosts don't cope very well if you tell them there are 0 programs,
			// so this should be at least 1, even if you're not really implementing programs.
}

int OctoPanAudioProcessor::getCurrentProgram()
{
	return 0;
}

void OctoPanAudioProcessor::setCurrentProgram (int index)
{
}

const String OctoPanAudioProcessor::getProgramName (int index)
{
	return {};
}

void OctoPanAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OctoPanAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	
	/*
		Reescribir todo esto de una manera más elegante
	 */
	
	previousAzimuth	= *parameters.getRawParameterValue("azimuth");
	previousSpread	= *parameters.getRawParameterValue("spread");
	previousshape	= *parameters.getRawParameterValue("shape");
	previousOffset	= *parameters.getRawParameterValue("offset");
	
	
	fill_spk_layout(&layout,
			nspeakers,
			*parameters.getRawParameterValue("offset") >= 0.5 ? 0.5 : 0);
	
	init_source(&source,
			*parameters.getRawParameterValue("azimuth"),
			*parameters.getRawParameterValue("spread"),
			*parameters.getRawParameterValue("shape"),
			2 * layout.spk_diff);
	
	compute_gains(gains, &source, &layout);
	
}

void OctoPanAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OctoPanAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused (layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;
	
	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif
	
	return true;
#endif
}
#endif

void OctoPanAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
//	const int totalNumInputChannels  = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();
	
	
	// Parámetros
	const double currentAzimuth	= *parameters.getRawParameterValue("azimuth");
	const double currentSpread	= *parameters.getRawParameterValue("spread");
	const double currentshape	= *parameters.getRawParameterValue("shape");
	const double currentOffset	= *parameters.getRawParameterValue("offset");
		
	
	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	for (int channel = 1; channel < totalNumOutputChannels; ++channel)
	{
		// copiamos el canal 1 a todos los demás
		buffer.copyFrom(channel, 0, buffer, 0, 0, buffer.getNumSamples());
	}
	
        
	/*
	Si algún parámetro cambió, copiamos las ganancias actuales al array de ganancias previas;
	Si el parámetro modificado es offset, actualizamos layout y copiamos offset a previousOffset;
	Si en cambio es un parámetro de fuente, actualizamos fuente y copiamos los nuevos parámetros
	 a previous.
	Por último, recalculamos ganancias y aplicamos rampa. Luego copiamos las ganancias actuales
	*/
	
	if (currentAzimuth	!= previousAzimuth	||
	    currentSpread	!= previousSpread	||
	    currentshape	!= previousshape	||
	    currentOffset	!= previousOffset)		{
		
		
		double *previousGainsPtr	= previousGains;
		double *gainsPtr		= gains;
		
		for (int i = 0; i < nspeakers; i++)
			*previousGainsPtr++ = *gainsPtr++;
		
		if (currentOffset != previousOffset) {
			
			fill_spk_layout(&layout, nspeakers, currentOffset >= 0.5 ? 0.5 : 0);
			previousOffset	= currentOffset;
		}
		else {
			init_source(&source, currentAzimuth, currentSpread, currentshape, 2 * layout.spk_diff);
			
			previousAzimuth	= currentAzimuth;
			previousSpread	= currentSpread;
			previousshape	= currentshape;
		}
		
		compute_gains(gains, &source, &layout);
		
		for (int channel = 0; channel < totalNumOutputChannels; ++channel)
			buffer.applyGainRamp(channel, 0, buffer.getNumSamples(), previousGains[channel], gains[channel]);


	} else {
		for (int channel = 0; channel < totalNumOutputChannels; ++channel)
			buffer.applyGain(channel, 0, buffer.getNumSamples(), gains[channel]);
	}

}

//==============================================================================
bool OctoPanAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OctoPanAudioProcessor::createEditor()
{
	return new OctoPanAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void OctoPanAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
	
	ScopedPointer<XmlElement> xml (parameters.state.createXml());
	copyXmlToBinary (*xml, destData);
}

void OctoPanAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
	
	ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
	if (xmlState != nullptr)
		if (xmlState->hasTagName (parameters.state.getType()))
			parameters.state = ValueTree::fromXml (*xmlState);
	
	
	
	previousAzimuth	= *parameters.getRawParameterValue("azimuth");
	previousSpread	= *parameters.getRawParameterValue("spread");
	previousshape	= *parameters.getRawParameterValue("shape");
	previousOffset	= *parameters.getRawParameterValue("offset");
	
	fill_spk_layout(&layout,
			nspeakers,
			*parameters.getRawParameterValue("offset") >= 0.5 ? 0.5 : 0);
	
	init_source(&source,
		    *parameters.getRawParameterValue("azimuth"),
		    *parameters.getRawParameterValue("spread"),
		    *parameters.getRawParameterValue("shape"),
		    2 * layout.spk_diff);
	
	compute_gains(gains, &source, &layout);
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new OctoPanAudioProcessor();
}

