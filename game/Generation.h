#ifndef GENERATION_H
#define GENERATION_H

#include "Define.h"

static class Generation {
public:
	static float bilinearInterpolation(float x1, float y1, float x2, float y2, float x, float y, float b11, float b12, float b21, float b22);
	static float bicubicInterpolation();
	static int** map(int x, int y, int maxz, int octave);
	//static int** map(int x, int y, int maxz, int octave);
};

#endif