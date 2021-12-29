//
// Created by gioele fiorenza on 29/12/21.
//

#ifndef SPARSE_MATRIX_SPARSE_MATRIX_H
#define SPARSE_MATRIX_SPARSE_MATRIX_H

#include <algorithm>
#include <iostream>

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
        element(const element &other): x(other.x), y(other.y), value(other.value), next(nullptr) {} //todo: valutare se ha senso copiare il next

        ~element() {}
    };

    element* _head;
    size_t _size;
    value_t _default_value;
    position_t _n_columns;
    position_t _n_rows;

public:

    /**
     @brief Costruttore di default

     Costruttore che istanzia una matrice sparsa 10 x 10;
     */
    sparse_matrix(): _head(nullptr), _size(0), _n_columns(10), _n_rows(10) {}
    /**
     @brief Costruttore con valore di default passato come argomento

     Costruttore che prende un valore di default che viene ritornato quando nella cella da leggere non è presente il valore

     @param default_value
     */
    explicit sparse_matrix(const value_t &default_value): _default_value(default_value), _head(nullptr), _size(0) {}

    sparse_matrix(const sparse_matrix &other): _head(nullptr), _size(other._size), _default_value(other._default_value) {

        element* iter_other = other._head;

        if(iter_other != nullptr) {
            this->_head = new element(*iter_other);
            element* iter_curr = this->_head;

            while(iter_other != nullptr){
                iter_curr->next = new element(*iter_other);
                iter_curr = iter_curr->next;
                iter_other = iter_other->next;
            }
        }
    }

    sparse_matrix& operator=(const sparse_matrix &other){
        if(this != &other){
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

    size_t size() const { return _size;}
    const value_t& default_value() const { return _default_value;}

    position_t columns() const {
        position_t max_column_num = 0;
        if(_head == nullptr) return 0;
        element* current = _head;

        while(current != nullptr){
            if(current->y > max_column_num) max_column_num = current->y;
            current = current->next;
        }

        return max_column_num;
    }

    position_t rows() const { return _n_rows;}

    void set(position_t x, position_t y, const value_t &value){
        element* current(_head);

        while (_size != 0 && current->next != nullptr){
            if(current->x == x && current->y == y) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        if(_size != 0 && current->x == x && current->y == y){
            current->value = value;
            return;
        }

        element* el = new element(x, y, value);
        if(_m_max < y) _m_max = y;
        if(_n_max < x) _n_max = x;

        if(_size == 0)
            _head = el;
        else
            current->next = el;
        _size++;
    }

    void print_test(){
        element* current(_head);

        while (current != nullptr){
            std::cout << current->x << ", " << current->y << ", " <<  current->value << std::endl;
            current = current->next;
        }
    }


    const value_t& operator()(position_t x, position_t y) const {
        element* current(_head);

        while (current != nullptr){
            if(current->x == x && current->y == y)
                return current->value;
            current = current->next;
        }

        return _default_value;
    }





};

#endif //SPARSE_MATRIX_SPARSE_MATRIX_H
