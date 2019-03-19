#include<string>
#include<vector>
#pragma once
class BigInt
{
public:
        BigInt();

        BigInt(std::string);
        BigInt(const BigInt &);
        ~BigInt(){}
        BigInt operator=(std::string const &);

        friend std::istream& operator>>(std::istream &, BigInt &);
        friend std::ostream& operator<<(std::ostream &, BigInt &);

        friend BigInt operator+(BigInt &, BigInt&);
        friend BigInt operator-(BigInt &, BigInt&);
        friend BigInt operator*(BigInt &, BigInt &);
        friend BigInt operator/(BigInt &, BigInt &);
        friend BigInt operator%(BigInt &, BigInt &);

        friend bool operator<(BigInt &, BigInt &);
        friend bool operator>(BigInt &, BigInt &);
        friend bool operator==(BigInt &, BigInt &);



private:
        std::vector<char> input;
        bool isNegative;
        int inputSize;
        bool invalidInt;
};

