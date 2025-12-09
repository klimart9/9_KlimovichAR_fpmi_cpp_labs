#include <iostream>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <cstdint>

class Vector {
private:
    size_t size_ = 0;
    int* data_ = nullptr;
    size_t capacity_ = 0;

    void Reallocate(size_t new_capacity) {
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Vector() : size_(0), data_(nullptr), capacity_(0) {
    }

    Vector(size_t n) : size_(n), capacity_(n), data_(new int[n]) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }

    Vector(std::initializer_list<int> list)
        : size_(list.size()), capacity_(list.size()), data_(new int[list.size()]) {
        size_t i = 0;
        for (int item : list) {
            data_[i] = item;
            ++i;
        }
    }

    size_t Size() const {
        return size_;
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), data_(nullptr) {
        if (capacity_ > 0) {
            data_ = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    size_t Capacity() const {
        return capacity_;
    }

    Vector& operator=(const Vector& other) {
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

    void PushBack(int elem) {
        if (size_ >= capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            Reallocate(new_capacity);
        }
        data_[size_] = elem;
        ++size_;
    }

    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }

    const int& operator[](size_t index) const {
        return data_[index];
    }

    int& operator[](size_t index) {
        return data_[index];
    }

    ~Vector() {
        delete[] data_;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            Reallocate(new_capacity);
        }
    }

    void Swap(Vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};

std::ostream& operator<<(std::ostream& out, const Vector& vec) {
    out << "[";
    for (size_t i = 0; i < vec.Size(); i++) {
        if (i == vec.Size() - 1) {
            out << vec[i];
        } else {
            out << vec[i] << " ";
        }
    }
    out << ']';
    return out;
}

int main() {
    Vector s(10);
    Vector copy(s);
    Vector p{1, 2, 3, 4, 5, 6};
    p[2] = 8;
    p.PushBack(10);
    p.PushBack(999);
    std::cout << p;
    p.Reserve(4);
    std::cout << p.Capacity();
}