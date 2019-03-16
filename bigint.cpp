#include "pch.h"
#include "bigint.h"
#include <deque>
#include <string>

BigInt::BigInt() : neg(false), sz(0)
{

}

BigInt::BigInt(std::string s)
{
     std::copy(s.begin(), s.end(), std::back_inserter(numString));
}

BigInt::BigInt(double d)
{

}

BigInt::BigInt(long d)
{
}

BigInt::BigInt(long long d)
{
}

BigInt::~BigInt()
{
}

std::istream & operator >>(std::istream & stream, BigInt & myint) {
        std::string s;
        stream >> s;
        //strip negative if exists, copy string into vector
        if(s[0] == '-'){
            myint.neg = true;
            std::copy(s.begin() + 1, s.end(), std::back_inserter(myint.numString));
            myint.sz = s.length() - 1;
        }
        else{
            myint.neg = false;
            std::copy(s.begin(), s.end(), std::back_inserter(myint.numString));
            myint.sz = s.length();

        }
        return stream;
}

std::ostream & operator <<(std::ostream & stream, BigInt & myint) {
    std::string s;
    std::vector<char>::iterator it;
    it = myint.numString.begin();
    while(it != myint.numString.end()){
        s += *it;
        it++;
    }
    stream << s;
    return stream;
}


BigInt operator+(BigInt & lhs, BigInt & rhs)
{
    std::deque<int> dq;
    std::string res;
    //if both negative, normal add and then make result negative
    if(lhs.neg == true && rhs.neg == true){
            res += '-';
    }
    //if lhs is negative
    else if(lhs.neg == true){
        //if lhs > rhs
        if(lhs.numString > rhs.numString){
            lhs.neg = false;
            BigInt b;
            b.numString.push_back('-');
            BigInt bb = lhs - rhs;
            b.numString.insert(
                 b.numString.end(),
                 std::make_move_iterator(bb.numString.begin()),
                 std::make_move_iterator(bb.numString.end())
               );
            return b;
        }
        else if(lhs.numString < rhs.numString){
            lhs.neg = false;
            BigInt bb = rhs - lhs;
            return bb;

        }
        else{
            res = "0";
            BigInt b = res;
            return b;        }
    }
    //if rhs is negative
    else if(rhs.neg == true){
         if(lhs.numString > rhs.numString){
            rhs.neg = false;
            BigInt bb = lhs - rhs;
            return bb;
        }
         else if(lhs.numString > rhs.numString){
            rhs.neg = false;
            BigInt b;
            b.numString.push_back('-');
            BigInt bb = rhs - lhs;
            b.numString.insert(
                 b.numString.end(),
                 std::make_move_iterator(bb.numString.begin()),
                 std::make_move_iterator(bb.numString.end())
               );
            return b;
        }
    }



    bool carry = false;
    int lhsSize = static_cast<int>(lhs.numString.size());
    std::cout << "\nlhsSize: " << lhsSize << std::endl;
    int rhsSize = static_cast<int>(rhs.numString.size());
    std::cout << "\nrhsSize: " << rhsSize << std::endl;

    int temp;
    std::vector<char>::iterator itLhs = lhs.numString.end() - 1;
    std::vector<char>::iterator itRhs = rhs.numString.end() - 1;

    while (itLhs >= lhs.numString.begin() && itRhs >= rhs.numString.begin()) {
            temp = (*itLhs - '0') + (*itRhs - '0');
            if (carry == true) {
                    temp++;
            }
            if (temp > 9) {
                    carry = true;
                    temp -= 10;
            }
            else { carry = false; }
            std::cout << "\ntemp is : " << temp << std::endl;
            itLhs--;
            itRhs--;
            dq.push_front(temp);
    }
    while (itLhs >= lhs.numString.begin()) {
            //fill any remaining digits
            int temp = *itLhs - '0';
            if (carry == true) {
                    temp++;
            }

            if (temp > 9) {
                    carry = true;
                    temp -= 10;
            }
            else { carry = false; }
            std::cout << "\ntemp is : " << temp << std::endl;
            dq.push_front(temp);
            itLhs--;

    }
    while (itRhs >= rhs.numString.begin()) {
            //fill any remaining digits
            int temp = *itRhs - '0';
            if (carry == true) {
                    temp++;
            }

            if (temp > 9) {
                    carry = true;
                    temp -= 10;
            }
            else { carry = false; }
            std::cout << "\ntemp is : " << temp << std::endl;
            itRhs--;
            dq.push_front(temp);
    }
    if (carry == true) {
            dq.push_front(1);
    }

    while (!dq.empty()) {
            res += std::to_string(dq.front());
            dq.pop_front();
    }
    BigInt b(res);

    return b;
}



BigInt operator-(BigInt & lhs, BigInt & rhs)
{
    std::deque<int> dq;
    std::string res;
    //if both negative
    if(lhs.neg == true && rhs.neg == true){
        if(lhs.numString > rhs.numString){
            //make both pos, then add neg to result, then subtract
            rhs.neg = false;
            lhs.neg = false;
            res += '-';
        }
        else if(lhs.numString < rhs.numString){
            rhs.neg = false;
            lhs.neg = false;
            lhs.numString.swap(rhs.numString);
        }
        else{
            res = "0";
            BigInt b = res;
            return b;
        }
    }
    //if lhs is negative
    else if(lhs.neg == true){
        //change sign for second to neg, then add and return value with -
        rhs.neg = true;
        return lhs + rhs;
    }
    //if rhs is negative, just add, this is pos num
    else if(rhs.neg == true){
        rhs.neg = false;
        return lhs + rhs;
    }
    else{
        if(lhs.numString < rhs.numString){
            res += '-';
            lhs.numString.swap(rhs.numString);
        }
    }


    bool borrow = false;
    int lhsSize = static_cast<int>(lhs.numString.size());
    std::cout << "\nlhsSize: " << lhsSize << std::endl;
    int rhsSize = static_cast<int>(rhs.numString.size());
    std::cout << "\nrhsSize: " << rhsSize << std::endl;

    int temp;
    std::vector<char>::iterator itLhs = lhs.numString.end() - 1;
    std::vector<char>::iterator itRhs = rhs.numString.end() - 1;

    while (itLhs >= lhs.numString.begin() && itRhs >= rhs.numString.begin()) {
            if (borrow == true) {
                    temp = (*itLhs - '0') - 1 - (*itRhs - '0');
            }
            else{
                temp = (*itLhs - '0') - (*itRhs - '0');
            }
            if (temp < 0) {
                    borrow = true;
                    temp = (*itLhs - '0') + 10 - (*itRhs - '0');
            }
            else { borrow = false; }
            std::cout << "\ntemp is : " << temp << std::endl;
            itLhs--;
            itRhs--;
            dq.push_front(temp);
    }
    while (itLhs >= lhs.numString.begin()) {
            //fill any remaining digits
            if (borrow == true) {
                    temp = (*itLhs - '0') - 1;
            }
            else{
                temp = (*itLhs - '0');
            }

            if (temp > 0) {
                std::cout << "\ntemp is : " << temp << std::endl;
                dq.push_front(temp);
            }
            itLhs--;


    }

    while (!dq.empty()) {
            res += std::to_string(dq.front());
            dq.pop_front();
    }
    BigInt b(res);

    return b;
}




bool BigInt::lessThan(int lhs, int rhs)
{
        if (lhs < rhs) {
                return true;
        }
        else if (lhs >= rhs) {
                return false;
        }
}

bool BigInt::checkDigits(std::string s) {
        for (int i = 0; i < s.length(); i++) {
                if (!isdigit(s[i])) {
                        return false;
                }
        }
        return true;
}

bool BigInt::lessThan(std::string, std::string)
{
        return false;
}

bool BigInt::lessThan(std::string s, int i)
{
        if (!checkDigits(s)) {
                return false;
        }
        std::string iString = std::to_string(i);

        std::cout << "s length: " << s.length() << " " << s << std::endl;
        std::cout << "iString length: " << iString.length() << " " << iString << std::endl;

        if (s.length() < iString.length()) {
                return true;
        }
        else if (s.length() > iString.length()) {
                return false;
        }
        else {
                for (int j = 0; j < iString.length(); j++) {
                        std::cout << "in loop\n";
                        std::cout << (int)iString[j] - '0' << "\n";
                        if ((int)iString[j] - '0' < (int)s[j] - '0') {
                                std::cout << "return false\n";
                                return false;
                        }
                        else if ((int)iString[j] - '0' > (int)s[j] - '0') {
                                std::cout << "return true\n";
                                return true;


                        }
             }
                return false;
        }


}
bool BigInt::lessThan(BigInt & lhs, BigInt & rhs)
{
    if(lhs.sz < rhs.sz){
        return true;
    }
    else if(lhs.sz > rhs.sz){
        return false;
    }
    else{
        std::vector<char>::iterator itLhs = lhs.numString.begin();
        std::vector<char>::iterator itRhs = rhs.numString.begin();

        while(itLhs != lhs.numString.end()){
            if(*itLhs < *itRhs){
                return true;
            }
            else if(*itLhs > *itRhs){
                return false;
            }
            else{
                itLhs++;
                itRhs++;
            }
            //To DO: this means it is zero
            return true;
        }

    }
}
