#ifndef SPARSE_MATRIX_SPARSEMATRIX_H
#define SPARSE_MATRIX_SPARSEMATRIX_H

#include <iostream> //cout
#include <assert.h> //assert
#include <iterator> // std::forward_iterator_tag
#include <cstddef> // std::ptrdiff_t
#include "myexception.h"

/**
 * @brief Gestisce una sparse matrix
 *
 * Mantiene in memoria solamente le celle di dati effettivamente inserite dall'utente,
 * se la cella non è presente viene ritornato il valore di default dello stesso tipo di T
 *
 * @tparam T tipo del dato che viene memorizzato nelle cella della matrice o viene ritornato come tipo di default
 */
template<typename T>
class SparseMatrix {

public:
    /** tipo associato al tipo T templato */
    typedef T value_t;
    /** tipo usato per la dimensione della matrice */
    typedef int size_t;
    /** tipo usato per identificare le coordinate all'interno della matrice */
    typedef int position_t;

    /**
     * @struct element
     * @brief Memorizza la posizione x e y dell'elemento nella matrice e il suo valore in value
     *
     * L'elemento viene ritornato dal deferenziamento di un iteratore e contiene oltre al valore effettivo, le informazioni
     * relative al suo posizionamento all'interno della matrice
     */
    struct element {
        position_t x; //!< posizione sulle righe della matrice
        position_t y; //!< posizione sulle colonne della matrice
        value_t value; //!< valore memorizzato dalla cella

        /**
         * @brief Costruttore di default di element
         *
         * Il costruttore di default di element richiama i costruttori di default dei suoi attributi membro
         */
        element(): x(), y(), value() {}

        /**
         * @brief Costruttore secondario
         *
         * Prende come parametro i valori dei dati membro e li assegna
         *
         * @param x posizione sulle righe della matrice
         * @param y posizione sulle colonne della matrice
         * @param value valore del dato memorizzato
         */
        element(position_t x, position_t y, const value_t &value): x(x), y(y), value(value){}

        /**
         * @brief Costruttore di copia
         *
         * Inizializza un nuovo oggetto sparse matrix copiando il contenuto di un'altro oggetto
         *
         * @param other oggetto di cui viene fatta la copia
         */
        element(const element &other): x(other.x), y(other.y), value(other.value) {}

        /**
         * @bief operatore di assegnamento
         *
         * Crea una copia del valore di element in una variabile dello stesso tipo
         *
         * @param other parametro dell'elemento da copiare
         * @return viene ritornata l'istanza di this (parametro prefisso dell'operatore = )
         */
        element& operator=(const element &other) {
            element tmp(other);
            std::swap(tmp.x, this->x);
            std::swap(tmp.y, this->y);
            value = other.value;

            return *this;
        }

        /**
         * @brief Distruttore
         */
        ~element() {}
    };

private:


    /**
     * @struct nodo
     * @brief struttura interna della sparse matrix per la gestione delle celle
     *
     * La struttura del nodo contiene un elemento, che corrisponde al dato effettivo e al puntatore al nodo successivo
     *
     */
    struct nodo {
        element el; //!< valore dell'elemento
        nodo* next; //!< puntatore al nodo successivo

        /**
         * @brief Costruttore di default di nodo
         *
         * Costruttore che inizializza il nodo con i valori di default, next a nullptr e chiama il costruttore di default
         * di element
         */
        nodo(): next(nullptr), el() {}

        /**
         * @brief Costruttore secondario
         *
         * Genera un nodo a partire da un elemento
         *
         * @param el elemento su cui effettua la copia
         */
        explicit nodo(const element &el): el(el), next(nullptr) {}

        /**
         * @brief Costruttore di copia
         *
         * Genera una copia del nodo a partire da un elemento other, non fa la copia del puntatore next
         *
         * @param other elemento di cui viene effettuata la copia
         */
        nodo(const nodo &other): el(other.el), next(nullptr) {}

        /**
         * @brief Costruttore secondario che prende tutti i parametri
         *
         * Inizializza il nodo passando tutti i parametri nel costruttore
         *
         * @param x posizione sulle colonne della matrice
         * @param y posizione sulle righe della matrice
         * @param value valore contenuto nella cella della matrice
         */
        nodo(position_t x, position_t y, const value_t &value): next(nullptr), el(x, y, value) {}

        /**
         * @brief operatore di assegnamento
         *
         * Crea una copia del nodo e la assegna all'istanza di this (parametro prefisso di operator =).
         * Elimina in automatico il puntatore memorizzato all'interno di this
         *
         * @param other nodo di cui viene effettuata la copia
         * @return ritorna la nuova copia dell'elemento
         */
        nodo& operator=(const nodo &other) {
            nodo tmp(other);
            std::swap(this->el, tmp.el);
            std::swap(this->next, tmp.next);

            return *this;
        }

        /**
         * @brief Distruttore
         */
        ~nodo() { next = nullptr; }
    };

    nodo* _head; //!< puntatore al primo elemento della lista
    size_t _size; //!< numero di elementi effettivamente memorizzati all'interno della lista
    value_t _default_value; //!< valore che viene ritornato se la cella cercata non esiste in memoria
    position_t _n_columns; //!< numero di colonne della matrice logica
    position_t _n_rows; //!< numero di righe della matrice logica

public:
    /**
     * @brief Costruttore di default
     *
     * La dimensione di default della matrice è 0x0
     */
    SparseMatrix(): _head(nullptr), _size(0), _n_columns(0), _n_rows(0), _default_value() {}

    /**
     * @brief Costruttore con valore di default passato come argomento
     *
     * Imposta il valore di default da ritornare quando non ci sono valori nella cella letta.
     * Imposta 0x0 come dimensione della matrice
     *
     * @param default_value
     */
    explicit SparseMatrix(const value_t &default_value): _default_value(default_value), _head(nullptr), _size(0), _n_columns(0), _n_rows(0) {}

    /**
     * @brief Costruttore per settare la dimensione e il valore di default della matrice
     *
     * Imposta la dimensione della matrice e il suo valore di default
     *
     * @param default_value valore di default per le celle senza un valore assegnato
     * @param n_rows numero di righe della matrice
     * @param n_cols numero di colonne della matrice
     */
    SparseMatrix(const value_t &default_value, const position_t n_rows, const position_t n_cols):
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
     * @param other sparse matrix di cui fare la copia
     */
    SparseMatrix(const SparseMatrix &other): _head(nullptr), _size(other._size), _default_value(other._default_value), _n_columns(other._n_columns), _n_rows(other._n_rows) {

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
     * Crea una copia di other in this e ripulisce le vecchie celle di this.
     *
     * @param other sparse matrix di cui fare la copia
     * @return reference a SparseMatrix
     */
    SparseMatrix& operator=(const SparseMatrix &other){
        if(this != &other){
            SparseMatrix tmp(other);
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
    ~SparseMatrix() {
        clear();
    }

    /**
     * @brief Ritorna la quantità di dati salvati
     *
     * Ritorna il numero di dati che effettivamente sono stati memorizzati sullo heap
     *
     * @return quantità dei dati effettivamente salvati nella matrice
     */
    size_t size() const { return _size;}

    /**
     * @brief Ritorna il valore impostato come valore di default
     *
     * Ritorna il dato impostato come dato di default
     *
     * @return valore impostato come valore di default
     */
    const value_t& default_value() const { return _default_value;}

    /**
     * @brief Ritorna il numero delle colonne con cui è stata inizializzata la matrice
     *
     * Ritorna il numero di colonne massime della matrice
     *
     * @return numero di colonne massime della matrice
     */
    position_t columns() const { return _n_columns; }

    /**
     * @brief Ritorna il numero delle righe con cui è stata inizializzata la matrice
     *
     * Ritorna il numero di righe massime della matrice
     *
     * @return numero di righe massime della matrice
     */
    position_t rows() const { return _n_rows;}

    /**
     * @brief Metodo per settare il valore di una cella
     *
     * Imposta il valore della cella in posizione (x, y) con il valore passato come parametro.
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

    /**
     * @brief Operator() per ottenere l'elemento in posizione (x, y)
     *
     * Ritorna l'elemento della matrice memorizzato all'interno la cella (x, y)
     *
     * @param x Posizione sulle righe della matrice
     * @param y Posizione sulle colonne della matrice
     * @return valore memorizzato nella cella della matrice
     */
    const value_t& operator()(position_t x, position_t y) const {
        nodo* current(_head);

        while (current != nullptr){
            if(current->el.x == x && current->el.y == y)
                return current->el.value;
            current = current->next;
        }

        return _default_value;
    }

    /**
     * @brief Funzione clear per pulire la memoria
     *
     * Rimuove tutti gli elementi presenti nella matrice dallo heap
     *
     */
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

    /**
     * @brief classe const_iterator
     *
     * Genera un const iterator per la sparse matrix seguendo la struttura standard degli iteratori costanti
     *
     */
    class const_iterator {

    public:
        /** tipo per identificare la tipologia di iteratore (forward) */
        typedef std::forward_iterator_tag iterator_category;
        /** tipo del valore ritornato dall'iteratore */
        typedef element                   value_type;
        /** tipo per la differenza tra 2 puntatori*/
        typedef ptrdiff_t                 difference_type;
        /** puntatore al tipo di dato puntato dall'iteratore*/
        typedef const element*            pointer;
        /** reference al tipo di dato ritornato dall'iteratore*/
        typedef const element&            reference;

        /**
         * @brief Costruttore di default
         *
         * Inizializza il puntatore dell'iteratore a nullptr
         */
        const_iterator(): ptr(nullptr) {}

        /**
         * @brief Costruttore di copia
         *
         * Crea un iteratore eseguendo la copia di un altro iteratore
         *
         * @param other iteratore da cui copiare il puntatore
         */
        const_iterator(const const_iterator &other): ptr(other.ptr) {}

        /**
         * @brief Operatore di assegnamento
         *
         * Esegue una copia del puntatore, la memorizza nell'oggetto prefisso e ritorna l'elemento
         *
         * @param other iteratore di cui eseguire la copia
         * @return
         */
        const_iterator& operator=(const const_iterator &other) {
            const_iterator tmp(other);
            std::swap(this->ptr, tmp.ptr);
            return *this;
        }

        /**
         * @brief Distruttore
         *
         * Non viene eliminato nessun dato
         *
         */
        ~const_iterator() {}

        /**
         * @brief Operatore di deferenziamento
         *
         * Ritorna il dato puntato dall'iteratore
         *
         * @return reference all'elemento element
         */
        reference operator*() const {
            return ptr->el;
        }

        /**
         * @brief Operatore di accesso al dato
         *
         * Ritorna il puntatore al dato puntato dall'iteratore
         *
         * @return
         */
        pointer operator->() const {
            return &ptr->el;
        }

        /**
         * @brief Operatore di incremento postfisso
         *
         * Ritorna il dato puntato dall'iteratore e successivamente sposta il puntatore all'elemento successivo
         *
         * @return l'iteratore prima dell'incremento
         */
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ptr = ptr->next;
            return tmp;
        }

        /**
         * @brief Operatore di incremento prefisso
         *
         * Sposta l'iteratore all'elemento successivo e ritorna il nuovo elemento puntato
         *
         * @return l'iteratore dopo l'incremento
         */
        const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        /**
         * @brief Operatore di uguaglianza
         *
         * Confronta due iteratori tra di loro, ritorna true se puntano allo stesso nodo
         *
         * @param other iteratore di confronto
         * @return true sse i puntatori degli iteratori stanno puntando allo stesso nodo
         */
        bool operator==(const const_iterator &other) const {
            return ptr == other.ptr;
        }

        /**
         * @brief Operatore di diversità
         *
         * Confronta due iteratori tra di loro, ritorna true se sono diversi
         *
         * @param other iteratore di confronto
         * @return true sse i puntatori degli iteratori stanno puntando a nodi diversi
         */
        bool operator!=(const const_iterator &other) const {
            return !(ptr == other.ptr);
        }

    private:
        const nodo* ptr; //!< nodo puntato dall'iteratore

        friend class SparseMatrix;

        /**
         * @brief Costrutture privato dell'iteratore
         *
         * Costruttore usato dalla classe friend per costruire l'iteratore a partire dal puntatore al nodo
         *
         * @param p puntatore al nodo con cui viene inizializzato l'iteratore
         */
        const_iterator(const nodo* p): ptr(p) {}

    };

    const_iterator begin() const {
        return const_iterator(_head);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

};

#endif //SPARSE_MATRIX_SPARSEMATRIX_H
