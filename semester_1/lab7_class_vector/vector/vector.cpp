#include "vector.h"
#include <algorithm>

void Vector::Reallocate(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

Vector::Vector() : size_(0), data_(nullptr), capacity_(0) {
}

Vector::Vector(size_t n) : size_(n), capacity_(n), data_(new int[n]) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<int> list)
    : size_(list.size()), capacity_(list.size()), data_(new int[list.size()]) {
    size_t i = 0;
    for (int item : list) {
        data_[i] = item;
        ++i;
    }
}

size_t Vector::Size() const {
    return size_;
}

size_t Vector::Capacity() const {
    return capacity_;
}

Vector::Vector(const Vector& other)
    : size_(other.size_), capacity_(other.capacity_), data_(nullptr) {
    if (capacity_ > 0) {
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    if (capacity_ > 0) {
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    } else {
        data_ = nullptr;
    }

    return *this;
}

void Vector::PushBack(int elem) {
    if (size_ >= capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reallocate(new_capacity);
    }
    data_[size_] = elem;
    ++size_;
}

void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

void Vector::Clear() {
    size_ = 0;
}

const int& Vector::operator[](size_t index) const {
    return data_[index];
}

int& Vector::operator[](size_t index) {
    return data_[index];
}

Vector::~Vector() {
    delete[] data_;
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        Reallocate(new_capacity);
    }
}

void Vector::Swap(Vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::ostream& operator<<(std::ostream& out, const Vector& vec) {
    out << "[";
    for (size_t i = 0; i < vec.Size(); i++) {
        if (i == vec.Size() - 1) {
            out << vec[i];
        } else {
            out << vec[i] << ", ";
        }
    }
    out << ']';
    return out;
}
