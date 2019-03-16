#include <QCoreApplication>
#include "pch.h"
#include "BigInt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string oper;

    std::cout << "BIG INTEGER CALCULATOR\n\n";
    std::cout << "Perform addition or subtraction on integers of any size.\n";

    while (1) {
        BigInt num1;
        BigInt num2;
        std::cout << "------------------------\n";
        std::cout << "Enter 1st number: ";
        std::cin >> num1;
        std::cout << std::endl;
        std::cout << "Operator + or - : ";
        std::cin >> oper;
        if(oper != "+" && oper != "-"){
            std::cout <<"\nError:  Incorrect operator\n\n";
            continue;
        }
        std::cout << std::endl;
        std::cout << "Enter 2nd number: ";
        std::cin >> num2;
        BigInt summ;
        if(oper == "-"){
            summ = num1 - num2;
        }
        else if (oper == "+"){
            summ = num1 + num2;
        }
        std::cout << "\nAnswer = " << summ << std::endl;
    }
    return a.exec();
}
