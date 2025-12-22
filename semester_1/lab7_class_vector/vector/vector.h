#pragma once
#include <iostream>
#include <initializer_list>
#include <cstddef>

class Vector {
private:
    size_t size_ = 0;
    int* data_ = nullptr;
    size_t capacity_ = 0;

    

public:
    Vector();

    Vector(size_t n);

    Vector(std::initializer_list<int> list);

    Vector(const Vector& other);

    Vector& operator=(const Vector& other);

    ~Vector();

    size_t Size() const;

    size_t Capacity() const;

    void Reallocate(size_t new_capacity);

    void PushBack(int elem);

    void PopBack();

    void Clear();

    void Reserve(size_t new_capacity);

    void Swap(Vector& other);

    const int& operator[](size_t index) const;

    int& operator[](size_t index);
};

std::ostream& operator<<(std::ostream& out, const Vector& vec);
