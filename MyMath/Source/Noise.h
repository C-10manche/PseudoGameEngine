#pragma once
#include <cmath>
#include <array>

// Gradient array for 2D
static std::array<std::array<int, 2>, 12> grad2 = { {
    {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
    {1, 0}, {-1, 0}, {1, 0}, {-1, 0},
    {0, 1}, {0, -1}, {0, 1}, {0, -1}
} };

// Dot product helper
inline float dot(const std::array<int, 2>& g, float x, float y) {
    return g[0] * x + g[1] * y;
}

// Simplex noise function (2D)
float simplexNoise(float xin, float yin) {
    static const float F2 = 0.5f * (sqrt(3.0f) - 1.0f);
    static const float G2 = (3.0f - sqrt(3.0f)) / 6.0f;

    // Skew the input space
    float s = (xin + yin) * F2;
    int i = floor(xin + s);
    int j = floor(yin + s);

    float t = (i + j) * G2;
    float X0 = i - t;
    float Y0 = j - t;
    float x0 = xin - X0;
    float y0 = yin - Y0;

    // Determine which simplex cell we're in
    int i1 = (x0 > y0) ? 1 : 0;
    int j1 = (x0 > y0) ? 0 : 1;

    // Offsets for remaining corners
    float x1 = x0 - i1 + G2;
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0f + 2.0f * G2;
    float y2 = y0 - 1.0f + 2.0f * G2;

    // Hash function (simple permutation table)
    static const int perm[512] = { 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, /* Repeat */ 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23 };

    int ii = i & 255;
    int jj = j & 255;
    int gi0 = perm[ii + perm[jj]] % 12;
    int gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
    int gi2 = perm[ii + 1 + perm[jj + 1]] % 12;

    // Compute contribution from each corner
    float t0 = 0.5f - x0 * x0 - y0 * y0;
    float n0 = (t0 < 0) ? 0.0f : (t0 * t0) * (t0 * t0) * dot(grad2[gi0], x0, y0);

    float t1 = 0.5f - x1 * x1 - y1 * y1;
    float n1 = (t1 < 0) ? 0.0f : (t1 * t1) * (t1 * t1) * dot(grad2[gi1], x1, y1);

    float t2 = 0.5f - x2 * x2 - y2 * y2;
    float n2 = (t2 < 0) ? 0.0f : (t2 * t2) * (t2 * t2) * dot(grad2[gi2], x2, y2);

    return 70.0f * (n0 + n1 + n2);
}
