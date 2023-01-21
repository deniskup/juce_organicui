/*
  ==============================================================================

    IntRangeUI.h
    Created: 21 Jan 2023
    Author:  dkuper

  ==============================================================================
*/

#pragma once

class IntRangeUI : public ParameterUI
{

public:
	IntRangeUI(Array<IntRangeParameter*> parameters);
	virtual ~IntRangeUI();

	enum Direction { HORIZONTAL, VERTICAL };
	
	Array<IntRangeParameter*> p2ds;
	IntRangeParameter * p2d;

	IntParameter xParam;
	IntParameter yParam;

	std::unique_ptr<ParameterUI> xSlider;
	std::unique_ptr<ParameterUI> ySlider;

	std::unique_ptr<P2DUI> canvasUI;
	juce::Rectangle<float> canvasSwitchRect;
	bool canShowExtendedEditor;

	var mouseDownValue;

	bool isUpdatingFromParam;

	void mouseDownInternal(const MouseEvent &) override;
	void mouseUpInternal(const MouseEvent &) override;

	void paint(Graphics& g) override;
    void resized() override;
	void showEditWindowInternal() override;
	void showEditRangeWindowInternal() override;

	void updateUseExtendedEditor();

	virtual void rangeChanged(Parameter * p) override;

protected:
	void updateUIParamsInternal() override;
	virtual void newMessage(const Parameter::ParameterEvent & e) override;

	//void valueChanged(const var &) override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntRangeUI)
};