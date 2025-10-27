#pragma once

class CAProgressDisplay;

class NProgressDisplay
{
public:
	static CAProgressDisplay* PProgressDisplay;
	static void InitialiseProgressDisplay(CAProgressDisplay* progressDisplay);
};