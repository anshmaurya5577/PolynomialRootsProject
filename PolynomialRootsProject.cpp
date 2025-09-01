#include <bits/stdc++.h>
#include "json.hpp"   // nlohmann/json
using namespace std;
using json = nlohmann::json;

// Function to convert string in given base to decimal
long long baseToDecimal(const string &num, int base) {
    long long result = 0;
    for (char c : num) {
        int digit;
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else
            digit = 10 + (tolower(c) - 'a');
        result = result * base + digit;
    }
    return result;
}

int main() {
    string filename;
    cout << "Enter JSON filename (e.g. test1.json): ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << endl;
        return 1;
    }

    // Parse JSON
    json j;
    file >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    // Prepare output file
    string outputFile = filename.substr(0, filename.find_last_of(".")) + "_output.txt";
    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error: Cannot create output file." << endl;
        return 1;
    }

    out << "Total roots provided (n): " << n << "\n";
    out << "Minimum roots required (k): " << k << "\n\n";

    vector<long long> roots;

    // Extract roots
    for (int i = 1; i <= n; i++) {
        string baseStr = j[to_string(i)]["base"];
        string valueStr = j[to_string(i)]["value"];
        int base = stoi(baseStr);
        long long root = baseToDecimal(valueStr, base);
        roots.push_back(root);
        out << "Root " << i << " (base " << base << "): " << valueStr 
            << " -> decimal = " << root << "\n";
    }

    // Example: polynomial using first two roots
    if (roots.size() >= 2) {
        long long x = roots[0];
        long long y = roots[1];
        long long c = x * y;

        out << "\nQuadratic polynomial from first two roots:\n";
        out << "P(z) = z^2 - (" << (x + y) << ")z + " << c << "\n";
        out << "Constant c = " << c << "\n";
    }

    out.close();
    cout << "✅ Output written to " << outputFile << endl;
    return 0;
}
