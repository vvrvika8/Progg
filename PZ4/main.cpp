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
    
    cout << "\n5. ExtendedIntArray - дополнительные методы:" << endl;
    ExtendedIntArray extArr(5);
    extArr.setValue(0, 10);
    extArr.setValue(1, 20);
    extArr.setValue(2, 30);
    extArr.setValue(3, 40);
    extArr.setValue(4, 50);
    
    cout << "extArr: ";
    extArr.print();
    cout << "Среднее значение: " << extArr.getAverage() << endl;
    cout << "Медианное значение: " << extArr.getMedian() << endl;
    cout << "Наименьший элемент: " << extArr.getMin() << endl;
    cout << "Наибольший элемент: " << extArr.getMax() << endl;
    
    cout << "\n6. ExtendedIntArray с нечетным количеством элементов:" << endl;
    ExtendedIntArray extArr2(4);
    extArr2.setValue(0, 15);
    extArr2.setValue(1, 5);
    extArr2.setValue(2, 25);
    extArr2.setValue(3, 10);
    
    cout << "extArr2: ";
    extArr2.print();
    cout << "Среднее значение: " << extArr2.getAverage() << endl;
    cout << "Медианное значение: " << extArr2.getMedian() << endl;
    cout << "Наименьший элемент: " << extArr2.getMin() << endl;
    cout << "Наибольший элемент: " << extArr2.getMax() << endl;
    
    return 0;
}