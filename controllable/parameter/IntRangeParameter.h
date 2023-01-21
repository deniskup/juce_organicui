/*
  ==============================================================================

    IntRangeParameter.h
    Created: 21 Jan 2023
    Author:  dkuper

  ==============================================================================
*/
#pragma once

class IntRangeParameter : public Parameter
{
public:
	IntRangeParameter(const String &niceName, const String &description, bool enabled = true);
	~IntRangeParameter() {}

	int x, y;
	FloatParameter::UIType defaultUI;
	bool showExtendedEditor;
	bool extendedEditorInvertX;
	bool extendedEditorInvertY;
	bool extendedEditorStretchMode;
	bool canShowExtendedEditor;

	void setPoint(Point<int> value);
	void setPoint(int x, int y);
	UndoableAction * setUndoablePoint(Point<int> oldPoint, Point<int> newPoint, bool onlyReturnAction = false);
	UndoableAction* setUndoablePoint(int oldX, int oldY, int newX, int newY, bool onlyReturnAction = false);

	void setValueInternal(var  &_value) override;
	void setBounds(int _minX, int _minY, int _maxX, int _maxY);
	
	virtual bool setAttributeInternal(String name, var val) override;
	virtual StringArray getValidAttributes() const override;

	virtual StringArray getValuesNames() override;

	Point<int> getPoint();
	virtual var getLerpValueTo(var targetValue, float weight) override;
	virtual void setWeightedValue(Array<var> values, Array<float> weights) override;

	void setShowExtendedEditor(bool value);

	bool checkValueIsTheSame(var newValue, var oldValue) override;

	ControllableUI * createDefaultUI(Array<Controllable*> controllables = {}) override;

	static IntRangeParameter * create() { return new IntRangeParameter("New IntRange Parameter", ""); }
	virtual String getTypeString() const override { return getTypeStringStatic(); }
	static String getTypeStringStatic() { return "IntRange"; }

	virtual var getJSONDataInternal() override;
	virtual void loadJSONDataInternal(var data) override;


protected:
	virtual var getCroppedValue(var originalValue) override;
};
