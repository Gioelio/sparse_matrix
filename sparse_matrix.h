#ifndef SPARSE_MATRIX_SPARSE_MATRIX_H
#define SPARSE_MATRIX_SPARSE_MATRIX_H

#include <iostream> //cout
#include <assert.h> //assert
#include <iterator> // std::forward_iterator_tag
#include <cstddef> // std::ptrdiff_t
#include "myexception.h"

template<typename T>
class sparse_matrix {

public:
    typedef T value_t;
    typedef int size_t;
    typedef int position_t;

    struct element {
        position_t x;
        position_t y;
        value_t value;

        element() {}
        element(position_t x, position_t y, const value_t &value): x(x), y(y), value(value){}
        element(const element &other): x(other.x), y(other.y), value(other.value) {}

        element& operator=(const element &other) {
            element tmp(other);
            std::swap(tmp.x, this->x);
            std::swap(tmp.y, this->y);
            std::swap(tmp.value, this->value);

            return *this;
        }

        ~element() {}
    };

private:

    struct nodo {
        element el;
        nodo* next;

        nodo(): next(nullptr), el(nullptr) {}
        explicit nodo(const element e): el(e), next(nullptr) {}
        nodo(const nodo &other): el(other.el), next(nullptr) {}
        nodo(position_t x, position_t y, const value_t &value): next(nullptr), el(x, y, value) {}

        nodo& operator=(const nodo &other) {
            nodo tmp(other);
            std::swap(this->el, tmp.el);
            std::swap(this->next, tmp.next);

            return *this;
        }

        ~nodo() { next = nullptr; }
    };

    nodo* _head;
    size_t _size;
    value_t _default_value;
    position_t _n_columns;
    position_t _n_rows;

public:
    /**
     * @brief Costruttore di default
     *
     * La dimensione della matrice di default è 100x100
     */
    sparse_matrix(): _head(nullptr), _size(0), _n_columns(100), _n_rows(100) {}

    /**
     * @brief Costruttore con valore di default passato come argomento
     *
     * Costruttore che imposta il valore di default da ritornare quando non ci sono valori nella cella letta
     *
     * La dimensione della matrice di default è 100x100
     *
     * @param default_value
     */
    explicit sparse_matrix(const value_t &default_value): _default_value(default_value), _head(nullptr), _size(0), _n_columns(100), _n_rows(100) {}

    /**
     * @brief Costruttore per settare la dimensione e il valore di default della matrice
     *
     * Costruttore che consente di scegliere la dimensione della matrice e il suo valore di default
     *
     * @param default_value valore di default per le celle senza un valore assegnato
     * @param n_rows numero di righe della matrice
     * @param n_cols numero di colonne della matrice
     */
    sparse_matrix(const value_t &default_value, const position_t n_rows, const position_t n_cols):
        _default_value(default_value),
        _head(nullptr),
        _size(0),
        _n_columns(n_cols),
        _n_rows(n_rows){}



    /**
     * @brief Costruttore di copia
     *
     * Prende una sparse matrix e ne genera una copia scollegata contenente gli stessi dati di quella originale
     *
     * @param other
     */
    sparse_matrix(const sparse_matrix &other): _head(nullptr), _size(other._size), _default_value(other._default_value), _n_columns(other._n_columns), _n_rows(other._n_rows) {

        nodo* iter_other = other._head;

        try {

            if (iter_other != nullptr) {
                this->_head = new nodo(*iter_other);
                nodo *iter_curr = this->_head;
                iter_other = iter_other->next;

                while (iter_other != nullptr) {
                    iter_curr->next = new nodo(*iter_other);
                    iter_curr = iter_curr->next;
                    iter_other = iter_other->next;
                }
            }
        } catch(...){
            clear();
            throw;
        }
    }

    /**
     * @brief Operatore di assegnamento
     *
     * Operatore di assegnamento che serve per copiare il contenuto di other in *this.
     *
     * @param other
     * @return reference a sparse_matrix
     */
    sparse_matrix& operator=(const sparse_matrix &other){
        if(this != &other){
            sparse_matrix tmp(other);
            std::swap(this->_head, tmp._head);
            std::swap(this->_size, tmp._size);
            std::swap(this->_default_value, tmp._default_value);
            std::swap(this->_n_rows, tmp._n_rows);
            std::swap(this->_n_columns, tmp._n_columns);
        }
        return *this;
    }

    /**
     * @brief Distruttore della classe
     *
     * Elimina il contenuto delle celle memorizzate nella matrice
     *
     */
    ~sparse_matrix() {
        clear();
    }

    /**
     * @brief Ritorna la quantità di dati salvati
     *
     * Metodo per ottenere il numero di dati che effettivamente sono stati memorizzati sullo heap
     *
     * @return quantità dei dati effettivamente salvati nella matrice
     */
    size_t size() const { return _size;}

    /**
     * @brief Ritorna il valore impostato come valore di default
     *
     * Metodo per ottenere il dato impostato come dato di default
     *
     * @return valore impostato come valore di default
     */
    const value_t& default_value() const { return _default_value;}

    /**
     * @brief Ritorna il numero delle colonne con cui è stata inizializzata la matrice
     *
     * Metodo per conoscere il numero di colonne massime della matrice
     *
     * @return numero di colonne della matrice
     */
    position_t columns() const { return _n_columns; }

    /**
     * @brief Ritorna il numero delle righe con cui è stata iniziliazzata la matrice
     *
     * Metodo per conoscere il numero di righe massime della matrice
     *
     * @return
     */
    position_t rows() const { return _n_rows;}

    /**
     * @brief Metodo per settare il valore di una cella
     *
     * Il metodo imposta il valore della cella in posizione (x, y) con il valore passato come parametro.
     *
     *
     * @param x posizione sulle righe della matrice
     * @param y posizione sulle colonne della matrice
     * @param value valore a cui viene impostata la cella indicata in posizione (x, y)
     * @throw my_out_of_range exception: viene lanciata se x e y sforano le dimensioni della matrice
     */
    void set(position_t x, position_t y, const value_t &value){

        if(x >= _n_rows ||  y >= _n_columns)
            throw my_out_of_range("Il valore degli indici supera il range impostato");

        nodo* current(_head);

        if(_size != 0){
            while (current->next != nullptr){
                if(current->el.x == x && current->el.y == y) {
                    current->el.value = value;
                    return;
                }
                current = current->next;
            }

            if(current->el.x == x && current->el.y == y){
                current->el.value = value;
                return;
            }
        }

        nodo* el = new nodo(x, y, value);

        if(_size == 0)
            _head = el;
        else
            current->next = el;
        _size++;
    }

    void print_test(){
        nodo* current(_head);

        while (current != nullptr){
            current = current->next;
        }
    }


    const value_t& operator()(position_t x, position_t y) const {
        nodo* current(_head);

        while (current != nullptr){
            if(current->el.x == x && current->el.y == y)
                return current->el.value;
            current = current->next;
        }

        return _default_value;
    }

    class const_iterator {
        //sono chiamati trades dell'iteratore e sono info utili per l'iteratore:
        // - che tipo di iteratore è
        // - che tipo di dati contiene
        // - ptrdiff_t tipo di dato della differenza tra 2 puntatori
        // gli altri 2 sono puntatori e reference e qui sono settati const, mentre in iterator no.
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef element                      value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const element*               pointer;
        typedef const element&               reference;


        const_iterator(): ptr(nullptr) {}

        const_iterator(const const_iterator &other): ptr(other.ptr) {}

        const_iterator& operator=(const const_iterator &other) {
            const_iterator tmp(other);
            std::swap(this->ptr, tmp.ptr);
            return *this;
        }

        //Il distruttore sarà quasi sempre vuoto perchè gli iteratori non possiedono i dati
        ~const_iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return ptr->el;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return &ptr->el;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ptr = ptr->next;
            return tmp;
        }

        const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        bool operator==(const const_iterator &other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator &other) const {
            return !(ptr == other.ptr);
        }

    private:
        const nodo* ptr;

        friend class sparse_matrix;

        const_iterator(const nodo* p): ptr(p) {}

    };

    const_iterator begin() const {
        return const_iterator(_head);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

private:
    void clear(){
        nodo* current(_head);

        while(current != nullptr){
            nodo* tmp(current);
            current = current->next;
            delete tmp;
        }

        _head = nullptr;
        _n_rows = 0;
        _n_columns = 0;
        _size = 0;
    }



};

#endif //SPARSE_MATRIX_SPARSE_MATRIX_H
