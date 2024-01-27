#include <iostream>
#include <vector>
using namespace std;
class Shape {
   public:
    virtual double area() const = 0;
};
class Rectangle : public Shape {
   public:
    Rectangle() : x(0.0), y(0.0){};
    Rectangle(double _x, double _y) : x(_x), y(_y){};
    double area() const override;

   private:
    double x;
    double y;
};

class Circle : public Shape {
   public:
    Circle() : r(0.0){};
    Circle(double _r) : r(_r){};
    double area() const override;

   private:
    double r;
};

double Rectangle::area() const { return x * y; }
double Circle::area() const { return r * r * 3.14159; }

double totalAreas(const vector<Shape *> vect) {
    double sum = 0;
    for (auto obj : vect) {
        sum += obj->area();
    }
    return sum;
}

int main() {
    vector<Shape *> vect;
    Rectangle kare(2, 4);
    Circle cember(3);
    vect.push_back(&cember);
    vect.push_back(&kare);
    cout << totalAreas(vect);
}