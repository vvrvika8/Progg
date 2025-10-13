#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "pgm_utils.h"

using namespace std;
namespace fs = filesystem;

struct TestResult {
    string imageName;
    double noiseLevel;
    string filterType;
    int filterSize;
    double similarity;
};

vector<string> findPGMFiles(const string& directory) {
    vector<string> files;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".pgm") {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

void runTests(const vector<string>& imageFiles, const string& outputCSV) {
    ofstream csv(outputCSV);
    csv << "Image,NoiseLevel,FilterType,FilterSize,Similarity\n";
    
    vector<double> noiseLevels = {0.05, 0.1, 0.2};
    vector<pair<string, int>> filters = {
        {"Median", 3}, {"Median", 5}, {"Median", 7},
        {"Mean", 3}, {"Mean", 5}, {"Mean", 7},
        {"Gaussian", 3}, {"Gaussian", 5}, {"Gaussian", 7}
    };
    
    for (const auto& imageFile : imageFiles) {
        PGMImage original;
        if (!original.load(imageFile)) {
            cerr << "Error loading: " << imageFile << endl;
            continue;
        }
        
        string imageName = fs::path(imageFile).stem().string();
        cout << "Processing: " << imageName << endl;
        
        for (double noiseLevel : noiseLevels) {
            PGMImage noisy = original;
            noisy.addNoise(noiseLevel);
            
            for (const auto& filter : filters) {
                PGMImage filtered = noisy;
                
                if (filter.first == "Median") {
                    filtered.medianFilter(filter.second);
                } else if (filter.first == "Mean") {
                    filtered.meanFilter(filter.second);
                } else if (filter.first == "Gaussian") {
                    filtered.gaussianFilter(filter.second);
                }
                
                double similarity = original.compare(filtered);
                
                csv << imageName << "," << noiseLevel << "," 
                    << filter.first << "," << filter.second << "," 
                    << similarity << "\n";
                
                cout << "  Noise: " << noiseLevel << ", Filter: " << filter.first 
                     << " " << filter.second << ", Similarity: " << similarity << "%" << endl;
            }
        }
    }
    
    csv.close();
}

int main() {
    string imageDir = "images";
    string outputCSV = "test_results.csv";
    
    if (!fs::exists(imageDir)) {
        fs::create_directory(imageDir);
        cout << "Created 'images' directory. Please add PGM files there." << endl;
        return 1;
    }
    
    vector<string> imageFiles = findPGMFiles(imageDir);
    
    if (imageFiles.empty()) {
        cout << "No PGM files found in 'images' directory." << endl;
        return 1;
    }
    
    cout << "Found " << imageFiles.size() << " PGM files." << endl;
    cout << "Starting noise removal tests..." << endl;
    
    runTests(imageFiles, outputCSV);
    
    cout << "Tests completed. Results saved to " << outputCSV << endl;
    
    return 0;
}