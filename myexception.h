#ifndef SPARSE_MATRIX_MYEXCEPTION_H
#define SPARSE_MATRIX_MYEXCEPTION_H

#include <stdexcept> //std::range_error

/**
 * Gestione personalizzata delle eccezioni
 */
class my_out_of_range: public std::runtime_error {
public:
    /**
     * @brief Eccezione che viene lanciata quando gli indici escono dalla dimensione logica della matrice
     *
     * @param msg messaggio di errore che viene mostrato quando l'eccezione viene lanciata
     */
    my_out_of_range(const std::string &msg);
};


#endif //SPARSE_MATRIX_MYEXCEPTION_H
