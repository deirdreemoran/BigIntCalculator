#include <QCoreApplication>
#include "pch.h"
#include "BigInt.h"

void runTests();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    runTests();

    std::cout << "BIG INTEGER CALCULATOR\n\n";
    std::cout << "Perform addition or subtraction on integers of any size.\n";
    while (1) {
        std::string oper;
        BigInt num1;
        BigInt num2;
        std::cout << "------------------------\n";
        std::cout << "Enter 1st number: ";
        std::cin >> num1;
        std::cout << std::endl;
        std::cout << "Operator + or - : ";
        std::cin >> oper;
        if(oper != "+" && oper != "-" && oper != "*"){
            std::cout <<"\nError:  Incorrect operator\n\n";
            continue;
        }
        std::cout << std::endl;
        std::cout << "Enter 2nd number: ";
        std::cin >> num2;
        BigInt result;

        if(oper == "-"){
            result = num1 - num2;
        }
        else if (oper == "+"){
            result = num1 + num2;
        }
        else if (oper == "*"){
            result = num1 * num2;
        }
        std::cout << "\nAnswer = " << result << std::endl;
    }
    return a.exec();
}

//TODO: formal testing
void runTests(){

    BigInt num1;// = INT_MAX;
    BigInt num2;// = INT_MIN;
    BigInt result;

    num1 = "99999999999999999999999999999999999999999999999";
    num2 = "99999999999999999999999999999999999999999999999";

    result = num1 + num2;
    std::cout << "\n" << result << " ";
    result = num2 + 36 + num2 + 73;
    result = 36 + num2;
    std::cout << result;
    //if(result == num1 + num2d);


}
