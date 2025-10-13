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

#endif