#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Utility function to add two large numbers
string addStrings(string num1, string num2) {
    // Make sure num1 is the longer string
    if (num1.length() < num2.length()) {
        swap(num1, num2);
    }

    string result = "";
    int carry = 0;
    int diff = num1.length() - num2.length();

    // Add digits from the rightmost position
    for (int i = num2.length() - 1; i >= 0; i--) {
        int sum = (num2[i] - '0') + (num1[i + diff] - '0') + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    // Add remaining digits of num1
    for (int i = num1.length() - num2.length() - 1; i >= 0; i--) {
        int sum = (num1[i] - '0') + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    // Add any remaining carry
    if (carry) {
        result.push_back(carry + '0');
    }

    // Reverse the result
    reverse(result.begin(), result.end());
    return result;
}

// Utility function to subtract two large numbers (num1 > num2)
string subtractStrings(string num1, string num2) {
    string result = "";
    int carry = 0;

    // Make the strings the same length by padding zeros
    while (num2.length() < num1.length()) {
        num2 = '0' + num2;
    }

    // Subtract from rightmost digit
    for (int i = num1.length() - 1; i >= 0; i--) {
        int sub = (num1[i] - '0') - (num2[i] - '0') - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(sub + '0');
    }

    // Remove leading zeros
    while (result.length() > 1 && result.back() == '0') {
        result.pop_back();
    }

    reverse(result.begin(), result.end());
    return result;
}

// Utility function to multiply two large numbers using long multiplication (single digit)
string multiplySingleDigit(string num1, char digit) {
    string result = "";
    int carry = 0;

    for (int i = num1.length() - 1; i >= 0; i--) {
        int mul = (num1[i] - '0') * (digit - '0') + carry;
        carry = mul / 10;
        result.push_back(mul % 10 + '0');
    }

    if (carry) {
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());
    return result;
}

// Function to multiply a number with 10^shift (just add zeros at the end)
string shiftLeft(string num, int shift) {
    return num + string(shift, '0');
}

// Karatsuba multiplication function
string karatsuba(string num1, string num2) {
    // Base case for recursion: single-digit multiplication
    if (num1.length() == 1 && num2.length() == 1) {
        int result = (num1[0] - '0') * (num2[0] - '0');
        return to_string(result);
    }

    // Make both numbers the same length by padding with zeros
    while (num1.length() < num2.length()) num1 = '0' + num1;
    while (num2.length() < num1.length()) num2 = '0' + num2;

    int n = num1.length();
    int half = n / 2;

    // Split the numbers into two halves
    string X1 = num1.substr(0, half);
    string X0 = num1.substr(half);
    string Y1 = num2.substr(0, half);
    string Y0 = num2.substr(half);

    // Recursively compute P1, P2, and P3
    string P1 = karatsuba(X1, Y1);
    string P2 = karatsuba(X0, Y0);
    string P3 = karatsuba(addStrings(X1, X0), addStrings(Y1, Y0));

    // Combine the results
    string part1 = shiftLeft(P1, 2 * (n - half));  // P1 * 10^2m
    string part2 = shiftLeft(subtractStrings(subtractStrings(P3, P1), P2), n - half); // (P3 - P1 - P2) * 10^m
    string result = addStrings(addStrings(part1, part2), P2);  // Final result

    return result;
}

int main() {
    // Input two large integers
    string num1, num2;
    cout << "Enter first large integer: ";
    cin >> num1;
    cout << "Enter second large integer: ";
    cin >> num2;

    // Multiply using Karatsuba algorithm
    string product = karatsuba(num1, num2);

    // Output the result
    cout << "Product of the two large integers: " << product << endl;

    return 0;
}
