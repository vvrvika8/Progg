#include <iostream>
#include "structs.h"
#include "func.h"

using namespace std;

int main() {
    cout << "=== Демонстрация работы с геометрическими фигурами ===" << endl;
    
    // Демонстрация работы с точками
    cout << "\n--- Работа с точками ---" << endl;
    Point p1 = readPoint();
    cout << "Создана точка: ";
    printPoint(p1);
    cout << endl;
    
    // Демонстрация работы с кругом
    cout << "\n--- Работа с кругом ---" << endl;
    Circle circle = readCircle();
    printCircle(circle);
    cout << endl;
    cout << "Длина окружности: " << circleCircumference(circle) << endl;
    cout << "Площадь круга: " << circleArea(circle) << endl;
    
    // Демонстрация работы с квадратом
    cout << "\n--- Работа с квадратом ---" << endl;
    Square square = readSquare();
    printSquare(square);
    cout << endl;
    cout << "Периметр квадрата: " << squarePerimeter(square) << endl;
    cout << "Площадь квадрата: " << squareArea(square) << endl;
    
    // Проверка принадлежности точки
    cout << "\n--- Проверка принадлежности точки ---" << endl;
    cout << "Точка ";
    printPoint(p1);
    cout << (isPointInCircle(p1, circle) ? " находится" : " не находится") << " внутри круга" << endl;
    cout << "Точка ";
    printPoint(p1);
    cout << (isPointInSquare(p1, square) ? " находится" : " не находится") << " внутри квадрата" << endl;
    
    // Проверка нахождения на контуре
    cout << "\n--- Проверка нахождения на контуре ---" << endl;
    cout << "Точка ";
    printPoint(p1);
    cout << (isPointOnCircle(p1, circle) ? " находится" : " не находится") << " на окружности" << endl;
    cout << "Точка ";
    printPoint(p1);
    cout << (isPointOnSquare(p1, square) ? " находится" : " не находится") << " на границе квадрата" << endl;
    
    // Создаем вторые фигуры для проверки пересечений и принадлежностей
    cout << "\n--- Создание второй фигуры каждого типа ---" << endl;
    Circle circle2 = readCircle();
    Square square2 = readSquare();
    
    // Проверка пересечений
    cout << "\n--- Проверка пересечений ---" << endl;
    cout << "Круги ";
    printCircle(circle);
    cout << " и ";
    printCircle(circle2);
    cout << (circlesIntersect(circle, circle2) ? " пересекаются" : " не пересекаются") << endl;
    
    cout << "Квадраты ";
    printSquare(square);
    cout << " и ";
    printSquare(square2);
    cout << (squaresIntersect(square, square2) ? " пересекаются" : " не пересекаются") << endl;
    
    cout << "Круг ";
    printCircle(circle);
    cout << " и квадрат ";
    printSquare(square);
    cout << (circleSquareIntersect(circle, square) ? " пересекаются" : " не пересекаются") << endl;
    
    // Проверка принадлежности фигур
    cout << "\n--- Проверка принадлежности фигур ---" << endl;
    cout << "Круг ";
    printCircle(circle);
    cout << (isCircleInCircle(circle, circle2) ? " находится" : " не находится") << " внутри круга ";
    printCircle(circle2);
    cout << endl;
    
    cout << "Квадрат ";
    printSquare(square);
    cout << (isSquareInSquare(square, square2) ? " находится" : " не находится") << " внутри квадрата ";
    printSquare(square2);
    cout << endl;
    
    cout << "Квадрат ";
    printSquare(square);
    cout << (isSquareInCircle(square, circle) ? " находится" : " не находится") << " внутри круга ";
    printCircle(circle);
    cout << endl;
    
    cout << "Круг ";
    printCircle(circle);
    cout << (isCircleInSquare(circle, square) ? " находится" : " не находится") << " внутри квадрата ";
    printSquare(square);
    cout << endl;
    
    return 0;
}