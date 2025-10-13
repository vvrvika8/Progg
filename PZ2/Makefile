#include <iostream>
#include "IntArray.h"

using namespace std;

int main() {
    cout << "=== Демонстрация IntArray ===" << endl;
    
    cout << "\n1. Базовые операции:" << endl;
    IntArray arr1(3);
    arr1.setValue(0, 10);
    arr1.setValue(1, -50);
    arr1.setValue(2, 100);
    cout << "arr1: ";
    arr1.print();
    
    cout << "\n2. Конструктор копирования:" << endl;
    IntArray arr2 = arr1;
    arr2.setValue(0, 99);
    cout << "arr1: ";
    arr1.print();
    cout << "arr2: ";
    arr2.print();
    
    cout << "\n3. Добавление в конец:" << endl;
    arr1.pushBack(42);
    arr1.pushBack(-88);
    cout << "После pushBack: ";
    arr1.print();
    
    cout << "\n4. Сложение и вычитание:" << endl;
    IntArray arrA(3);
    arrA.setValue(0, 10);
    arrA.setValue(1, 20);
    arrA.setValue(2, 30);
    
    IntArray arrB(2);
    arrB.setValue(0, 5);
    arrB.setValue(1, 15);
    
    cout << "A: ";
    arrA.print();
    cout << "B: ";
    arrB.print();
    
    IntArray sum = arrA.add(arrB);
    cout << "A + B: ";
    sum.print();
    
    IntArray diff = arrA.subtract(arrB);
    cout << "A - B: ";
    diff.print();
    
    return 0;
}