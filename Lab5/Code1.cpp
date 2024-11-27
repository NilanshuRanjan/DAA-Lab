#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>

using namespace std;

// Class to represent an item in the knapsack
class Item {
public:
    int weight;
    int value;
    int shelf_life;

    // Constructor
    Item(int value, int weight, int shelf_life) {
        if (weight <= 0) {
            throw invalid_argument("Invalid weight: " + to_string(weight) +
                                    ". Weight of an item cannot be zero or negative.");
        }
        if (value < 0) {
            throw invalid_argument("Invalid value: " + to_string(value) +
                                    ". Value of an item cannot be negative.");
        }
        if (shelf_life <= 0) {
            throw invalid_argument("Invalid shelf life: " + to_string(shelf_life) +
                                    ". Shelf life must be greater than zero.");
        }
        this->weight = weight;
        this->value = value;
        this->shelf_life = shelf_life;
    }

    // Utility function to calculate the value to weight ratio
    double value_weight_ratio() const {
        return static_cast<double>(value) / weight;
    }

    // Utility function to combine shelf life and value-weight ratio in comparison
    pair<double, int> priority() const {
        return { value_weight_ratio(), -shelf_life }; // Higher value-weight, lower shelf life prioritized
    }
};

// Function to implement the fractional knapsack problem
double fractional_knapsack(int capacity, vector<Item>& items) {
    if (capacity <= 0) {
        throw invalid_argument("Capacity of the knapsack must be greater than zero.");
    }
    if (items.empty()) {
        throw invalid_argument("Item list cannot be empty.");
    }

    // Sort items by priority: value-weight ratio (desc) and shelf life (asc)
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.priority() > b.priority();
    });

    double total_value = 0.0;  // Total value accumulated
    int current_weight = 0;    // Current weight of the knapsack

    for (const Item& item : items) {
        if (current_weight + item.weight <= capacity) {
            // Take the whole item
            current_weight += item.weight;
            total_value += item.value;
        } else {
            // Take fraction of the item
            int remaining_capacity = capacity - current_weight;
            double fraction = static_cast<double>(remaining_capacity) / item.weight;
            total_value += item.value * fraction;
            break;  // Knapsack is full
        }
    }
    return total_value;
}

// Test case runner with error handling
void run_test_case(const vector<Item>& items, int capacity) {
    try {
        // Print the items with their weights, values, and shelf lives
        cout << "\nItems (Weight, Value, Shelf Life):\n";
        for (size_t i = 0; i < items.size(); ++i) {
            cout << "Item " << i + 1 << ": Weight = " << items[i].weight
                 << ", Value = " << items[i].value
                 << ", Shelf Life = " << items[i].shelf_life << '\n';
        }

        // Calculate and print the total knapsack value
        double result = fractional_knapsack(capacity, const_cast<vector<Item>&>(items));

        cout << "Knapsack Value for " << items.size() << " items: " << result << "\n\n";
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << '\n';
    }
}

int main() {
    // Test cases
    vector<Item> items_1 = { Item(10, 60, 5), Item(20, 80, 10), Item(30, 100, 3) };
    run_test_case(items_1, 200);

    vector<Item> items_2 = { Item(5, 50, 1), Item(20, 90, 2), Item(15, 50, 4) };
    run_test_case(items_2, 200);

    vector<Item> items_3 = { Item(5, 30, 8), Item(10, 10, 6), Item(20, 100, 2), Item(15, 60, 5) };
    run_test_case(items_3, 200);

    // Negative Test Cases with proper error handling
    cout << "\nNegative Test Cases\n";

    // Empty item list
    vector<Item> items_6;
    run_test_case(items_6, 200); // Expected: Error for empty item list

    // Knapsack capacity is zero
    vector<Item> items_7 = { Item(5, 30, 3), Item(10, 50, 5) };
    run_test_case(items_7, 0); // Expected: Error for zero capacity

    // Item with zero weight
    try {
        vector<Item> items_8 = { Item(10, 0, 5) }; // Invalid item
        run_test_case(items_8, 200);
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << '\n'; // Expected: Error for zero weight
    }

    // Item with negative value
    try {
        vector<Item> items_9 = { Item(-10, 5, 5) }; // Invalid item
        run_test_case(items_9, 200);
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << '\n'; // Expected: Error for negative value
    }

    // Item with zero shelf life
    try {
        vector<Item> items_10 = { Item(10, 5, 0) }; // Invalid item
        run_test_case(items_10, 200);
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << '\n'; // Expected: Error for zero shelf life
    }

    return 0;
}
