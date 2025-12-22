#include "forward_list.h"
#include <stdexcept>

ForwardList::ForwardList(): head_(nullptr) {
}

ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr) {
    if (rhs.head_ == nullptr) {
        return; 
    }

    head_ = new Node(rhs.head_->value_);
    Node* current = head_;
    Node* rhsCurrent = rhs.head_->next_;

    while (rhsCurrent != nullptr) {
        current->next_ = new Node(rhsCurrent->value_);
        current = current->next_;
        rhsCurrent = rhsCurrent->next_;
    }
}
ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr) {
    if (count == 0) {
        return;
    }

    head_ = new Node(value);
    Node* current = head_;

    for (size_t i = 1; i < count; ++i) {
        current->next_ = new Node(value);
        current = current->next_;
    }
}
ForwardList::ForwardList(std::initializer_list<int32_t> list) : head_(nullptr) {
    if (list.size() == 0) {
        return;  
    }

    std::initializer_list<int32_t>::iterator it = list.begin();
    head_ = new Node(*it);
    Node* current = head_;
    ++it;

    for (std::initializer_list<int32_t>::iterator it = list.begin() + 1; it != list.end(); ++it) {
        current->next_ = new Node(*it);
        current = current->next_;
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }

    Clear();

    if (rhs.head_ == nullptr) {
        head_ = nullptr;
        return *this;
    }

    head_ = new Node(rhs.head_->value_);
    Node* current = head_;
    Node* rhsCurrent = rhs.head_->next_;

    while (rhsCurrent != nullptr) {
        current->next_ = new Node(rhsCurrent->value_);
        current = current->next_;
        rhsCurrent = rhsCurrent->next_;
    }

    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::PushFront(int32_t value) {
    Node* newNode = new Node(value);
    newNode->next_ = head_;
    head_ = newNode;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;
    }
    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
}

void ForwardList::Remove(int32_t value) {
    while (head_ != nullptr && head_->value_ == value) {
        PopFront();
    }

    Node* current = head_;
    while (current != nullptr && current->next_ != nullptr) {
        if (current->next_->value_ == value) {
            Node* temp = current->next_;
            current->next_ = temp->next_;
            delete temp;
        } else {
            current = current->next_;
        }
    }
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        PopFront();
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    while (current != nullptr) {
        out << current->value_;
        if (current->next_ != nullptr) {
            out << " ";
        }
        current = current->next_;
    }
}

int32_t ForwardList::Front() const {
    if (head_ == nullptr) {
        throw "ForwardList is empty";
    }
    return head_->value_;
}

size_t ForwardList::Size() const {
    size_t count = 0;
    Node* current = head_;
    while (current != nullptr) {
        ++count;
        current = current->next_;
    }
    return count;
}
