#include <iostream>
#include "SymmetricGroup.h"
#include "Matrix.h"

int main()
{
    Matrix m1, m2;
    std::cin >> m1;
    m1.ChangeSignOfRow(1);
    std::cout << m1;
    system("pause");
    return 0;
}
