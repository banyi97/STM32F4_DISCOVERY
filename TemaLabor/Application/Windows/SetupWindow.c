/*
 * SetupWindow.c
 *
 *  Created on: 2016 okt. 28
 *      Author: Nagy Ákos
 */

#include "SetupWindow.h"
#include <string.h>

Window SetupWindow;

Window* GetSetupWindow()
{
	return &SetupWindow;
}

void InitSetupWindow()
{
	//Labels
	SetupWindow.LabelsNum = 2;
	Label* Caption = &SetupWindow.Labels[0];
	Caption->Position.x = 5;
	Caption->Position.y = 290;
	Caption->LeftAlign = 1;
	strcpy(Caption->Label, "Calibration...");

	Label* CalibLbl = &SetupWindow.Labels[1];
	CalibLbl->Position.x = 5;
	CalibLbl->Position.y = 270;
	CalibLbl->LeftAlign = 1;
	strcpy(CalibLbl->Label, "Don't move the device");

	//Unused controls
	SetupWindow.ButtonsNum = 0;
	SetupWindow.ChartActive = 0;
	SetupWindow.CompassActive = 0;
	SetupWindow.ConsoleActive = 0;
}

