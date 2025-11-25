#include "IntArray.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

IntArray::IntArray(int arraySize) {
    size = arraySize > 0 ? arraySize : 1;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

IntArray::IntArray(const IntArray& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

IntArray::~IntArray() {
    delete[] data;
}

void IntArray::print() const {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool IntArray::isValidValue(int value) const {
    return (value >= -100 && value <= 100);
}

bool IntArray::isValidIndex(int index) const {
    return (index >= 0 && index < size);
}

bool IntArray::setValue(int index, int value) {
    if (!isValidIndex(index)) {
        cout << "Ошибка индекса!" << endl;
        return false;
    }
    if (!isValidValue(value)) {
        cout << "Ошибка значения!" << endl;
        return false;
    }
    data[index] = value;
    return true;
}

bool IntArray::getValue(int index, int& value) const {
    if (!isValidIndex(index)) {
        cout << "Ошибка индекса!" << endl;
        return false;
    }
    value = data[index];
    return true;
}

void IntArray::pushBack(int value) {
    if (!isValidValue(value)) {
        cout << "Ошибка значения!" << endl;
        return;
    }
    
    int newSize = size + 1;
    int* newData = new int[newSize];
    
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    
    newData[size] = value;
    delete[] data;
    data = newData;
    size = newSize;
}

IntArray IntArray::add(const IntArray& other) const {
    int maxSize = max(size, other.size);
    IntArray result(maxSize);
    
    for (int i = 0; i < maxSize; i++) {
        int sum = 0;
        if (i < size) sum += data[i];
        if (i < other.size) sum += other.data[i];
        if (sum > 100) sum = 100;
        if (sum < -100) sum = -100;
        result.data[i] = sum;
    }
    return result;
}

IntArray IntArray::subtract(const IntArray& other) const {
    int maxSize = max(size, other.size);
    IntArray result(maxSize);
    
    for (int i = 0; i < maxSize; i++) {
        int diff = 0;
        if (i < size) diff += data[i];
        if (i < other.size) diff -= other.data[i];
        if (diff > 100) diff = 100;
        if (diff < -100) diff = -100;
        result.data[i] = diff;
    }
    return result;
}

double ExtendedIntArray::getAverage() const {
    int sum = 0;
    for (int i = 0; i < getSize(); i++) {
        int value;
        getValue(i, value);
        sum += value;
    }
    return static_cast<double>(sum) / getSize();
}

double ExtendedIntArray::getMedian() const {
    vector<int> values;
    for (int i = 0; i < getSize(); i++) {
        int value;
        getValue(i, value);
        values.push_back(value);
    }
    
    sort(values.begin(), values.end());
    
    int n = values.size();
    if (n % 2 == 0) {
        return (values[n/2 - 1] + values[n/2]) / 2.0;
    } else {
        return values[n/2];
    }
}

int ExtendedIntArray::getMin() const {
    int minVal;
    getValue(0, minVal);
    
    for (int i = 1; i < getSize(); i++) {
        int value;
        getValue(i, value);
        if (value < minVal) {
            minVal = value;
        }
    }
    return minVal;
}

int ExtendedIntArray::getMax() const {
    int maxVal;
    getValue(0, maxVal);
    
    for (int i = 1; i < getSize(); i++) {
        int value;
        getValue(i, value);
        if (value > maxVal) {
            maxVal = value;
        }
    }
    return maxVal;
}