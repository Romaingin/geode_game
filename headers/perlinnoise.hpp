#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include <vector>

class PerlinNoise {
	std::vector<int> p;
public:
	PerlinNoise();

	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);

	// Generate the noise
	double Noise(double x, double y, double z);
	double OctavePerlin(double x, double y, double z, int octaves, double persistence);
	double OctaveSmoothPerlin(double x, double y, double z, int octaves, double persistence);
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};

#endif
