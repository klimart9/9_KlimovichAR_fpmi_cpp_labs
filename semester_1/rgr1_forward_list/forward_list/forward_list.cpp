#include "forward_list.h"

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
