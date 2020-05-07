/**
 * @Author: Brandon Wolenetz
 * @Date:   20-Apr-2020
 * @Project: TemplatedAlgorithms/Beta
 * @Filename: Vector.h
 * @Last modified by:   Brandon Wolenetz
 * @Copyright: Copyright � 2020 DigiPen (USA) Corporation.
 */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
////////////////////////////////////////////////////////////////////////////////

namespace Beta {
    namespace Data {

        class SubscriptError {
        public:
            SubscriptError(size_t Subscript) : subscript_(Subscript) {};
            size_t GetSubscript(void) const {
                return subscript_;
            }

        private:
            size_t subscript_;
        };

        template <typename T> class Vector {
        public:
            // Default constructor
            Vector(void);

            // Destructor
            ~Vector();

            // Adds a node to the back of the array. If there is
            // not enough room in the array, it will be grown to
            // handle more items.
            void push_back(T value);

            // Adds a node to the front of the array. If there is
            // not enough room in the array, it will be grown to
            // handle more items. All items to the right must be
            // shifted over one element to the right.
            void push_front(T value);

            // Subscript operators for const and non-const
            T operator[](size_t index) const;
            T& operator[](size_t index);

            // Deletes the underlying array and sets size_ to 0
            void Clear(void);

            // Return true if the vector is empty, otherwise, false
            bool Empty(void) const;

            // Returns the number of elements in the vector.
            int Size(void) const;

            // Returns the size of the underlying array
            unsigned Capacity(void) const;

            // The number of memory allocations that have occurred
            unsigned allocations(void) const;

            // Copy constructor
            Vector(const Vector& rhs);

            // Constructor to create a Vector from an array
            Vector(const T array[], size_t size);

            // Removes the last element. Does nothing if empty.
            void pop_back(void);

            // Removes the first element. Does nothing if empty.
            void pop_front(void);

            // Inserts a new node at the specified position. Now throws an
            // exception if the position is invalid. (Calls check_bounds
            // which is the function that is actually throwing.)
            void insert(T value, size_t position);

            // Removes an element at specified position
            void remove(size_t position);

            // Assignment operator
            Vector& operator=(const Vector& rhs);

            // Concatenates a vector onto the end of this vector.
            Vector& operator+=(const Vector& rhs);

            // Concatenates two Vectors.
            Vector operator+(const Vector& rhs) const;

            // Reverses the order of the elements (Linear time)
            void reverse(void);

            // Swaps the contents of other with this Vector (Constant time)
            void swapv(Vector& other);

            // Equality operator (Linear time)
            // Both vectors must be the same size.
            bool operator==(const Vector& rhs) const;

            // Reallocates an array to match the size of the number
            // of elements. If size == capacity, does nothing.
            void shrink_to_fit(void);

        private:
            T* array_;          // The dynamically allocated array
            unsigned size_;     // The number of elements in the array
            unsigned capacity_; // The allocated size of the array
            unsigned allocs_;   // Number of allocations (resizes)

            // Private methods...
            void check_bounds(size_t index) const;
            void grow(void);

            // Other private methods...
        };
    } // namespace Data
} // namespace Beta

#include <algorithm> // swap
#include <cstdlib>   // abort
#include <iostream>  // cout

namespace Beta {
    namespace Data {

        // Default constructor
        template <typename T>
        Vector<T>::Vector(void)
            : array_(nullptr), size_(0), capacity_(0), allocs_(0) {}

        // Destructor
        template <typename T> Vector<T>::~Vector() {
            if (array_ != nullptr) {
                delete[] array_;
                array_ = nullptr;
            }
        }

        // Copy constructor
        template <typename T>
        Vector<T>::Vector(const Vector<T>& other)
            : array_(nullptr), size_(0), capacity_(0), allocs_(0) {
            *this = other;
        }

        // Constructor to create a Vector from an array
        template <typename T>
        Vector<T>::Vector(const T array[], size_t size)
            : array_(nullptr), size_(0), capacity_(0), allocs_(0) {

            ++allocs_;
            array_ = new T[size];
            capacity_ = size;
            for (unsigned i = 0; i < size; ++i) {
                push_back(array[i]);
            }
        }

        // Adds a node to the back of the array. If there is
        // not enough room in the array, it will be grown to
        // handle more items.
        template <typename T> void Vector<T>::push_back(T value) {
            if (size_ == capacity_) {
                grow();
            }
            array_[size_] = value;
            ++size_;
        }

        // Adds a node to the front of the array. If there is
        // not enough room in the array, it will be grown to
        // handle more items. All items to the right will be
        // shifted over by one element to the right.
        template <typename T> void Vector<T>::push_front(T value) {
            if (size_ == capacity_) {
                grow();
            }
            // shift everything over 1
            memcpy(array_ + 1, array_, sizeof(T) * size_);
            array_[0] = value;
            ++size_;
        }

        // Removes the last element. Does nothing if empty.
        template <typename T> void Vector<T>::pop_back() {
            if (size_ == 0)
                return;
            --size_;
        }

        // Removes the first element. Does nothing if empty.
        template <typename T> void Vector<T>::pop_front() {
            if (size_ == 0)
                return;
            if (size_ == 1) {
                --size_;
                return;
            }

            --size_;
            memcpy(array_, array_ + 1, sizeof(T) * size_);
        }

        // Inserts a new node at the specified position. throws a subscript error
        // if the position is invalid.
        template <typename T> void Vector<T>::insert(T value, size_t position) {
            check_bounds(position);
            if (size_ == capacity_) {
                grow();
            }

            memcpy(array_ + position + 1, array_ + position,
                   sizeof(T) * (size_ - position));
            array_[position] = value;
            ++size_;
        }

        // Removes an element at specified position
        template <typename T> void Vector<T>::remove(size_t position) {
            check_bounds(position);
            memcpy(array_ + position, array_ + position + 1, sizeof(T) * (size_ - position));
            --size_;
        }

        // Deletes the underlying array and sets size and capacity to 0
        template <typename T> void Vector<T>::Clear(void) {
            if (array_ != nullptr) {
                delete[] array_;
                array_ = nullptr;
            }

            size_ = 0;
            capacity_ = 0;
        }

        // Returns weather the vector is empty
        template <typename T> bool Vector<T>::Empty(void) const {
            return size_ == 0;
        }

        // Assignment operator
        template <typename T>
        Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
            if (other.capacity_ > capacity_) {
                if (array_ != nullptr) {
                    delete[] array_;
                }

                ++allocs_;
                array_ = new T[other.size_];
                capacity_ = other.size_;
            }

            size_ = other.size_;
            memcpy(array_, other.array_, sizeof(T) * size_);

            return *this;
        }

        // Concatenates a vector onto the end of this vector.
        template <typename T>
        Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {

            unsigned otherStartSize = other.size();
            for (unsigned i = 0; i < otherStartSize; ++i) {
                push_back(other[i]);
            }

            return *this;
        }

        // Concatenates two Vectors.
        template <typename T>
        Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
            Vector newVec = Vector();

            newVec.array_ = new T[size_ + other.size_];

            memcpy(newVec.array_, array_, sizeof(T) * size_);
            memcpy(newVec.array_ + size_, other.array_, sizeof(T) * other.size_);

            ++newVec.allocs_;

            newVec.size_ = size_ + other.size_;
            newVec.capacity_ = size_ + other.size_;

            return newVec;
        }

        // Subscript operators for const and non-const
        template <typename T> T Vector<T>::operator[](size_t index) const {
            check_bounds(index);
            return array_[index];
        }
        template <typename T> T& Vector<T>::operator[](size_t index) {
            check_bounds(index);
            return array_[index];
        }

        // Reverses the order of the elements in the Vector
        template <typename T> void Vector<T>::reverse() {
            T* newArr = new T[size_];

            for (int i = 0; i < size_; ++i) {
                newArr[i] = array_[(size_ - 1) - i];
            }

            delete[] array_;
            array_ = newArr;
        }

        // Swaps the contents of another Vector with this Vector
        template <typename T> void Vector<T>::swapv(Vector<T>& other) {
            std::swap(other.size_, size_);
            std::swap(other.capacity_, capacity_);
            std::swap(other.array_, array_);
            std::swap(other.allocs_, allocs_);
        }

        // Equality operator
        // Both vectors must be the same size.
        template <typename T>
        bool Vector<T>::operator==(const Vector& other) const {
            if (size_ != other.size_)
                return false;

            for (unsigned i = 0; i < size_; ++i) {
                if (array_[i] != other[i]) {
                    return false;
                }
            }

            return true;
        }

        // Reallocates an array to match the size of the number
        // of elements. If size == capacity, does nothing.
        template <typename T> void Vector<T>::shrink_to_fit() {
            if (size_ == capacity_)
                return;

            T* newArr = new T[size_];
            capacity_ = size_;

            memcpy(newArr, array_, sizeof(T) * size_);

            delete[] array_;
            array_ = newArr;

            ++allocs_;
        }

        // get Vector size
        template <typename T> int Vector<T>::Size(void) const {
            return (int)size_;
        }

        // get Vector capacity
        template <typename T> unsigned Vector<T>::Capacity(void) const {
            return capacity_;
        }

        // get Vector allocations
        template <typename T> unsigned Vector<T>::allocations(void) const {
            return allocs_;
        }

        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        // private
        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////

        // check if an index is valid, throw subscript error if its not
        template <typename T> void Vector<T>::check_bounds(size_t index) const {
            // Don't have to check for < 0 because index is unsigned
            if (index >= size_) {
                /*std::cout << "Attempting to access index " << index << ".";
                std::cout << " The size of the array is " << size_
                          << ". Aborting...\n";
                std::abort();*/

                throw SubscriptError(index);
            }
        }

        // double the capacity of the array
        template <typename T> void Vector<T>::grow() {
            // Double the capacity
            capacity_ = (capacity_) ? capacity_ * 2 : 1;

            // allocate a new array and copy everything to it
            ++allocs_;
            T* newArray = new T[capacity_];

            // delete array if not null
            if (array_ != nullptr) {
                memcpy(newArray, array_, sizeof(T) * size_);
                delete[] array_;
            }

            array_ = newArray;
        }
    } // namespace Data
} // namespace Beta

#endif // VECTOR_H
