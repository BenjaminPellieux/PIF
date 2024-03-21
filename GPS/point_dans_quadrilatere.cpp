#include <iostream>

struct Point {
    double x, y;
};

double produitVectoriel(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool pointDansQuadrilatere(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& point) {
    // Vérifier le premier triangle
    if (
        produitVectoriel(p1, p2, point) >= 0 &&
        produitVectoriel(p2, p3, point) >= 0 &&
        produitVectoriel(p3, p1, point) >= 0
    ) {
        return true;
    }

    // Vérifier le deuxième triangle
    if (
        produitVectoriel(p1, p3, point) >= 0 &&
        produitVectoriel(p3, p4, point) >= 0 &&
        produitVectoriel(p4, p1, point) >= 0
    ) {
        return true;
    }

    return false;
}

int main() {
    Point p1 = {1, 1};
    Point p2 = {5, 1};
    Point p3 = {4, 5};
    Point p4 = {2, 4};
    Point point = {3, 3};

    if (pointDansQuadrilatere(p1, p2, p3, p4, point)) {
        std::cout << "Le point est à l'intérieur du quadrilatère." << std::endl;
    } else {
        std::cout << "Le point est à l'extérieur du quadrilatère." << std::endl;
    }

    return 0;
}