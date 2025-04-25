#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

// Convert base string to decimal
unsigned long long base_to_decimal(const string& value, int base) {
    unsigned long long result = 0;
    for (char ch : value) {
        int digit = isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}

// Lagrange Interpolation at x = 0
unsigned long long lagrange_interpolation(const vector<int>& x, const vector<unsigned long long>& y, int k) {
    long double result = 0.0;

    for (int i = 0; i < k; ++i) {
        long double term = static_cast<long double>(y[i]);
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0.0 - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }

    return static_cast<unsigned long long>(round(result));
}

int main() {
    ifstream file("input.json");
    json j;
    file >> j;

    int k = j["keys"]["k"];
    vector<int> x_vals;
    vector<unsigned long long> y_vals;

    for (int i = 1; x_vals.size() < k; ++i) {
        string idx = to_string(i);
        if (j.contains(idx)) {
            int x = i;
            int base = stoi(j[idx]["base"].get<string>());
            string value = j[idx]["value"];
            unsigned long long y = base_to_decimal(value, base);
            x_vals.push_back(x);
            y_vals.push_back(y);
        }
    }

    unsigned long long secret = lagrange_interpolation(x_vals, y_vals, k);
    cout << secret << endl;
    return 0;
}
