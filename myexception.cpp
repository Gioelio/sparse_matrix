#include "myexception.h"

/**
 * @brief Eccezione che viene lanciata quando gli indici escono dalla dimensione logica della matrice
 *
 * @param msg messaggio di errore che viene mostrato quando l'eccezione viene lanciata
 */
my_out_of_range::my_out_of_range(const std::string &msg): std::range_error(msg) {}
