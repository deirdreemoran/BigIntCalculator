#include <QCoreApplication>
#include "pch.h"
#include "BigInt.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    std::string oper;
    std::cout << "BIG INTEGER CALCULATOR\n\n";
    std::cout << "Perform addition, subtraction, or comparsion on any number\n";
    std::cout << "To use previous answer as variable, enter 'previous'\n";
    std::cout << "Examples:\n";
    std::cout << "\t4 + 5\t = 9\n";
    std::cout << "\tprevious - 5\t = 4\n";
    std::cout << "\t88 > 500\tfalse\n";
    std::cout << "\t88 < 500\ttrue\n";

    while (1) {
        BigInt num1;
        BigInt num2;
        std::cout << "Enter first number: ";
                std::cin >> num1;
                std::cout << std::endl;
                std::cout << "Enter operator: ";
                std::cin >> oper;
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
                std::cout << "\n" << num1 << " " << oper << " " << num2;
                std::cout << "\nanswer = " << summ << std::endl;


                //std::cout << num1 + num2;
               // res = c.lessThan(k, 999999);
                //std::cout << k << " < 999999: " << res << std::endl;
        }
       /* res = c.lessThan("33", 0);
        std::cout << 33 << " < 0: " << res << std::endl;

        res = c.lessThan(5, 0);
        std::cout << 5 << " < 0: " << res << std::endl;
        res = c.lessThan(0, 5);
        std::cout << 0 << " < 5: " << res << std::endl;
        res = c.lessThan(0, 0);
        std::cout << 0 << " < 0: " << res << std::endl;

        std::string s = "12345";
        // num1.add(s);
        std::string pstr = num1.add(s, p);
        std::cout << "\npstr: " << pstr << "\n";

        std::string str;
        str = num1.add(5, 3);
        std::cout << "str2: " << str << "\n";
        std::vector<char> g;
        //  g.push_back(num1.add(5, 7));
        // std::cout << g[0];*/
    return a.exec();

    }
