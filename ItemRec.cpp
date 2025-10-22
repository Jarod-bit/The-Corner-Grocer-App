#include "ItemRec.h"

// Build an item record with name and an optional starting count
ItemRec::ItemRec(const std::string& name, int count)
    : name_(name), lower_(name), count_(count) {
}

// Increase the quantity by one
void ItemRec::AddOne() {
    ++count_;
}

// Original (display) name
const std::string& ItemRec::Name() const {
    return name_;
}

// Lower-case version used for comparisons
const std::string& ItemRec::Lower() const {
    return lower_;
}

// Current quantity
int ItemRec::Count() const {
    return count_;
}

// Cache a precomputed lower-case name
void ItemRec::SetLower(const std::string& lowerName) {
    lower_ = lowerName;
}