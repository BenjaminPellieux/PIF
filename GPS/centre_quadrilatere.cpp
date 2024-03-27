#include <iostream>

struct Point {
    double x, y;
};

Point trouverCentreQuadrilatere(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    Point centre;
    centre.x = (p1.x + p2.x + p3.x + p4.x) / 4.0;
    centre.y = (p1.y + p2.y + p3.y + p4.y) / 4.0;
    return centre;
}

int main() {
    // Définir les sommets du quadrilatère
    Point p1 = {1, 1};
    Point p2 = {5, 1};
    Point p3 = {4, 5};
    Point p4 = {2, 4};

    // Calculer le centre du quadrilatère
    Point centre = trouverCentreQuadrilatere(p1, p2, p3, p4);

    // Afficher les coordonnées du centre
    std::cout << "Le centre du quadrilatère est : (" << centre.x << ", " << centre.y << ")" << std::endl;

    return 0;
}