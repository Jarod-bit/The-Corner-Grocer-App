#pragma once
#ifndef ITEMREC_H
#define ITEMREC_H

#include <string>

class ItemRec {
private:
    std::string name_;      // Original item name 
    std::string lower_;     // Lower-case name for comparisons
    int count_;             // Quantity seen in the input

public:
    // Build an item record with name and an optional starting count
    ItemRec(const std::string& name = "", int count = 0);

    // Increase the quantity by one
    void AddOne();

    // Name accessors (original + lower-case)
    const std::string& Name()  const;
    const std::string& Lower() const;

    // Count accessor
    int Count() const;

    // Set lower-case cache (kept public so caller can normalize once)
    void SetLower(const std::string& lowerName);
};

#endif