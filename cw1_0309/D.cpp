#include<iostream>
#include<limits>

using namespace std;

int main()
{
    cout << "char" << ' ' << CHAR_BIT * sizeof(char) << ' ' << int(numeric_limits<char>::min()) << ' ' << int(numeric_limits<char>::max()) << '\n';
    cout << "short int" << ' ' << CHAR_BIT * sizeof(short int) << ' ' << numeric_limits<short int>::min() << ' ' << numeric_limits<short int>::max() << '\n';
    cout << "int" << ' ' << CHAR_BIT * sizeof(int) << ' ' << numeric_limits<int>::min() << ' ' << numeric_limits<int>::max() << '\n';
    cout << "long int" << ' ' << CHAR_BIT * sizeof(long int) << ' ' << numeric_limits<long int>::min() << ' ' << numeric_limits<long int>::max() << '\n';
    cout << "float" << ' ' << CHAR_BIT * sizeof(float) << ' ' << numeric_limits<float>::min() << ' ' << numeric_limits<float>::max() << '\n';
    cout << "double" << ' ' << CHAR_BIT * sizeof(double) << ' ' << numeric_limits<double>::min() << ' ' << numeric_limits<double>::max() << '\n';
    return 0;
}