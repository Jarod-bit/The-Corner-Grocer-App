/*
 * Project: Corner Grocer
 * Author:  Jarod Jecas
 * Date:    10/14/2025
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

/* Class stores item name and count */
class ItemRec {
private:
    string name_;
    string key_;
    int qty_;

public:
    ItemRec() : name_(""), key_(""), qty_(0) {}
    ItemRec(const string& n, const string& k, int q) : name_(n), key_(k), qty_(q) {}

    const string& Name() const { return name_; }
    const string& Key()  const { return key_; }
    int Quantity() const { return qty_; }

    void SetName(const string& n) { name_ = n; }
    void SetKey(const string& k) { key_ = k; }
    void SetQty(int q) { qty_ = q; }
    void AddOne() { ++qty_; }
};

/* Converts string to lowercase */
static string to_lower(const string& s) {
    string out = s;
    for (size_t i = 0; i < out.size(); ++i) {
        out[i] = static_cast<char>(tolower(static_cast<unsigned char>(out[i])));
    }
    return out;
}

/* Trims spaces from both ends */
static string trim(const string& s) {
    size_t a = 0, b = s.size();
    while (a < b && isspace(static_cast<unsigned char>(s[a]))) ++a;
    while (b > a && isspace(static_cast<unsigned char>(s[b - 1]))) --b;
    return s.substr(a, b - a);
}

/* Reads file and builds item list */
static bool read_file(const string& file, vector<ItemRec>& out) {
    ifstream fin(file.c_str());
    if (!fin.is_open()) return false;

    out.clear();
    string line;
    while (getline(fin, line)) {
        string name = trim(line);
        if (name.empty()) continue;
        string key = to_lower(name);

        int found = -1;
        for (size_t i = 0; i < out.size(); ++i) {
            if (out[i].Key() == key) { found = static_cast<int>(i); break; }
        }

        if (found == -1) {
            out.push_back(ItemRec(name, key, 1));
        }
        else {
            out[found].AddOne();
        }
    }

    fin.close();
    return true;
}

/* Writes backup file */
static void write_backup(const vector<ItemRec>& list) {
    ofstream fout("frequency.dat");
    if (!fout.is_open()) {
        cout << "Could not create frequency.dat\n";
        return;
    }
    for (size_t i = 0; i < list.size(); ++i) {
        fout << list[i].Name() << " " << list[i].Quantity() << "\n";
    }
    fout.close();
}

/* Makes heap array  */
static ItemRec* make_array(const vector<ItemRec>& v, int& count) {
    count = static_cast<int>(v.size());
    if (count == 0) return nullptr;

    ItemRec* arr = new ItemRec[count];
    for (int i = 0; i < count; ++i) arr[i] = v[i];
    return arr;
}

/* Finds item by key  */
static ItemRec* find_item(ItemRec* arr, int n, const string& key) {
    for (int i = 0; i < n; ++i) {
        if (arr[i].Key() == key) return &arr[i];
    }
    return nullptr;
}

/* Shows all items */
static void show_list(ItemRec* arr, int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i].Name() << " " << arr[i].Quantity() << "\n";
}

/* Shows histogram */
static void show_hist(ItemRec* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i].Name() << " ";
        for (int s = 0; s < arr[i].Quantity(); ++s) cout << "*";
        cout << "\n";
    }
}

/* Gets count for a specific item  */
static int get_count(ItemRec* arr, int n, const string& name) {
    string key = to_lower(trim(name));
    ItemRec* found = find_item(arr, n, key);
    return (found == nullptr) ? 0 : found->Quantity();
}

/* Handles each menu option */
static bool handle_menu(const string& file, int choice) {
    vector<ItemRec> list;
    if (!read_file(file, list)) {
        cout << "Error reading file.\n";
        return false;
    }

    write_backup(list);  // always create backup

    int count = 0;
    ItemRec* arr = make_array(list, count);

    if (choice == 1) {
        cout << "Enter item: ";
        string name;
        cin.ignore(1000, '\n');
        getline(cin, name);
        cout << name << " " << get_count(arr, count, name) << "\n";
    }
    else if (choice == 2) {
        show_list(arr, count);
    }
    else if (choice == 3) {
        show_hist(arr, count);
    }

    delete[] arr;
    arr = nullptr;
    return true;
}

/* Main program loop */
int main() {
    const string INPUT_FILE = "CS210_Project_Three_Input_File.txt";

    vector<ItemRec> init;
    if (read_file(INPUT_FILE, init)) write_backup(init);

    while (true) {
        cout << "\n=== Corner Grocer ===\n";
        cout << "1 - Search for item\n";
        cout << "2 - Show all items\n";
        cout << "3 - Show histogram\n";
        cout << "4 - Exit\n";
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }

        if (choice >= 1 && choice <= 3) {
            handle_menu(INPUT_FILE, choice);
        }
        else {
            cout << "Enter 1–4.\n";
        }
    }

    return 0;
}