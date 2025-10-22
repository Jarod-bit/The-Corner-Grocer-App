/*
 * Corner Grocer – Frequency Analyzer
 * Jarod Jecas
 * 10/22/2025
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include "ItemRec.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

static const char* INPUT_FILE = "CS210_Project_Three_Input_File.txt";
static const char* BACKUP_FILE = "frequency.dat";

// Convert a string to lower-case 
string ToLower(const string& s) {
    string out = s;
    for (size_t i = 0; i < out.size(); ++i) {
        out[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(out[i])));
    }
    return out;
}

// Find index of item by lower-case name; return -1 if not found
int FindIndexByLower(const vector<ItemRec>& items, const string& lowerName) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].Lower() == lowerName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Read the input file and build frequency list in a vector
bool LoadFrequencies(vector<ItemRec>& outItems) {
    std::ifstream in(INPUT_FILE);
    if (!in) {
        return false;
    }

    outItems.clear();
    string word;

    while (in >> word) {
        string lower = ToLower(word);

        // Look for an existing record
        int idx = FindIndexByLower(outItems, lower);
        if (idx >= 0) {
            // Found -> just bump count
            outItems[static_cast<size_t>(idx)].AddOne();
        }
        else {
            // New item -> create record with cached lower-case
            ItemRec rec(word, 1);
            rec.SetLower(lower);
            outItems.push_back(rec);
        }
    }

    return true;
}

// Write frequency.dat (backup) from the vector
void WriteBackup(const vector<ItemRec>& items) {
    std::ofstream out(BACKUP_FILE);
    if (!out) {
        // Silent failure is fine for backup; keep app usable
        return;
    }

    for (size_t i = 0; i < items.size(); ++i) {
        out << items[i].Name() << " " << items[i].Count() << "\n";
    }
}

// Allocate a dynamic array copy (demonstrates pointers/new[]/delete[])
ItemRec* CopyToHeap(const vector<ItemRec>& src, int& outSize) {
    outSize = static_cast<int>(src.size());
    if (outSize == 0) {
        return nullptr;
    }

    ItemRec* heapArray = new ItemRec[outSize];
    for (int i = 0; i < outSize; ++i) {
        heapArray[i] = src[static_cast<size_t>(i)];
    }
    return heapArray;
}

// Print menu
void PrintMenu() {
    cout << "=== Corner Grocer ===\n";
    cout << "1 - Search for item\n";
    cout << "2 - Show all items\n";
    cout << "3 - Show histogram\n";
    cout << "4 - Exit\n";
    cout << "Choice: ";
}

// Show all items: "Name count"
void ShowAll(const ItemRec* data, int n) {
    if (data == nullptr || n <= 0) {
        cout << "(no data)\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        cout << data[i].Name() << " " << data[i].Count() << "\n";
    }
}

// Show histogram with asterisks
void ShowHistogram(const ItemRec* data, int n) {
    if (data == nullptr || n <= 0) {
        cout << "(no data)\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        cout << data[i].Name() << " ";
        for (int k = 0; k < data[i].Count(); ++k) {
            cout << "*";
        }
        cout << "\n";
    }
}

// Return the count for a specific item name 
int CountFor(const ItemRec* data, int n, const string& query) {
    if (data == nullptr || n <= 0) {
        return 0;
    }

    string lower = ToLower(query);
    for (int i = 0; i < n; ++i) {
        if (data[i].Lower() == lower) {
            return data[i].Count();
        }
    }
    return 0;
}

int main() {
    // Step 1: Build frequencies from the input file
    vector<ItemRec> items;

    if (!LoadFrequencies(items)) {
        cout << "Error: could not open \"" << INPUT_FILE << "\".\n";
        return 1;
    }

    // Write backup file at startup 
    WriteBackup(items);

    // Demonstrate pointers by copying to a dynamic array
    int heapCount = 0;
    ItemRec* heapItems = CopyToHeap(items, heapCount);

    // Menu loop (no while(true))
    int choice = 0;
    while (choice != 4) {
        PrintMenu();
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid entry.\n";
            continue;
        }

        if (choice == 1) {
            // Search for a single item
            cout << "Enter item: ";
            string name;
            cin >> name;
            int c = CountFor(heapItems, heapCount, name);
            cout << name << " " << c << "\n";
        }
        else if (choice == 2) {
            // Show all item counts
            ShowAll(heapItems, heapCount);
        }
        else if (choice == 3) {
            // Show histogram
            ShowHistogram(heapItems, heapCount);
        }
        else if (choice == 4) {
            // Exit
            cout << "Goodbye.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    // Clean up dynamic memory (pointer use)
    delete[] heapItems;
    heapItems = nullptr;

    return 0;
}