/*
  ==============================================================================

    DashboardUI.h
    Created: 19 Apr 2017 11:06:43pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

class DashboardGroupItemUI :
	public DashboardItemUI
{
public:
	DashboardGroupItemUI(DashboardGroupItem * group);
	~DashboardGroupItemUI();

	DashboardGroupItem* group;
};