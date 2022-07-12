#include "Noise.h"
#include <stdlib.h>

float Noise::Wavelet(float t, float a) {
	float C = 1 - (3 * powf(t, 2)) + (2 * (powf(fabsf(t), 3)));
	float L = a * t;
	float W = C * L;
	return W;
}

float Noise::PerlinNoise(float t, float a) {

	float Rand = rand() % 3 - 2;
	float noise = Wavelet(t, a) + t * ((Rand + Wavelet(t, a)) - Wavelet(t, a));
	return noise;
}

float Noise::TwoDimensionalWavelet(float x, float y, float ax, float ay) {

	float Cx = 1 - (3 * powf(x, 2)) + (2 * (powf(fabsf(x), 3)));
	float Cy = 1 - (3 * powf(y, 2)) + (2 * (powf(fabsf(y), 3)));
	float L = ax * x + ay * y;
	float W = Cx * Cy * L;

	return W;
}

float Noise::ThreeDimensionalWavelet(float x, float y, float z, float ax, float ay, float az)
{
	float Cx = 1 - (3 * powf(x, 2)) + (2 * (powf(fabsf(x), 3)));
	float Cy = 1 - (3 * powf(y, 2)) + (2 * (powf(fabsf(y), 3)));
	float Cz = 1 - (3 * powf(z, 2)) + (2 * (powf(fabsf(z), 3)));
	float L = ax * x + ay * y + az * z;
	float W = Cx * Cy * Cz * L;

	return W;
}
