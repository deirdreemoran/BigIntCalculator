#include<string>
#include<vector>
#pragma once

class BigInt
{
public:
        BigInt();
        BigInt(std::string);
        BigInt(int);
        BigInt(long);
        BigInt(const BigInt &);
        ~BigInt(){}

        BigInt operator=(std::string const &);

        friend std::istream& operator>>(std::istream &, BigInt &);
        friend std::ostream& operator<<(std::ostream &, BigInt &);

        BigInt operator+(BigInt &);
        BigInt operator+(int);
        BigInt operator+(long);

        friend BigInt operator+(BigInt&);

        friend BigInt operator-(BigInt &, BigInt&);
        friend BigInt operator-(int, BigInt&);
        friend BigInt operator-(BigInt &, int);

        friend BigInt operator*(BigInt &, BigInt &);
        friend BigInt operator/(BigInt &, BigInt &);
        friend BigInt operator%(BigInt &, BigInt &);

        friend bool operator<(BigInt &, BigInt &);
        friend bool operator>(BigInt &, BigInt &);
        friend bool operator==(BigInt &, BigInt &);
private:
        std::vector<char> input;
        bool isNegative;
        bool invalidInt;
};

