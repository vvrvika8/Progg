#ifndef PGM_UTILS_H
#define PGM_UTILS_H

#include <vector>
#include <string>

class PGMImage {
private:
    int width, height, maxVal;
    std::vector<std::vector<int>> pixels;

public:
    bool load(const std::string& filename);
    bool save(const std::string& filename) const;
    void addNoise(double noiseLevel);
    void medianFilter(int kernelSize);
    void meanFilter(int kernelSize);
    void gaussianFilter(int kernelSize, double sigma = 1.0);
    double compare(const PGMImage& other) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif