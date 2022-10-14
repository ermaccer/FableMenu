#pragma once

class eMouse {
public:
	int x;
	int y;

	float deltaX;
	float deltaY;
	bool gotDelta;

	eMouse();

	void Clear();

	static void UpdateMouse();

	static eMouse mouse;


	static int  GetDeltaX();
	static int  GetDeltaY();

	static void LockMouse();
};

