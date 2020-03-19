/*
  ==============================================================================

    AssetManager.h
    Created: 23 Oct 2016 2:22:04pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

using namespace juce;

class AssetManager
{
public:
	juce_DeclareSingleton(AssetManager, true);
	AssetManager();
	virtual ~AssetManager();

	Image warningImage;

	ImageButton * getRemoveBT();
	ImageButton * getConfigBT();
	ImageButton * getTargetBT();
	ImageButton * getPowerBT();  
	ImageButton * getAddBT();
	ImageButton * getDuplicateBT();
	ImageButton * getFileBT();
	ImageButton * getEditBT();
	ImageButton * getRightArrowBT();
	ImageButton * getDownArrowImageBT();
	ImageButton * getUpBT();
	ImageButton * getDownBT();

	Image getInImage();
	Image getOutImage();
	Image getReloadImage();
	Image getPlayImage();
	Image getStopImage();
	Image getPrevCueImage();
	Image getNextCueImage();
	Image getTriggerImage();
	Image getRelativeImage();

	ImageButton * getSetupBTImage(const Image & image);
	ImageButton * getToggleBTImage(const Image &image);
};