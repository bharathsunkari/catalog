#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include "json.hpp" // Include the downloaded nlohmann json header

using namespace std;
using json = nlohmann::json; // Alias for convenience

// Function to convert values from any base to base 10
long long baseToDecimal(const string &value, int base) {
    return stoll(value, nullptr, base); // Converts string in the given base to base 10
}

// Function to perform Lagrange interpolation to find the constant term 'c'
double lagrangeInterpolation(const vector<pair<int, long long>> &points) {
    int k = points.size();
    double constant = 0.0;

    for (int i = 0; i < k; ++i) {
        double term = points[i].second;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0.0 - points[j].first) / (points[i].first - points[j].first);
            }
        }
        constant += term;
    }

    return constant;
}

int main() {
    // JSON input for test case 2
    string jsonInput = R"({
        "keys": {
            "n": 9,
            "k": 6
        },
        "1": {
            "base": "10",
            "value": "28735619723837"
        },
        "2": {
            "base": "16",
            "value": "1A228867F0CA"
        },
        "3": {
            "base": "12",
            "value": "32811A4AA0B7B"
        },
        "4": {
            "base": "11",
            "value": "917978721331A"
        },
        "5": {
            "base": "16",
            "value": "1A22886782E1"
        },
        "6": {
            "base": "10",
            "value": "28735619654702"
        },
        "7": {
            "base": "14",
            "value": "71AB5070CC4B"
        },
        "8": {
            "base": "9",
            "value": "122662581541670"
        },
        "9": {
            "base": "8",
            "value": "642121030037605"
        }
    })";

    // Parse JSON using nlohmann/json
    json root = json::parse(jsonInput);

    int n = root["keys"]["n"];
    int k = root["keys"]["k"];

    vector<pair<int, long long>> points;

    // Decode the points
    for (auto it = root.begin(); it != root.end(); ++it) {
        if (it.key() == "keys") continue;

        int x = stoi(it.key());
        int base = stoi(it.value()["base"].get<string>());
        string value = it.value()["value"].get<string>();

        long long y = baseToDecimal(value, base);
        points.push_back({x, y});
    }

    // Find the constant term 'c' using Lagrange Interpolation
    double c = lagrangeInterpolation(points);
    cout << "Constant term c: " << c << endl;

    return 0;
}
