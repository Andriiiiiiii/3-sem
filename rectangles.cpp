#include <string>
#include <iostream>

using namespace std;

struct Point
{
    unsigned long long x, y;
    Point(unsigned long long x, unsigned long long y) : x(x), y(y) { }
    Point minx(Point const& rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }
    Point miny(Point const& rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }
    Point maxx(Point const& rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }
    Point maxy(Point const& rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }
    void operator=(Point const& other)
    {
        x = other.x;
        y = other.y;
    }
    void print() const
    {
        cout << "(" << x << "," << y << ")" << endl;
    }
};

class Rectangle
{
public:
    Rectangle(Point const& point) : point(point) { }
    Rectangle() : Rectangle(Point(0, 0)) { }
    void print() const
    {
        point.print();
    }
    Rectangle operator*(const Rectangle& rha) const
    {
        Rectangle minx = Rectangle(point.minx(rha.point));
        Rectangle miny = Rectangle(minx.point.miny(rha.point));
        return minx;
    }
    Rectangle operator+(const Rectangle& rha) const {
        Rectangle minx = Rectangle(point.maxx(rha.point));
        Rectangle miny = Rectangle(minx.point.maxy(rha.point));
        return miny;
    }
    Rectangle& operator+=(Rectangle const& rha)
    {
        Rectangle temp = Rectangle(point.maxx(rha.point));
        *this = Rectangle(temp.point.maxy(rha.point));
        return *this;
    }
    Rectangle& operator*=(Rectangle const& rha)
    {
        Rectangle temp = Rectangle(point.minx(rha.point));
        *this = Rectangle(temp.point.miny(rha.point));
        return *this;
    }
private:
    Point point;
};


Rectangle StrtoRec(int& i, string str)
{
    int x = 0;
    i++;
    while (str[i] != ',')
    {
        x = 10 * x + str[i] - '0';
        i++;
    }
    i++;
    int y = 0;
    while (str[i] != ')')
    {
        y = 10 * y + str[i] - '0';
        i++;
    }
    Rectangle rec(Point(x, y));
    return rec;
}

Rectangle get_res(string str)
{
    int mult = 0;
    int brackets = 0;
    for (char c : str)
    {
        if (c == '*')
        {
            mult++;
        }
        if (c == '(')
        {
            brackets++;
        }
    }
    Rectangle* rec_to_sum = new Rectangle[brackets - mult];
    int i = 0;
    int k = 0;
    while (i < str.length())
    {
        Rectangle a(Point(0, 0));
        if (str[i] == '(')
        {
            Rectangle tmp = StrtoRec(i, str);
            a += tmp;
        }
        if (not(++i == str.length()))
        {
            while (str[i] == '*')
            {
                i++;
                Rectangle tmp = StrtoRec(i, str);
                i++;
                a *= tmp;
            }
        }
        i++;
        rec_to_sum[k] = a;
        k++;
    }
    Rectangle result;
    for (i = 0; i < brackets - mult; ++i)
    {
        result += rec_to_sum[i];
    }
    delete[] rec_to_sum;
    return result;
}

int main()
{
    string str;
    getline(cin, str);
    Rectangle result = get_res(str);
    result.print();
    return 0;
}
