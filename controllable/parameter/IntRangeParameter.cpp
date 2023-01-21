/*
  ==============================================================================

	IntRangeParameter.cpp
	Created: 21 Jan 2023 
	Author:  dkuper

  ==============================================================================
*/

IntRangeParameter::IntRangeParameter(const String& niceName, const String& description, bool _enabled) :
	Parameter(INTRANGE, niceName, description, 0, 0, 1, _enabled),
	x(0), y(0),
	defaultUI(FloatParameter::NONE),
	showExtendedEditor(false),
	extendedEditorInvertX(false),
	extendedEditorInvertY(false),
	extendedEditorStretchMode(false),
	canShowExtendedEditor(true)
{
	canHaveRange = true;

	value = var();
	value.append(0.f);
	value.append(0.f);

	defaultValue = var();
	defaultValue.append(0.f);
	defaultValue.append(0.f);

	minimumValue = var();
	minimumValue.append((int)INT32_MIN);
	minimumValue.append((int)INT32_MIN);

	maximumValue = var();
	maximumValue.append((int)INT32_MAX);
	maximumValue.append((int)INT32_MAX);

	//hideInEditor = true;
	argumentsDescription = "int, int";
}


void IntRangeParameter::setPoint(Point<int> point)
{
	setPoint(point.x, point.y);
}

void IntRangeParameter::setPoint(int _x, int _y)
{
	var d;
	d.append(_x);
	d.append(_y);
	setValue(d);
}

UndoableAction* IntRangeParameter::setUndoablePoint(Point<int> oldPoint, Point<int> newPoint, bool onlyReturnAction)
{
	return setUndoablePoint(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y, onlyReturnAction);
}

UndoableAction* IntRangeParameter::setUndoablePoint(int oldX, int oldY, int newX, int newY, bool onlyReturnAction)
{
	var od;
	od.append(oldX);
	od.append(oldY);
	var d;
	d.append(newX);
	d.append(newY);

	if (checkValueIsTheSame(od, d) && !alwaysNotify) return nullptr;

	return setUndoableValue(od, d, onlyReturnAction);
}

void IntRangeParameter::setValueInternal(var& _value)
{
	if (_value.size() < 2)
	{
		jassertfalse;
		return;
	}

	_value[0] = (int)_value[0];
	_value[1] = (int)_value[1];

	Parameter::setValueInternal(_value);

	x = _value[0];
	y = _value[1];
}

void IntRangeParameter::setBounds(int _minX, int _minY, int _maxX, int _maxY)
{
	var minRange;
	var maxRange;
	minRange.append(_minX);
	minRange.append(_minY);
	maxRange.append(_maxX);
	maxRange.append(_maxY);
	setRange(minRange, maxRange);
}

bool IntRangeParameter::setAttributeInternal(String name, var val)
{
	if (name == "ui")
	{
		if (val == "time") defaultUI = FloatParameter::TIME;
		else if (val == "slider") defaultUI = FloatParameter::SLIDER;
		else if (val == "stepper") defaultUI = FloatParameter::STEPPER;
		else if (val == "label") defaultUI = FloatParameter::LABEL;
	}
	else if (name == "canvasInvertX") extendedEditorInvertX = (bool)val;
	else if (name == "canvasInvertY") extendedEditorInvertY = (bool)val;
	else if (name == "canvasStretchMode") extendedEditorStretchMode = (bool)val;
	else
	{
		return Parameter::setAttributeInternal(name, val);
	}

	return true;
}

StringArray IntRangeParameter::getValidAttributes() const
{
	StringArray att = Parameter::getValidAttributes();
	att.addArray({ "ui", "canvasInvertX","canvasInvertY","canvasStretchMode" });
	return att;
}

StringArray IntRangeParameter::getValuesNames()
{
	return StringArray("X", "Y");
}

Point<int> IntRangeParameter::getPoint() {
	return Point<int>(x, y);
}

var IntRangeParameter::getLerpValueTo(var targetValue, float weight)
{
	if (!targetValue.isArray()) return value;
	var result;
	result.append((int)jmap(weight, (float)x, (float)targetValue[0]));
	result.append((int)jmap(weight, (float)y, (float)targetValue[1]));
	return result;
}

void IntRangeParameter::setWeightedValue(Array<var> values, Array<float> weights)
{
	jassert(values.size() == weights.size());

	float tValues[2];
	tValues[0] = tValues[1] = 0;

	for (int i = 0; i < values.size(); ++i)
	{
		jassert(values[i].size() == 2);
		for (int j = 0; j < 2; j++)
		{
			tValues[j] += (float)values[i][j] * weights[i];
		}
	}

	setPoint((int)tValues[0], (int)tValues[1]);
}

void IntRangeParameter::setShowExtendedEditor(bool val)
{
	if (val == showExtendedEditor) return;
	showExtendedEditor = val;
	queuedNotifier.addMessage(new ParameterEvent(ParameterEvent::UI_PARAMS_CHANGED, this));
}

bool IntRangeParameter::checkValueIsTheSame(var newValue, var oldValue)
{
	if (!(newValue.isArray() && oldValue.isArray())) return false;
	if (newValue.size() == 0 || oldValue.size() == 0) return false;

	bool result = newValue[0] == oldValue[0] && newValue[1] == oldValue[1];

	return result;
}

ControllableUI* IntRangeParameter::createDefaultUI(Array<Controllable*> controllables)
{
	Array<IntRangeParameter*> parameters = getArrayAs<Controllable, IntRangeParameter>(controllables);
	if (parameters.size() == 0) parameters.add(this);
	return new IntRangeUI(parameters);
}

var IntRangeParameter::getJSONDataInternal()
{
	var data = Parameter::getJSONDataInternal();
	if (showExtendedEditor)
	{
		data.getDynamicObject()->setProperty("extendedEditor", showExtendedEditor);
		if (extendedEditorInvertX) data.getDynamicObject()->setProperty("extendedEditorInvertX", extendedEditorInvertX);
		if (extendedEditorInvertY) data.getDynamicObject()->setProperty("extendedEditorInvertY", extendedEditorInvertY);
		if (extendedEditorStretchMode) data.getDynamicObject()->setProperty("extendedEditorStretchMode", extendedEditorStretchMode);
	}
	return data;
}

void IntRangeParameter::loadJSONDataInternal(var data)
{
	Parameter::loadJSONDataInternal(data);
	showExtendedEditor = data.getProperty("extendedEditor", showExtendedEditor);
	extendedEditorInvertX = data.getProperty("extendedEditorInvertX", extendedEditorInvertX);
	extendedEditorInvertY = data.getProperty("extendedEditorInvertY", extendedEditorInvertY);
	extendedEditorStretchMode = data.getProperty("extendedEditorStretchMode", extendedEditorStretchMode);
}

var IntRangeParameter::getCroppedValue(var originalValue)
{
	jassert(originalValue.isArray() && minimumValue.isArray() && maximumValue.isArray());
	if (!originalValue.isArray() || originalValue.size() < 2)
	{
		var val;
		val.append((int)originalValue);
		val.append(0);
		return val;
	}

	if (minimumValue.size() < 2 || maximumValue.size() < 2) return originalValue;

	var val;
	for (int i = 0; i < 2; ++i) val.append(jlimit(minimumValue[i], maximumValue[i], originalValue[i]));
	return val;
}
