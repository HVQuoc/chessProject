class Point
{
public:
    int x, y;
    Point();
    bool operator==(Point other);
    Point operator+(const Point& p);
    void set(int x0, int y0);
    Point(int x0, int y0);
    int X();
    int Y();
};

