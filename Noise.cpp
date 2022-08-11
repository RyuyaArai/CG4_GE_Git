#include "Noise.h"
#include <stdlib.h>
#include <time.h>

#define HASH_CODE_MAX       (256)
#define HASH_CODE_TABLE_NUM     (HASH_CODE_MAX*2)

int g_HashCode[HASH_CODE_TABLE_NUM] = {};

float Noise::Wavelet(float t, float a) {
	float C = 1 - (3 * powf(t, 2)) + (2 * (powf(fabsf(t), 3)));
	float L = a * t;
	float W = C * L;
	return W;
}

float Noise::PerlinNoise(float t, float a) {
    srand((unsigned)time(NULL));

	float Rand = (rand() % 2001 - 1000);
    Rand = Rand / 1000;
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

float Noise::Fade(float t) {
    //Ken Perlin��(�p�[�����m�C�Y��������l)���l����������Ԋ֐�.
    //6x^5 - 15x^4 + 10x^3.
    return (6 * powf(t, 5) - 15 * powf(t, 4) + 10 * powf(t, 3));
}

float Noise::Lerp(float a, float b, float t) {
    return (a + (b - a) * t);
}

unsigned int GetHash(int x, int y) {
    x %= HASH_CODE_MAX;
    y %= HASH_CODE_MAX;
    return g_HashCode[x + g_HashCode[y]];
}

float Noise::SampleGrad(unsigned int hash, float a, float b) {

    unsigned int key = hash % 0x4;
    switch (key)
    {
    case 0x0:   return a;   //a * 1.0f + b * 0.0f.
    case 0x1:   return -a;  //a * -1.0f + b * 0.0f.
    case 0x2:   return -b;  //a * 0.0f + b * -1.0f.
    case 0x3:   return b;   //a * 0.0f + b * 1.0f.
    };
    return 0.0f;
}

float Noise::SamplePNoise(float x, float y) {

    //�������Ə������ɕ�����.
    int xi = (int)floorf(x);
    int yi = (int)floorf(y);
    float xf = x - xi;
    float yf = y - yi;

    //�i�q�_����n�b�V�������o���C���̒l����Ɍ��z���擾����.
    float a00 = SampleGrad(GetHash(xi, yi), xf, yf);
    float a10 = SampleGrad(GetHash(xi + 1, yi), xf - 1.0f, yf);
    float a01 = SampleGrad(GetHash(xi, yi + 1), xf, yf - 1.0f);
    float a11 = SampleGrad(GetHash(xi + 1, yi + 1), xf - 1.0f, yf - 1.0f);

    //��Ԃ�������.
    xf = Fade(xf);
    yf = Fade(yf);

    //�ʒu�ɍ��킹�Ċi�q�_�̂ǂ̓_�����ԉe�����󂯂邩�����߂�.
    //(���z�֐����œ��ς�����Ă���̂ŁC�x�N�g���̌����ɂ���Ă͕��̒l���o��D�͈͂�-1.0f~1.0f).
    //(�Ȃ̂ŁC���̒l�ɂ��邽�߂�1.0f�𑫂���2.0f�Ŋ����Ă���).
    return (Lerp(Lerp(a00, a10, xf), Lerp(a01, a11, xf), yf) + 1.0f) / 2.0f;
}

float Noise::SampleOctavePerlinNoise(float x, float y) {

    float a = 1.0f;
    float f = 1.0f;
    float maxValue = 0.0f;
    float totalValue = 0.0f;
    float per = 0.5f;
    for (int i = 0; i < 5; ++i) {
        totalValue += a * SamplePNoise(x * f, y * f);
        maxValue += a;
        a *= per;
        f *= 2.0f;
    }
    return totalValue / maxValue;
}