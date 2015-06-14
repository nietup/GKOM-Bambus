#pragma once
#include <vector>

class Perlin {
    std::vector<int> p;
public:
    Perlin();
    Perlin(unsigned int seed);
    double noise(double x, double y, double z);
private:
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
};
