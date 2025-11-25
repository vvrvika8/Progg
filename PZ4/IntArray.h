#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray {
private:
    int* data;
    int size;

public:
    IntArray(int arraySize);
    IntArray(const IntArray& other);
    ~IntArray();
    
    void print() const;
    bool setValue(int index, int value);
    bool getValue(int index, int& value) const;
    void pushBack(int value);
    IntArray add(const IntArray& other) const;
    IntArray subtract(const IntArray& other) const;
    int getSize() const { return size; }

private:
    bool isValidValue(int value) const;
    bool isValidIndex(int index) const;
};

class ExtendedIntArray : public IntArray {
public:
    ExtendedIntArray(int arraySize) : IntArray(arraySize) {}
    ExtendedIntArray(const IntArray& other) : IntArray(other) {}
    
    double getAverage() const;
    double getMedian() const;
    int getMin() const;
    int getMax() const;
};

#endif