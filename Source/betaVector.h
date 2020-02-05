//------------------------------------------------------------------------------
//
// File Name:	betaVector.h
// Author(s):	Brandon Wolenetz
// Project:		Project 2 : Object Management
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include <cstring>


namespace Beta {
    namespace Data {

        //a templated re-sizseable array class because you said I cant use std::vector...

        template <typename type>
        class Vector {
        public:

            //default constructor
            Vector();

            //copy constructor
            Vector(const Vector<type>& other);

            //destructor
            ~Vector();

            //getters
            size_t Size() const;
            size_t Capacity() const;

            //push a type to the back of the vector
            void push_back(const type& val);

            //pop off the back of the vector
            void pop_back();

            //remove the type at the index provided
            void remove(const size_t index);

            //access the vector array
            type& operator[](const size_t index);

            //access the vector array
            const type& operator[](const size_t index) const;

            //assignment operator
            Vector<type>& operator=(const Vector<type>& other);

            //clear the vector
            void Clear();


        private:

            //private member variables
            type* m_array;
            size_t m_size;
            size_t m_capacity;

        };



        //------templated class member functions------

        //default constructor
        template <typename type>
        Vector<type>::Vector() : m_size(0), m_capacity(1) {
            m_array = new type[m_capacity];
        }

        //copy constructor
        template <typename type>
        Vector<type>::Vector(const Vector<type>& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
            m_array = new type[other.m_capacity];
            std::memcpy(m_array, other.m_array, sizeof(type) * other.m_size);
        }

        //destructor
        template <typename type>
        Vector<type>::~Vector() {
            delete[] m_array;
        }

        //getters
        template <typename type>
        size_t Vector<type>::Size() const {
            return m_size;
        }
        template <typename type>
        size_t Vector<type>::Capacity() const {
            return m_capacity;
        }

        //push a type to the back of the vector
        template <typename type>
        void Vector<type>::push_back(const type& val) {
            if (m_size + 1 > m_capacity) {
                m_capacity *= 2;

                type* newArray = new type[m_capacity];
                std::memcpy(newArray, m_array, sizeof(type) * m_size);

                delete[] m_array;
                m_array = newArray;
            }

            m_array[m_size] = val;
            ++m_size;

        }

        //pop off the back of the vector
        template <typename type>
        void Vector<type>::pop_back() {
            if(m_size > 0)
                --m_size;
        }

        //remove the type at the index provided
        template <typename type>
        void Vector<type>::remove(const size_t index) {
            if (index >= 0 && index < m_size) {
                std::memcpy(m_array + index, m_array + index + 1, sizeof(type) * (m_size - index));
                --m_size;
            }
        }

        //access the vector array
        template <typename type>
        type& Vector<type>::operator[](const size_t index) {
            return m_array[index];
        }

        //access the vector array
        template <typename type>
        const type& Vector<type>::operator[](const size_t index) const {
            return m_array[index];
        }

        //assignment operator
        template <typename type>
        Vector<type>& Vector<type>::operator=(const Vector<type>& other) {
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            delete[] m_array;

            m_array = new type[other.m_capacity];
            std::memcpy(m_array, other.m_array, sizeof(type) * other.m_size);

            return *this;
        }

        //clear the vector
        template <typename type>
        void Vector<type>::Clear() {
            m_size = 0;
        }

    }
}