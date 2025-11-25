#include <iostream>
#include <algorithm>
#include <stdexcept>

class DynamicArray {
protected:
    int* data;
    size_t size;

public:
    DynamicArray(size_t arraySize = 0) : size(arraySize) {
        data = new int[size]();
    }

    DynamicArray(const DynamicArray& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    virtual ~DynamicArray() {
        delete[] data;
    }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    void setValue(size_t index, int value) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Value must be between -100 and 100");
        }
        data[index] = value;
    }

    int getValue(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Value must be between -100 and 100");
        }

        int* newData = new int[size + 1];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        newData[size] = value;
        delete[] data;
        data = newData;
        size++;
    }

    DynamicArray add(const DynamicArray& other) const {
        size_t maxSize = std::max(size, other.size);
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 + val2;
        }
        return result;
    }

    DynamicArray subtract(const DynamicArray& other) const {
        size_t maxSize = std::max(size, other.size);
        DynamicArray result(maxSize);

        for (size_t i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 - val2;
        }
        return result;
    }

    size_t getSize() const { return size; }
    const int* getData() const { return data; }
};

class ExtendedDynamicArray : public DynamicArray {
public:
    ExtendedDynamicArray(size_t arraySize = 0) : DynamicArray(arraySize) {}
    ExtendedDynamicArray(const DynamicArray& other) : DynamicArray(other) {}

    double calculateAverage() const {
        if (size == 0) return 0.0;
        double sum = 0;
        for (size_t i = 0; i < size; i++) {
            sum += data[i];
        }
        return sum / size;
    }

    double calculateMedian() {
        if (size == 0) return 0.0;
        
        int* sortedData = new int[size];
        for (size_t i = 0; i < size; i++) {
            sortedData[i] = data[i];
        }
        
        std::sort(sortedData, sortedData + size);
        
        double median;
        if (size % 2 == 0) {
            median = (sortedData[size/2 - 1] + sortedData[size/2]) / 2.0;
        } else {
            median = sortedData[size/2];
        }
        
        delete[] sortedData;
        return median;
    }

    int findMin() const {
        if (size == 0) throw std::runtime_error("Array is empty");
        int minVal = data[0];
        for (size_t i = 1; i < size; i++) {
            if (data[i] < minVal) minVal = data[i];
        }
        return minVal;
    }

    int findMax() const {
        if (size == 0) throw std::runtime_error("Array is empty");
        int maxVal = data[0];
        for (size_t i = 1; i < size; i++) {
            if (data[i] > maxVal) maxVal = data[i];
        }
        return maxVal;
    }
};

int main() {
    try {
        std::cout << "=== Testing DynamicArray ===" << std::endl;
        DynamicArray arr1(3);
        arr1.setValue(0, 10);
        arr1.setValue(1, 20);
        arr1.setValue(2, 30);
        
        std::cout << "Array 1: ";
        arr1.print();
        
        arr1.pushBack(40);
        std::cout << "After pushBack(40): ";
        arr1.print();
        
        DynamicArray arr2(2);
        arr2.setValue(0, 5);
        arr2.setValue(1, 15);
        
        std::cout << "Array 2: ";
        arr2.print();
        
        DynamicArray sum = arr1.add(arr2);
        std::cout << "Array1 + Array2: ";
        sum.print();
        
        std::cout << "\n=== Testing ExtendedDynamicArray ===" << std::endl;
        ExtendedDynamicArray extArr;
        extArr.pushBack(10);
        extArr.pushBack(20);
        extArr.pushBack(30);
        extArr.pushBack(40);
        extArr.pushBack(50);
        
        std::cout << "Extended Array: ";
        extArr.print();
        
        std::cout << "Average: " << extArr.calculateAverage() << std::endl;
        std::cout << "Median: " << extArr.calculateMedian() << std::endl;
        std::cout << "Min: " << extArr.findMin() << std::endl;
        std::cout << "Max: " << extArr.findMax() << std::endl;
        
        ExtendedDynamicArray extArr2;
        extArr2.pushBack(15);
        extArr2.pushBack(5);
        extArr2.pushBack(25);
        
        std::cout << "\nArray 2: ";
        extArr2.print();
        std::cout << "Median: " << extArr2.calculateMedian() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}