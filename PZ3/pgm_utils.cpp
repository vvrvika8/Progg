#include "pgm_utils.h"
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

bool PGMImage::load(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return false;

    string magic;
    file >> magic;
    if (magic != "P2" && magic != "P5") return false;

    file >> width >> height >> maxVal;
    
    pixels.resize(height, vector<int>(width));
    
    if (magic == "P2") {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file >> pixels[i][j];
            }
        }
    } else {
        file.get();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                pixels[i][j] = file.get();
            }
        }
    }
    
    return true;
}

bool PGMImage::save(const string& filename) const {
    ofstream file(filename, ios::binary);
    if (!file) return false;

    file << "P2\n" << width << " " << height << "\n" << maxVal << "\n";
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file << pixels[i][j] << " ";
        }
        file << "\n";
    }
    
    return true;
}

void PGMImage::addNoise(double noiseLevel) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    uniform_int_distribution<> noiseVal(0, maxVal);
    
    int noisePixels = static_cast<int>(width * height * noiseLevel);
    
    for (int i = 0; i < noisePixels; i++) {
        int x = rand() % width;
        int y = rand() % height;
        pixels[y][x] = noiseVal(gen);
    }
}

void PGMImage::medianFilter(int kernelSize) {
    vector<vector<int>> result = pixels;
    int offset = kernelSize / 2;
    
    for (int y = offset; y < height - offset; y++) {
        for (int x = offset; x < width - offset; x++) {
            vector<int> window;
            for (int ky = -offset; ky <= offset; ky++) {
                for (int kx = -offset; kx <= offset; kx++) {
                    window.push_back(pixels[y + ky][x + kx]);
                }
            }
            sort(window.begin(), window.end());
            result[y][x] = window[window.size() / 2];
        }
    }
    pixels = result;
}

void PGMImage::meanFilter(int kernelSize) {
    vector<vector<int>> result = pixels;
    int offset = kernelSize / 2;
    
    for (int y = offset; y < height - offset; y++) {
        for (int x = offset; x < width - offset; x++) {
            int sum = 0;
            for (int ky = -offset; ky <= offset; ky++) {
                for (int kx = -offset; kx <= offset; kx++) {
                    sum += pixels[y + ky][x + kx];
                }
            }
            result[y][x] = sum / (kernelSize * kernelSize);
        }
    }
    pixels = result;
}

void PGMImage::gaussianFilter(int kernelSize, double sigma) {
    vector<vector<int>> result = pixels;
    int offset = kernelSize / 2;
    
    vector<vector<double>> kernel(kernelSize, vector<double>(kernelSize));
    double sum = 0.0;
    
    for (int y = -offset; y <= offset; y++) {
        for (int x = -offset; x <= offset; x++) {
            double value = exp(-(x*x + y*y) / (2 * sigma * sigma));
            kernel[y + offset][x + offset] = value;
            sum += value;
        }
    }
    
    for (int y = 0; y < kernelSize; y++) {
        for (int x = 0; x < kernelSize; x++) {
            kernel[y][x] /= sum;
        }
    }
    
    for (int y = offset; y < height - offset; y++) {
        for (int x = offset; x < width - offset; x++) {
            double conv = 0.0;
            for (int ky = -offset; ky <= offset; ky++) {
                for (int kx = -offset; kx <= offset; kx++) {
                    conv += pixels[y + ky][x + kx] * kernel[ky + offset][kx + offset];
                }
            }
            result[y][x] = static_cast<int>(conv);
        }
    }
    pixels = result;
}

double PGMImage::compare(const PGMImage& other) const {
    if (width != other.width || height != other.height) return -1.0;
    
    double mse = 0.0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double diff = pixels[y][x] - other.pixels[y][x];
            mse += diff * diff;
        }
    }
    mse /= (width * height);
    
    if (mse == 0.0) return 100.0;
    
    double psnr = 20 * log10(maxVal / sqrt(mse));
    double similarity = min(100.0, max(0.0, psnr));
    
    return similarity;
}