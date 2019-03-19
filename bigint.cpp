#include "pch.h"
#include "bigint.h"
#include <deque>
#include <string>

BigInt::BigInt() : isNegative(false), inputSize(0), invalidInt(false)
{
}

BigInt::BigInt(std::string s) : isNegative(false), inputSize(0), invalidInt(false)
{
    std::copy(s.begin(), s.end(), std::back_inserter(input));
}

BigInt::BigInt(const BigInt & myint)
{
    this->input = myint.input;
    this->inputSize = myint.inputSize;
    this->invalidInt = myint.invalidInt;
    this->isNegative = myint.isNegative;
}

BigInt BigInt::operator=(std::string const & s)
{
    std::copy(s.begin(), s.end(), std::back_inserter(input));
    BigInt f(s);
    return f;
}

std::istream & operator >>(std::istream & stream, BigInt & myint)
{
        std::string s;
        stream >> s;
        std::size_t found = s.find_first_not_of("-0123456789");
        if(found != std::string::npos){
           myint.invalidInt = true;
            return stream;
        }
        //copy string into vector without leading negative sign
        if(s[0] == '-'){
            myint.isNegative = true;
            std::copy(s.begin() + 1, s.end(), std::back_inserter(myint.input));
            myint.inputSize =(s.length() - 1);
        }
        else{
            std::copy(s.begin(), s.end(), std::back_inserter(myint.input));
            myint.inputSize =(s.length());
        }
        return stream;
}
std::ostream & operator <<(std::ostream & stream, BigInt & myint)
{
    std::string s;
    std::vector<char>::iterator it;

    it = myint.input.begin();
    while(it != myint.input.end()){
        s += *it;
        it++;
    }

    if(myint.invalidInt == true){
        std::string err(myint.input.begin(), myint.input.end());
        s += "INVALID: " + err;
    }
    stream << s;
    return stream;
}

BigInt operator+(BigInt & lhs, BigInt & rhs)
{
    BigInt result;
    std::deque<char> dq;
    std::string res;

    if(lhs.invalidInt){
        return lhs;
    }
    if(rhs.invalidInt){
        return rhs;
    }

    //if both are negative, negate result
    if(lhs.isNegative == true && rhs.isNegative == true){
        res += '-';
    }

    //if only lhs is negative
    else if(lhs.isNegative == true){
        //if equal -/+ numbers, sum will be zero
        if(lhs == rhs){
            result = "0";
            return result;
        }
        else if(lhs > rhs){
            lhs.isNegative = false;
            result = lhs - rhs;
            result.input.insert(result.input.begin(),'-');
            return result;
        }
        else if(lhs < rhs){
            lhs.isNegative = false;
            result = rhs - lhs;
            return result;
        }
    }
    //if rhs is negative
    else if(rhs.isNegative == true){
        if(lhs == rhs){
            result = "0";
            return result;
        }
         if(lhs > rhs){
            rhs.isNegative = false;
            result = lhs - rhs;
            return result;
        }
         else if(lhs > rhs){
            rhs.isNegative = false;
            result = rhs - lhs;
            result.input.insert(result.input.begin(),'-');
            return result;
        }
    }

    bool carry = false;
    int temp;
    std::vector<char>::iterator itLhs = lhs.input.end() - 1;
    std::vector<char>::iterator itRhs = rhs.input.end() - 1;
    while (itLhs >= lhs.input.begin() && itRhs >= rhs.input.begin()) {
            temp = (*itLhs - '0') + (*itRhs - '0');
            if (carry == true) {
                    temp++;
            }
            if (temp > 9) {
                    carry = true;
                    temp -= 10;
            }
            else { carry = false; }
            itLhs--;
            itRhs--;
            dq.push_front(static_cast<char>('0' + temp));
    }

    while (itLhs >= lhs.input.begin()) {
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
            dq.push_front(static_cast<char>('0' + temp));
            itLhs--;

    }
    while (itRhs >= rhs.input.begin()) {
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
            itRhs--;
            dq.push_front(static_cast<char>('0' + temp));
    }
    if (carry == true) {
            dq.push_front('1');
    }

    while (!dq.empty()) {
            res += dq.front();
            dq.pop_front();
    }
    result = res;
    return result;
}

BigInt operator-(BigInt & lhs, BigInt & rhs)
{
    BigInt result;
    std::deque<char> dq;
    std::string res;

    if(lhs.invalidInt){
        return lhs;
    }
    if(rhs.invalidInt){
        return rhs;
    }
    // Case 1:  Two negative integers
    if(lhs.isNegative == true && rhs.isNegative == true){
        if(lhs == rhs){
            result = "0";
            return result;
        }
        else if(lhs > rhs){
            rhs.isNegative = false;
            lhs.isNegative = false;
            res += '-';
        }
        //case C:
        else if(lhs < rhs){
            rhs.isNegative = false;
            lhs.isNegative = false;
            std::vector<char> temp;
            temp = lhs.input;
            lhs.input = rhs.input;
            rhs.input = temp;
        }
    }
    else if(lhs.isNegative){
        rhs.isNegative = true;
        result = lhs + rhs;
        return result;
    }
    //if rhs is negative, result is positive, regular add
    else if(rhs.isNegative){
        rhs.isNegative = false;
        result = lhs + rhs;
        return result;
    }
    //two positive numbers
    else{
        if(lhs == rhs){
            result = "0";
            return result;
        }
        if(lhs < rhs){
            res += '-';
            std::vector<char> temp;
            temp = lhs.input;
            lhs.input = rhs.input;
            rhs.input = temp;
        }
    }

    std::vector<char>::iterator itLhs = lhs.input.end() - 1;
    std::vector<char>::iterator itRhs = rhs.input.end() - 1;
    bool borrow = false;
    int temp = 0;

    //Reverse iterate through integer strings
    while (itLhs >= lhs.input.begin() && itRhs >= rhs.input.begin()) {
            if (borrow == true) {
                temp = (*itLhs - '0') - 1 - (*itRhs - '0');
            }
            if(borrow == false){
                temp = (*itLhs - '0') - (*itRhs - '0');
            }
            if (temp < 0) {
                borrow = true;
                temp = (*itLhs - '0') + 10 - (*itRhs - '0');
            }
            else{
                borrow = false;
            }
            itLhs--;
            itRhs--;
            dq.push_front(static_cast<char>('0' + temp));
    }
    //fill any remaining digits
    while (itLhs >= lhs.input.begin()) {
            if (borrow == true) {
                    temp = (*itLhs - '0') - 1;
            }
            else{
                temp = (*itLhs - '0');
            }

            if (temp > 0) {
                dq.push_front(static_cast<char>('0' + temp));
            }
            itLhs--;
    }

    while (!dq.empty()) {
            res += dq.front();
            dq.pop_front();
    }
    result = res;
    return result;
}

BigInt operator*(BigInt & lhs, BigInt & rhs)
{
    //check for invalid input
    if(lhs.invalidInt == true){
        return lhs;
    }
    if(rhs.invalidInt == true){
        return rhs;
    }
    //stores intermediate result of multiplication
    std::deque<char> row;
    int rNum = 0;

    int temp = 0;
    int carry = 0;
    //stores all rows to be added together after multiplication
    std::vector<BigInt> rows;

    //Reverse iterate through integer vectors
    int idxL = lhs.inputSize - 1;
    int idxR = rhs.inputSize - 1;
    while(idxR >= 0){
        idxL = lhs.inputSize - 1;
        carry = 0;
        while(idxL >= 0){
          temp = (rhs.input[idxR] - '0') * (lhs.input[idxL] - '0') + carry;
          if(temp > 9){
                carry = temp / 10;
                temp = temp % 10;
          }
          else{carry = 0;}
            idxL--;
            char c = '0' + temp;
            row.push_front(c);
        }
        if(carry > 0){
            char c = '0' + carry;
            row.push_front(c);
        }

        BigInt r;
        while(!row.empty()){
            r.input.push_back(row.front());
            row.pop_front();
        }
        int q = 0;
        while(q < rNum){
            r.input.push_back('0');
            q++;
        }
        rows.push_back(r);
        rNum++;
        idxR--;
    }

    int i = 0;
    BigInt result;
    result.input.push_back('0');

    while(i < rNum){
        BigInt current;
        current.input = rows[i].input;
        result.isNegative = false;
        current.isNegative = false;
        BigInt res2;
        res2 = result + current;
        result = res2;
        i++;
    }
    if(lhs.isNegative && !rhs.isNegative){
        result.input.insert(result.input.begin(),'-');
    }
    else if(!lhs.isNegative && rhs.isNegative){
        result.input.insert(result.input.begin(),'-');
    }
    return result;
}

bool operator==(BigInt & lhs, BigInt & rhs)
{
    if(lhs.inputSize < rhs.inputSize ){
        return false;
    }
    else if(lhs.inputSize > rhs.inputSize ){
        return false;
    }
    else{
        std::vector<char>::iterator itLhs = lhs.input.begin();
        std::vector<char>::iterator itRhs = rhs.input.begin();

        while(itLhs != lhs.input.end()){
            if(*itLhs < *itRhs){
                return false;
            }
            else if(*itLhs > *itRhs){
                return false;
            }
            else{
                itLhs++;
                itRhs++;
            }

        }
        return true;
    }
}

bool operator<(BigInt & lhs, BigInt & rhs)
{
    if(lhs.inputSize < rhs.inputSize ){
        return true;
    }
    else if(lhs.inputSize > rhs.inputSize ){
        return false;
    }
    else{
        std::vector<char>::iterator itLhs = lhs.input.begin();
        std::vector<char>::iterator itRhs = rhs.input.begin();

        while(itLhs != lhs.input.end()){
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

        }
    }
}

bool operator>(BigInt & lhs, BigInt & rhs)
{
    if(lhs.inputSize > rhs.inputSize ){
        return true;
    }
    else if(lhs.inputSize < rhs.inputSize ){
        return false;
    }
    else{
        std::vector<char>::iterator itLhs = lhs.input.begin();
        std::vector<char>::iterator itRhs = rhs.input.begin();

        while(itLhs != lhs.input.end()){
            if(*itLhs < *itRhs){
                return false;
            }
            else if(*itLhs > *itRhs){
                return true;
            }
            else{
                itLhs++;
                itRhs++;
            }

        }

    }
}
