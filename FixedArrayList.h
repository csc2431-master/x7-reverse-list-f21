//
// Interface Definition for the template version of the FixedArrayList Class
// Author: Max Benson
// Date: 08/07/2021
//

#ifndef FIXEDARRAYLIST_H
#define FIXEDARRAYLIST_H

#include <iostream>
using std::ostream;

template <typename ItemType>
class FixedArrayList  {
public:
    FixedArrayList(size_t capacity);

    // Rule of three
    ~FixedArrayList();
    FixedArrayList(const FixedArrayList&);
    const FixedArrayList& operator=(const FixedArrayList&);

    // Other methods
    bool Get(size_t position, ItemType& item) const;
    int Find(const ItemType& item, size_t start = 0) const;
    bool Insert(size_t position, const ItemType& item);
    bool Replace(size_t position, const ItemType& item);
    bool Swap(size_t position1, size_t position2);
    bool Remove(size_t position, ItemType& item);
    void Clear();

    size_t Size() const;

    bool CheckConsistency() const;

    // Stream output
    friend ostream& operator<<(ostream& os, const FixedArrayList& list) {
        os << "[";
        for (size_t position = 0; position < list._size; position ++) {
            if (position > 0) {
                os << ", ";
            }
            os << list._array[position];
        }
        return os << "]";
    }

private:
    ItemType* _array;
    size_t _size;
    size_t _capacity;
};

/**
 * Constructor
 * Creates an empty list.
 */
template <typename ItemType>
FixedArrayList<ItemType>::FixedArrayList(size_t capacity) {
    _array = new ItemType[capacity];
    _size = 0;
    _capacity = capacity;
}

/**
 * Destructor
 * Frees the dynamic memory allocated for the list
 */
template <typename ItemType>
FixedArrayList<ItemType>::~FixedArrayList() {
    delete[] _array;
}

/**
 * Copy Constructor
 * Creates a deep copy of the list.
 * The running time of the whole method is O(N) time where N is the
 * length of the list
 * @param other the list to be copied
 */
template <typename ItemType>
FixedArrayList<ItemType>::FixedArrayList(const FixedArrayList& other) {
    _array = new ItemType[other._capacity];
    for (size_t i = 0; i < other._size; i ++) {
        _array[i] = other._array[i];
    }
    _size = other._size;
    _capacity = other._capacity;
}

/**
 * Copy assignment operator
 * Enables deep copy assignment using the operator = overload.
 * Uses the copy constructor to copy the rhs.  Then swaps internals of
 * the copy with this.  By doing it this way, the old contents
 * of this will be automatically freed when the method finishes.
 * The running time of this method is the same as the copy
 * constructor , i.e. O(N)
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
template <typename ItemType>
const FixedArrayList<ItemType>& FixedArrayList<ItemType>::operator=(const FixedArrayList& rhs) {
    if (this != &rhs) {
        FixedArrayList copy(rhs);
        ItemType* swapArray;
        size_t swapSize;
        size_t swapCapacity;

        swapArray = _array;
        swapSize = _size;
        swapCapacity = _capacity;
        _array = copy._array;
        _capacity = copy._capacity;
        _size = copy._size;
        copy._array = swapArray;
        copy._size = swapSize;
        copy._capacity = swapCapacity;
    }
    return *this;
}

/**
 * Get  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the item found at position
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::Get(size_t position, ItemType& item) const {
    if (position < _size) {
        item = _array[position];
        return true;
    }
    return false;
}

/**
 * Searches for the position of the first matching item in the list starting
 * at position "start".  The method performs a linear search for the item.
 * If the element is found it returns the position, if it is not found it
 * returns -1.
 * The running time of this method depends on where the search starts
 * and where the item is found (if it is found)
 * @param item the object that the client is searching for.
 * @param start position at which to start the search
 * @return the position of the element if found, -1 otherwise.
 */
template <typename ItemType>
int FixedArrayList<ItemType>::Find(const ItemType& item, size_t start)  const {
    for (size_t i = start; i < _size; i++) {
        if (_array[i] == item) {
            return i;
        }
    }
    return -1;
}

/**
 * Inserts an element into a given position so long as the position is valid
 * and the list is not filled to capacity.
 * THe running time of inserting at the start is O(N), it's O(1) if you are
 * inserting at the end.
 * @param item what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise.
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::Insert(size_t position, const ItemType& item) {
    if (position > _size || _size == _capacity) {
        return false;
    }
    else {
        // Shift out elements to make room for insertion
        for (size_t i = _size; i > position; i --) {
            _array[i] = _array[i-1];
        }
        // Insert the element
        _array[position] = item;
        _size ++;
        return true;
    }
}

/**
 * Replace  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the new item to insert in the old one's place
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::Replace(size_t position, const ItemType& item) {
    if (position < _size) {
        _array[position] = item;
        return true;
    }
    return false;
}


/**
 * Swap elements in specified positions
 * This method runs in O(1) time.
 * @param position1 the position of the first element
 * @param position2 the position of the second element
 * @return true if valid positions were given, false otherwise
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::Swap(size_t position1, size_t position2) {
    if (position1 < _size && position2 < _size) {
        ItemType tmp;

        tmp = _array[position1];
        _array[position1] = _array[position2];
        _array[position2] = tmp;
        return true;
    }
    return false;
}

/**
 * Removes the item at position, so long as the position is valid. The item previously
 * stored in the list is returned in the supplied parameter.
 * THe running time of removing the first element is  O(N), it's O(1) if you are
 * removing the last element.
 * @param position the position of the element to be removed.
 * @param item the item previously stored in the list
 * @return true if node could be deleted, false if position at end of list or invalid,
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::Remove(size_t position, ItemType& item) {
    if (position >= _size) {
        return false;
    }
    else {
        item = _array[position];

        // Close up the gap
        for (size_t i = position; i < _size-1; i ++) {
            _array[i] = _array[i+1];
        }
        _size--;
        return true;
    }
}

/**
 * Clear the list
 * and then resetting _head to nullptr.
 * This method runs in O(1) time
 * There is no need to free the string values
 * that will occur when the class destructs
 */
template <typename ItemType>
void FixedArrayList<ItemType>::Clear() {
    _size = 0;
}

/**
 * Returns the current number of items in list
 * This method runs in O(1) time
 * @return current number of itesm in list
 */
template <typename ItemType>
size_t FixedArrayList<ItemType>::Size() const {
    return _size;
}

/**
 * Checks if list data structure appears to be consistent
 * @return true if list consistent, false otherwise
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::CheckConsistency() const {
    return _size <= _capacity;
}

#endif //FIXEDARRAYLIST_H
