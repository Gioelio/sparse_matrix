#include "test_class.h"
#include <algorithm> //swap


test_class::test_class(): value(), ptr(nullptr) {}

test_class::test_class(const int &value): value(value), ptr(nullptr) {}

test_class::test_class(const int &value, const int &value_ptr): value(value), ptr(nullptr) {
    ptr = new int(value_ptr);
}

test_class::test_class(const test_class &other): value(other.value), ptr(nullptr) {
    if(other.ptr != nullptr)
        ptr = new int(*other.ptr);
}

test_class& test_class::operator= (const test_class &other){
    test_class tmp(other);
    std::swap(tmp.value, this->value);
    std::swap(tmp.ptr, this->ptr);
    return *this;
}

test_class::~test_class() {
    delete ptr;
    ptr = nullptr;
}

bool test_class::operator==(const test_class &other) const { return other.value == value && other.ptr == ptr; }

int test_class::get_value() const {
    return value;
}

int test_class::get_value_ptr() const {
    return *ptr;
}