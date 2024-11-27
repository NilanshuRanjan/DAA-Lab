#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Linear search function
int linear_search(vector<int> arr, int key) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == key) {
            return i;  // Return the index if found
        }
    }
    return -1;  // Return -1 if the element is not found
}

// Binary search function
int binary_search(vector<int> arr, int key) {
    int left = 0, right = arr.size() - 1;
    
    // Sorting only once before binary search
    sort(arr.begin(), arr.end());
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == key) {
            return mid;  // Return the index if found
        }
        
        if (arr[mid] < key) {
            left = mid + 1;  // Search in the right half
        } else {
            right = mid - 1;  // Search in the left half
        }
    }
    return -1;  // Return -1 if the element is not found
}

int main() {
    int n;
    cout << "Number of elements in arr: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];  // Read the elements into the array
    }
    
    int key;
    cout << "Enter the key to search: ";
    cin >> key;
    
    // Linear search
    int linearResult = linear_search(arr, key);
    if (linearResult != -1) {
        cout << "Number found at index (Linear Search): " << linearResult << endl;
    } else {
        cout << "Number not found (Linear Search)" << endl;
    }

    // Binary search (make sure the array is sorted before calling binary_search)
    int binaryResult = binary_search(arr, key);
    i
