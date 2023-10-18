#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm> // для алгоритма сортировки
using namespace std;

class Point{
public:
    double x, y;
    Point(){
        x = 0; y = 0;
    }
    Point(double x, double y){
        this -> x = x; this -> y = y;
    }
    double distance() const{
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    // Переопределение оператора <
    bool operator <(const Point& p1) const{
        double d1 = this->distance();
        double d2 = p1.distance();
        return (d1 < d2);
    }
};
// Стандартный выходной поток cout имеет тип std::ostream.
// Поэтому первый параметр (левый операнд) представляет объект ostream,
// а второй (правый операнд) - выводимый объект Point.
// Поскольку мы не можем изменить стандартное определение std::ostream,
// поэтому определяем функцию оператора, которая не является членом класса.
ostream& operator<<(ostream& stream, const Point& point)
{
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}

int main()
{
    vector<Point> v;
    v.push_back(Point(1,2));
    v.push_back(Point(10,12));
    v.push_back(Point(21,7));
    v.push_back(Point(4,8));
    sort(v.begin(), v.end()); // требуется перегрузка оператора < для
// класса Point
    for (auto &point : v)
        std::cout << point << '\n'; // требуется перегрузка оператора << для
// класса Point
    return 0;
}
