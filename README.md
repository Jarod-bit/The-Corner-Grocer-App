"The-Corner-Grocer-App" 
**Author:** Jarod Jecas  
**Course:** CS-210 Programming Languages  
**Date:** 10/22/2025 

---

##  Overview
The Corner Grocer App is a C++ program designed for ChadaTech to help a local grocery store analyze customer purchase data. It reads a text file containing a list of purchased items and determines how often each item appears. This data helps the store optimize product placement and restocking strategies.

The program demonstrates **object-oriented programming**, **file handling**, and **pointer usage** while following modern C++ standards and code guidelines.

---

##  Features
- Reads purchase data from `CS210_Project_Three_Input_File.txt`
- Automatically generates a backup file named `frequency.dat` at startup
- Displays:
  1. Frequency of a specific item
  2. A full list of all item counts
  3. A text-based histogram of item frequencies
- Uses a dynamic array (via pointers) for memory management
- Implements encapsulation through the `ItemRec` class (separate `.h` and `.cpp` files)
- Includes input validation and error handling for invalid or missing data

---

##  Class Design
### `ItemRec`
Encapsulates grocery item data:

**Private members:**
- `name_` — Original item name  
- `lower_` — Lowercase version for case-insensitive comparison  
- `count_` — Quantity of times the item appears  

**Public methods:**
- `AddOne()` — Increases the item’s count  
- `Name()` / `Lower()` — Return the original or lowercase item name  
- `Count()` — Returns the current quantity  
- `SetLower()` — Caches the lowercase name for comparisons  

This structure supports **data encapsulation**, **reusability**, and **clean separation** between data and logic.

---

##  Concepts Demonstrated
- **Object-Oriented Design:** Class encapsulation, private data members, and clear interfaces  
- **Pointers & Dynamic Memory:** Demonstrates `new[]` and `delete[]` usage safely  
- **File I/O:** Reads data from an input file and writes a backup file automatically  
- **Controlled Loops:** Replaces `while(true)` with `while(choice != 4)` for clarity  
- **Inline Comments:** Concise explanations for each section of code  
- **Error Handling:** Protects against missing files and invalid input  

---
## Example Output
=== Corner Grocer ===
1 - Search for item
2 - Show all items
3 - Show histogram
4 - Exit
Choice: 1
Enter item: Peas
Peas 8

## Example Output
=== Corner Grocer ===
1 - Search for item
2 - Show all items
3 - Show histogram
4 - Exit
Choice: 2
Peas 8
Potatoes 5
Broccoli 7
...

## Example Output
=== Corner Grocer ===
1 - Search for item
2 - Show all items
3 - Show histogram
4 - Exit
Choice: 3
Peas ********
Broccoli *******
Potatoes *****
---
## Reflection

During the development of the Corner Grocer Frequency Analyzer, I gained a deeper understanding of how object-oriented programming and file handling can be combined to solve real-world problems. I designed a custom class to store and manage item data and implemented pointers to dynamically handle memory allocation on the heap. This helped me better understand how data can be accessed and organized in C++. Throughout the project, I focused on writing clear, readable code by using descriptive variable names and simple inline comments to explain each section’s purpose. I also ensured the logic stayed within the scope of what has been covered in class, using loops, conditionals, and basic file I/O instead of advanced libraries.
One of the biggest challenges was managing and displaying item data efficiently without relying on STL containers, but this helped strengthen my understanding of arrays and pointer operations. Overall, this project improved my ability to write structured, maintainable C++ code and gave me hands-on experience using object-oriented design and dynamic memory management in a practical application.

## README file completed by Jarod Jecas for CS-210 Project Three.
