//
// Created by gioele fiorenza on 29/12/21.
//

#ifndef SPARSE_MATRIX_SPARSE_MATRIX_H
#define SPARSE_MATRIX_SPARSE_MATRIX_H

#include <algorithm>
#include <iostream> //TODO: da rimuovere

template<typename T>
class sparse_matrix {

public:
    typedef T value_t;
    typedef unsigned int size_t;
    typedef unsigned int position_t;

private:

    struct element {
        position_t x;
        position_t y;
        value_t value;
        element* next;

        element(): next(nullptr) {}
        element(position_t x, position_t y, const value_t &value): x(x), y(y), value(value), next(nullptr) {}

        ~element() { delete value; }
    };

    element* _head;
    size_t _size;
    value_t _default_value;

public:

    sparse_matrix(): _head(nullptr), _size(0) {}
    explicit sparse_matrix(const value_t &default_value): _default_value(default_value), _head(nullptr), _size(0) {}

    sparse_matrix(const sparse_matrix &other): _head(nullptr), _size(0), _default_value(other._default_value) {
        //TODO: fare la copia degli elementi in element (usare add definito sotto)
    }

    sparse_matrix& operator=(const sparse_matrix &other){
        if(this != other){
            sparse_matrix tmp(other);
            std::swap(this->_head, tmp._head);
            std::swap(this->_size, tmp._size);
            std::swap(this->_default_value, tmp._default_value);
        }
        return *this;
    }

    ~sparse_matrix() {
        element* current(_head);

        //ho preferito fare un while sui puntatori, perché la size indica il numero di celle con un dato valido
        while(current != nullptr){
            element* tmp(current);
            current = current->next;
            delete tmp;
        }
    }

    void set(position_t x, position_t y, const value_t &value){
        element* current(_head);

        while (_size != 0 && current->next != nullptr){
            if(current->x == x && current->y == y) {
                current->value(value);
                return;
            }
            current = current->next;
        }

        if(current->x == x && current->y == y) {
            current->value(value);
            return;
        }

        if(_size != 0 && current->x == x && current->y == y){
            current->value(value);
            return;
        }

        element* el = new element(x, y, value);
        _head = el;
        _size++;
    }

    void print_test(){
        element* current(_head);

        while (current != nullptr){
            if(current->x == x && current->y == y)
                return *current->value;
            current = current->next;
        }
    }


    const value_t& operator()(position_t x, position_t y) const {
        element* current(_head);

        while (current != nullptr){
            if(current->x == x && current->y == y)
                return *current->value;
            current = current->next;
        }

        return *_default_value;
    }





};

#endif //SPARSE_MATRIX_SPARSE_MATRIX_H
