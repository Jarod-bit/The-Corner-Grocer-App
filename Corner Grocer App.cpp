/*
 * Project: Corner Grocer 
 * Author:  Jarod Jecas
 * Date:    10/14/2025
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>   // for tolower()
using namespace std;

// Struct definition for each grocery item
struct Item {
    string name;  // Original item name as read from file
    string key;   // Lowercase version for comparisons
    int count;    // Number of times the item appears
};


// Converts a string to lowercase for case-insensitive matching
string ToLower(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = static_cast<char>(tolower(static_cast<unsigned char>(result[i])));
    }
    return result;
}

// Removes spaces at the start and end of a string
string Trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }
    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }
    return s.substr(start, end - start);
}

// Reads all items from file and stores their frequencies in a vector
bool LoadFrequencies(const string& filename, vector<Item>& outList) {
    ifstream inFile(filename.c_str());
    if (!inFile.is_open()) {
        return false;  // File not found or could not open
    }

    outList.clear();
    string line;

    while (getline(inFile, line)) {
        string raw = Trim(line);
        if (raw.empty()) continue;

        string key = ToLower(raw);
        int found = -1;

        // Check if item already exists in vector
        for (size_t i = 0; i < outList.size(); ++i) {
            if (outList[i].key == key) {
                found = static_cast<int>(i);
                break;
            }
        }

        // If item not found, create a new record
        if (found == -1) {
            Item temp;
            temp.name = raw;
            temp.key = key;
            temp.count = 1;
            outList.push_back(temp);
        }
        else {
            outList[found].count += 1; // Increment existing count
        }
    }

    inFile.close();
    return true;
}

// Creates a dynamic array (on the heap) from a vector
Item* BuildArrayFromVector(const vector<Item>& v, int& outSize) {
    outSize = static_cast<int>(v.size());

    if (outSize == 0) return nullptr;

    Item* arr = new Item[outSize];  
    for (int i = 0; i < outSize; ++i) {
        arr[i] = v[static_cast<size_t>(i)];
    }

    return arr; 
}

// Finds an item by its lowercase key using a pointer
Item* FindByKey(Item* arr, int size, const string& key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i].key == key) {
            return &arr[i];  
        }
    }
    return nullptr; // Return nullptr if item not found
}

// Prints every item and its count
void PrintAll(Item* arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i].name << " " << arr[i].count << "\n";
    }
}

// Prints a histogram using asterisks
void PrintHistogram(Item* arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i].name << " ";
        for (int j = 0; j < arr[i].count; ++j) {
            cout << "*";
        }
        cout << "\n";
    }
}

// Gets the count of a specific item
int GetCount(Item* arr, int size, const string& query) {
    string key = ToLower(Trim(query));
    Item* found = FindByKey(arr, size, key); 
    return (found == nullptr) ? 0 : found->count;
}

// Main program � menu-driven interface
int main() {
    const string inputFile = "CS210_Project_Three_Input_File.txt";
    vector<Item> tempData;

    // Load file data into vector first
    if (!LoadFrequencies(inputFile, tempData)) {
        cout << "Error: Could not open input file: " << inputFile << "\n";
        return 1;
    }

    int size = 0;
    Item* items = BuildArrayFromVector(tempData, size); 

    // Display user menu
    while (true) {
        cout << "\n================ Corner Grocer =================\n";
        cout << "1 - Search for a specific item frequency\n";
        cout << "2 - Display all items with their counts\n";
        cout << "3 - Display histogram\n";
        cout << "4 - Exit program\n";
        cout << "Choose an option: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter 1-4.\n";
            continue;
        }

        if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }
        else if (choice == 1) {
            cout << "Enter item name: ";
            string itemName;
            cin.ignore(1000, '\n');
            getline(cin, itemName);
            int count = GetCount(items, size, itemName);
            cout << itemName << " " << count << "\n";
        }
        else if (choice == 2) {
            PrintAll(items, size);
        }
        else if (choice == 3) {
            PrintHistogram(items, size);
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    // Release memory before exiting
    delete[] items; // Frees memory used by dynamic array
    items = nullptr; // Good practice to reset pointer

    return 0;
}
