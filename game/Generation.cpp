#include "Header.h"
#include "Generation.h"

float Generation::bilinearInterpolation(float x1, float y1, float x2, float y2, float x, float y, float b11, float b12, float b21, float b22)
{
	float b1 = (b11 * (x2 - x) + b21 * (x - x1)) / (x2 - x1);
	float b2 = (b12 * (x2 - x) + b22 * (x - x1)) / (x2 - x1);
	float b = ((y2 - y) * b1 + (y - y1) * b2) / (y2 - y1);
	return b;
}

float Generation::bicubicInterpolation()
{
	return 0.0f;
}

int** Generation::map(int x, int y, int maxz, int octave)
{
	int** res = new int* [x];
	for (int i = 0; i < x; i++) {
		res[i] = new int[y];
	}
	for (int i = 0; i < x; i += octave) {
		for (int j = 0; j < y; j += octave){
			res[i][j] = rand() % maxz;
		}
	}
	for (int i = 0; i < x-1; i++) {
		if (true) {
			for (int j = 0; j < y-1; j++) {
				if (j % octave != 0 || i % octave != 0) {
					int x1 = i-i % octave;
					int y1 = j-j % octave;
					int x2 = x1 + octave;
					int y2 = y1 + octave;
					res[i][j] = round(bilinearInterpolation(x1, y1, x2, y2, i, j, res[x1][y1], res[x1][y2], res[x2][y1], res[x2][y2]));
				}
			}
		}
	}
	return res;
}
