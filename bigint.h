#include<string>
#include<vector>
#pragma once
class BigInt
{
public:
        BigInt();
        BigInt(int);
        BigInt(std::string);
        BigInt(double);
        BigInt(long);
        BigInt(long long);


        ~BigInt();

        bool lhsNeg;
        bool rhsNeg;

        bool lessThan(int, int);

        bool checkDigits(std::string s);
        bool lessThan(std::string, std::string);
        bool lessThan(std::string, int);
        bool lessThan(int, std::string);
        bool lessThan(BigInt&, BigInt&);
        friend std::istream& operator>>(std::istream &, BigInt &);
        friend std::ostream& operator<<(std::ostream &, BigInt &);
        friend BigInt operator+(BigInt &, BigInt&);
        friend BigInt operator-(BigInt &, BigInt&);
private:
        std::vector<char> numString;
        bool neg;
        int sz;
};

