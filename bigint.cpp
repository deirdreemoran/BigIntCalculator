#include "pch.h"
#include "bigint.h"
#include <deque>
#include <string>

BigInt::BigInt() :isNegative(false), inputSize(0)
{
}

BigInt::BigInt(std::string s)
{
     std::copy(s.begin(), s.end(), std::back_inserter(input));
}

BigInt::~BigInt()
{
}

std::istream & operator >>(std::istream & stream, BigInt & myint) {
        std::string s;
        stream >> s;
        //check for valid digits
        std::size_t found = s.find_first_not_of("0123456789");
        if(found != std::string::npos){
            myint.errorFound = true;
            return stream;
        }

          //copy string into vector without leading negative sign
        if(s[0] == '-'){
            myint.isNegative = true;
            std::copy(s.begin() + 1, s.end(), std::back_inserter(myint.input));
            myint.inputSize = static_cast<int>(s.length() - 1);
        }
        else{
            myint.isNegative = false;
            std::copy(s.begin(), s.end(), std::back_inserter(myint.input));
            myint.inputSize = static_cast<int>(s.length());

        }
        return stream;
}

std::ostream & operator <<(std::ostream & stream, BigInt & myint) {
    std::string s;
    std::vector<char>::iterator it;

    it = myint.input.begin();

    while(it != myint.input.end()){
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
    //if both are negative, negate result
    if(lhs.isNegative == true && rhs.isNegative == true){
            res += '-';
    }
    //if only lhs is negative
    else if(lhs.isNegative == true){
        //if equal -/+ numbers, sum will be zero
        if(lhs == rhs){
            res = "0";
            BigInt b = res;
            return b;
        }
        else if(lhs > rhs){
            lhs.isNegative = false;
            BigInt b;
            b.input.push_back('-');
            BigInt bb = lhs - rhs;
            b.input.insert(
                 b.input.end(),
                 std::make_move_iterator(bb.input.begin()),
                 std::make_move_iterator(bb.input.end())
               );
            return b;
        }
        else if(lhs < rhs){
            lhs.isNegative = false;
            BigInt bb = rhs - lhs;
            return bb;
        }
    }
    //if rhs is negative
    else if(rhs.isNegative == true){
        if(lhs == rhs){
            res = "0";
            BigInt b = res;
            return b;
        }
         if(lhs > rhs){
            rhs.isNegative = false;
            BigInt bb = lhs - rhs;
            return bb;
        }
         else if(lhs > rhs){
            rhs.isNegative = false;
            BigInt b;
            b.input.push_back('-');
            BigInt bb = rhs - lhs;
            b.input.insert(
                 b.input.end(),
                 std::make_move_iterator(bb.input.begin()),
                 std::make_move_iterator(bb.input.end())
               );
            return b;
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
            dq.push_front(temp);
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
            dq.push_front(temp);
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

    if(lhs.isNegative == true && rhs.isNegative == true){
        if(lhs == rhs){
            res = "0";
            BigInt b = res;
            return b;
        }
        else if(lhs > rhs){
            std::cout << "\nlhs is greater than rhs\n";
            //make both pos, then addisNegative to result, then subtract
            rhs.isNegative = false;
            lhs.isNegative = false;
            res += '-';
        }
        else if(lhs < rhs){
            rhs.isNegative = false;
            lhs.isNegative = false;
            std::vector<char> temp;
            temp = lhs.input;
            lhs.input = rhs.input;
            rhs.input = temp;
        }
    }
    //if lhs isNegative
    else if(lhs.isNegative){
        //change sign for second toisNegative, then add and return value with -
        rhs.isNegative = true;
        return lhs + rhs;
    }
    //if rhs isisNegativeative, just add, this is pos num
    else if(rhs.isNegative){
        rhs.isNegative = false;
        return lhs + rhs;
    }
    //two positive numbers
    else{
        if(lhs == rhs){
            res = "0";
            BigInt b = res;
            return b;
        }
        if(lhs < rhs){
            res += '-';
            std::vector<char> temp;
            temp = lhs.input;
            lhs.input = rhs.input;
            rhs.input = temp;
        }
    }

    bool borrow = false;
    int temp = 0;
    std::vector<char>::iterator itLhs = lhs.input.end() - 1;
    std::vector<char>::iterator itRhs = rhs.input.end() - 1;

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
            dq.push_front(temp);
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

bool BigInt::checkDigits(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

BigInt operator*(BigInt & lhs, BigInt & rhs)
{

    std::string res;
    if(lhs.isNegative && !rhs.isNegative){
        res = "-";
    }
    else if(!lhs.isNegative && rhs.isNegative){
        res = "-";
    }

    std::vector<char>::iterator itLhs = lhs.input.end();
    std::vector<char>::iterator itRhs = rhs.input.end();
//  4563456
//  x    34
    std::deque<char> row;
    int temp = 0;
    int carry = 0;
    while(itRhs != rhs.input.begin()){
        itLhs = lhs.input.end();
        while(itLhs != lhs.input.begin()){
            temp = (*itRhs - '0') * (*itLhs - '0') + carry;
            if(temp > 9){
                carry = temp / 10;
                temp = temp % 10;
            }
            itLhs--;
            row.push_front(temp);
        }

        itRhs--;
    }
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
