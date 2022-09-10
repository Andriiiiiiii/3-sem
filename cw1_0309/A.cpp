#include <iostream>

using namespace std;

void swap(void* a, void* b)
{
	void* c = a;
	a = b;
	b = c;
}

int main()
{
	char A, B;
	A = 'a';
	B = 'b';
	//void* a = &A;
	//void* b = &B;
	cout << " A = " << A << " B = " << B << endl;
	swap(A, B);
	cout << " A = " << A << " B = " << B;
	return 0;
}