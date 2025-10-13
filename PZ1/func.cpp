#include "func.h"
#include <iostream>
#include <cmath>

using namespace std;

const double EPSILON = 1e-5;

// Вспомогательная функция для сравнения с учетом погрешности
bool areEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

// Функции для точки
Point readPoint() {
    Point p;
    cout << "Введите координаты точки (x y): ";
    cin >> p.x >> p.y;
    return p;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

// Функции для круга
Circle readCircle() {
    Circle c;
    cout << "Введите координаты центра круга (x y): ";
    cin >> c.center.x >> c.center.y;
    cout << "Введите радиус круга: ";
    cin >> c.radius;
    return c;
}

void printCircle(const Circle& c) {
    cout << "Круг: центр ";
    printPoint(c.center);
    cout << ", радиус = " << c.radius;
}

double circleCircumference(const Circle& c) {
    return 2 * 3.14 * c.radius;
}

double circleArea(const Circle& c) {
    return 3.14 * c.radius * c.radius;
}

// Функции для квадрата
Square readSquare() {
    Square s;
    cout << "Введите координаты левого верхнего угла квадрата (x y): ";
    cin >> s.topLeft.x >> s.topLeft.y;
    cout << "Введите длину стороны квадрата: ";
    cin >> s.side;
    return s;
}

void printSquare(const Square& s) {
    cout << "Квадрат: левый верхний угол ";
    printPoint(s.topLeft);
    cout << ", сторона = " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

// Принадлежность точки фигуре
bool isPointInCircle(const Point& p, const Circle& c) {
    double distanceSquared = pow(p.x - c.center.x, 2) + pow(p.y - c.center.y, 2);
    return distanceSquared < pow(c.radius, 2) - EPSILON;
}

bool isPointInSquare(const Point& p, const Square& s) {
    return (p.x > s.topLeft.x + EPSILON) && 
           (p.x < s.topLeft.x + s.side - EPSILON) &&
           (p.y < s.topLeft.y - EPSILON) && 
           (p.y > s.topLeft.y - s.side + EPSILON);
}

// Нахождение точки на контуре
bool isPointOnCircle(const Point& p, const Circle& c) {
    double distanceSquared = pow(p.x - c.center.x, 2) + pow(p.y - c.center.y, 2);
    return areEqual(distanceSquared, pow(c.radius, 2));
}

bool isPointOnSquare(const Point& p, const Square& s) {
    bool onVerticalLeft = areEqual(p.x, s.topLeft.x) && 
                         (p.y <= s.topLeft.y + EPSILON) && 
                         (p.y >= s.topLeft.y - s.side - EPSILON);
    
    bool onVerticalRight = areEqual(p.x, s.topLeft.x + s.side) && 
                          (p.y <= s.topLeft.y + EPSILON) && 
                          (p.y >= s.topLeft.y - s.side - EPSILON);
    
    bool onHorizontalTop = areEqual(p.y, s.topLeft.y) && 
                          (p.x >= s.topLeft.x - EPSILON) && 
                          (p.x <= s.topLeft.x + s.side + EPSILON);
    
    bool onHorizontalBottom = areEqual(p.y, s.topLeft.y - s.side) && 
                             (p.x >= s.topLeft.x - EPSILON) && 
                             (p.x <= s.topLeft.x + s.side + EPSILON);
    
    return onVerticalLeft || onVerticalRight || onHorizontalTop || onHorizontalBottom;
}

// Пересечение фигур
bool circlesIntersect(const Circle& c1, const Circle& c2) {
    double distance = sqrt(pow(c1.center.x - c2.center.x, 2) + 
                          pow(c1.center.y - c2.center.y, 2));
    return distance <= c1.radius + c2.radius + EPSILON;
}

bool squaresIntersect(const Square& s1, const Square& s2) {
    // Проверка пересечения по оси X
    bool xOverlap = (s1.topLeft.x <= s2.topLeft.x + s2.side + EPSILON) &&
                   (s1.topLeft.x + s1.side >= s2.topLeft.x - EPSILON);
    
    // Проверка пересечения по оси Y
    bool yOverlap = (s1.topLeft.y >= s2.topLeft.y - s2.side - EPSILON) &&
                   (s1.topLeft.y - s1.side <= s2.topLeft.y + EPSILON);
    
    return xOverlap && yOverlap;
}

bool circleSquareIntersect(const Circle& c, const Square& s) {
    // Находим ближайшую точку квадрата к центру круга
    double closestX = max(s.topLeft.x, min(c.center.x, s.topLeft.x + s.side));
    double closestY = min(s.topLeft.y, max(c.center.y, s.topLeft.y - s.side));
    
    // Вычисляем расстояние от центра круга до ближайшей точки квадрата
    double distance = sqrt(pow(c.center.x - closestX, 2) + 
                          pow(c.center.y - closestY, 2));
    
    return distance <= c.radius + EPSILON;
}

// Принадлежность фигур
bool isCircleInCircle(const Circle& inner, const Circle& outer) {
    double distance = sqrt(pow(inner.center.x - outer.center.x, 2) + 
                          pow(inner.center.y - outer.center.y, 2));
    return distance + inner.radius <= outer.radius + EPSILON;
}

bool isSquareInSquare(const Square& inner, const Square& outer) {
    return (inner.topLeft.x >= outer.topLeft.x - EPSILON) &&
           (inner.topLeft.x + inner.side <= outer.topLeft.x + outer.side + EPSILON) &&
           (inner.topLeft.y <= outer.topLeft.y + EPSILON) &&
           (inner.topLeft.y - inner.side >= outer.topLeft.y - outer.side - EPSILON);
}

bool isSquareInCircle(const Square& s, const Circle& c) {
    // Проверяем, что все углы квадрата находятся внутри круга
    Point corners[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };
    
    for (const Point& corner : corners) {
        double distanceSquared = pow(corner.x - c.center.x, 2) + 
                                pow(corner.y - c.center.y, 2);
        if (distanceSquared > pow(c.radius, 2) + EPSILON) {
            return false;
        }
    }
    return true;
}

bool isCircleInSquare(const Circle& c, const Square& s) {
    // Проверяем, что круг полностью внутри квадрата
    return (c.center.x - c.radius >= s.topLeft.x - EPSILON) &&
           (c.center.x + c.radius <= s.topLeft.x + s.side + EPSILON) &&
           (c.center.y + c.radius <= s.topLeft.y + EPSILON) &&
           (c.center.y - c.radius >= s.topLeft.y - s.side - EPSILON);
}