// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONS_H
#define CONS_H
#include <memory>

// Put this in the declarations for a class to be uncopyable.
#define DISALLOW_COPY(TypeName) \
TypeName(const TypeName&) = delete
// Put this in the declarations for a class to be unassignable.
#define DISALLOW_ASSIGN(TypeName) TypeName& operator=(const TypeName&) = delete
// Put this in the declarations for a class to be uncopyable and unassignable.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
DISALLOW_COPY(TypeName);                 \
DISALLOW_ASSIGN(TypeName)

// Forward declarations.
template <typename T>
class Cell;
template <typename T>
class ListIterator;
// List represents a (possibly null) pointer to a cons cell.
template <typename T>
using List = std::shared_ptr<const Cell<T>>;
// Cons extends a cons list by prepending a new value to the front.
template <typename T>
List<T> Cons(const T& head, List<T> tail) {
    return std::make_shared<Cell<T>>(head, std::move(tail));
}
// Cell represents an individual "cons cell" within a cons list.
template <typename T>
class Cell {
public:
    Cell(const T& head, List<T> tail) : head_(head), tail_(std::move(tail)) {}
    // Head returns this cell's head element.
    const T& head() const { return head_; }
    // Tail returns this cell's tail element.
    const List<T>& tail() const { return tail_; }
private:
    T head_;
    List<T> tail_;
    DISALLOW_COPY_AND_ASSIGN(Cell);
};
// Begin returns a list iterator pointing to the first element of the
// cons list. It's provided to support range-based for loops.
template <typename T>
ListIterator<T> begin(const List<T>& list) {
    return ListIterator<T>(list);
}
// End returns a list iterator pointing to the "past-the-end" element
// of the cons list (i.e., nil). It's provided to support range-based
// for loops.
template <typename T>
ListIterator<T> end(const List<T>& list) {
    return ListIterator<T>();
}
// ListIterator provides C++ forward iterator semantics for traversing
// a cons list.
template <typename T>
class ListIterator {
public:
    ListIterator() : list_() {}
    explicit ListIterator(const List<T>& list) : list_(list) {}
    const T& operator*() const { return list_->head(); }
    ListIterator& operator++() {
        list_ = list_->tail();
        return *this;
    }
    friend bool operator==(const ListIterator& lhs, const ListIterator& rhs) {
        return lhs.list_ == rhs.list_;
    }
private:
    List<T> list_;
};
template <typename T>
bool operator!=(const ListIterator<T>& lhs, const ListIterator<T>& rhs) {
    return !(lhs == rhs);
}


#endif
