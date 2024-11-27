#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
using namespace std;

// Function to generate a random name
string Generate_Random_Name() {
    vector<string> firstNames = {"John", "Jane", "Alex", "Emily", "Chris", 
                                 "Katie", "Michael", "Sarah", "David", "Laura"};
    vector<string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones", 
                                "Miller", "Davis", "Garcia", "Wilson", "Martinez"};
    
    string firstName = firstNames[rand() % firstNames.size()];
    string lastName = lastNames[rand() % lastNames.size()];
    
    return firstName + " " + lastName;
}

// Function to generate a random salary
int Generate_Random_Salary() {
    return rand() % 90001 + 10000; // Random salary between 10,000 and 100,000
}

// Function to find both the max and min value in a vector
pair<int, int> find_Max_Min(vector<double>& a, int lo, int hi) {
    if (lo > hi) return {-1, -1};  // Error case if lo > hi
    
    if (lo == hi) return {a[lo], a[lo]};  // Base case when there's only one element

    int mid = (lo + hi) / 2;
    pair<int, int> leftMaxMin = find_Max_Min(a, lo, mid);
    pair<int, int> rightMaxMin = find_Max_Min(a, mid + 1, hi);
    
    int leftMax = leftMaxMin.first;
    int leftMin = leftMaxMin.second;
    int rightMax = rightMaxMin.first;
    int rightMin = rightMaxMin.second;
    
    // Return max of maxs and min of mins
    return {max(leftMax, rightMax), min(leftMin, rightMin)};
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    // Create and open the input and output files
    ofstream file("5input.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Write the header
    file << "Name,Salary\n";
    
    // Generate and write 2000 records to the CSV
    for (int i = 0; i < 2000; ++i) {
        string name = Generate_Random_Name();
        int salary = Generate_Random_Salary();
        file << name << "," << salary << "\n";
    }

    file.close();
    cout << "CSV file created successfully!" << endl;

    // Open input and output CSV files for processing
    ifstream inputFile("1input.csv");
    ofstream outputFile("1.csv");
    vector<double> v;

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;
    // Write the header for the output file
    outputFile << "Name,Salary,Tax,Home Rent,Bonus\n";

    // Skip the header line in the input file
    getline(inputFile, line);

    // Process each line from the input file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name, salaryStr;
        getline(ss, name, ',');
        getline(ss, salaryStr, ',');
        
        double salary = stod(salaryStr);
        v.push_back(salary);

        double tax = 0.10 * salary;
        double homeRent = 0.20 * salary;
        double bonus = 0.15 * salary;

        // Write the results to the output file
        outputFile << name << "," << salary << "," << tax << "," << homeRent << "," << bonus << "\n";
    }

    inputFile.close();
    outputFile.close();
    cout << "Calculations completed and output saved to '1.csv'." << endl;

    // Find min and max salaries
    pair<int, int> maxMin = find_Max_Min(v, 0, 2000);
    
    if (maxMin.second < 0) {
        cout << "Salary can't be negative" << endl;
    } else {
        cout << "Min Salary -> " << maxMin.second << endl;
        cout << "Max Salary -> " << maxMin.first << endl;
    }

    return 0;
}
