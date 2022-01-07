#ifndef SPARSE_MATRIX_TEST_CLASS_H
#define SPARSE_MATRIX_TEST_CLASS_H

/**
 * @brief Classe di test
 *
 * classe di test per controllare il comportamento di sparse matrix
 */
class test_class {

public:
    /**
     * @brief Costruttore di default
     *
     * Inizializza il puntatore a nullptr e l'intero al volore di default
     */
    test_class();

    /**
     * @brief Costruttore secondario
     *
     * Inizializza la classe con un intero passato come argomento
     *
     * @param value valore con cui viene inizializzata la classe
     */
    test_class(const int &value);

    /**
     * @brief Costruttore secondario
     *
     * Inizializza la classe usando 2 interi passati come argomento
     *
     * @param value valore con cui viene inizializzata la classe
     * @param value_ptr valore memorizzato nello heap
     */
    test_class(const int &value, const int &value_ptr);

    /**
     * @brief Costruttore di copia
     *
     * Crea una copia basandosi su una test class passata come parametro
     *
     * @param other test class di cui fare la copia
     */
    test_class(const test_class &other);

    /**
     * @brief Operatore di assegnamento
     *
     * Genera una copia e la ritorna all'oggetto prefisso rispetto all'operatore
     *
     * @param other classe di cui eseguire la copia
     * @return la copia di other
     */
    test_class& operator= (const test_class &other);

    /**
     * @brief Distruttore
     *
     * Elimina i dati dallo heap per evitare memory leak
     */
    ~test_class();

    /**
     * @brief Operatore di uguaglianza
     *
     * Confronta 2 test class tra di loro
     *
     * @param other classe con cui confrontare this
     * @return true sse le classi contengono gli stessi dati
     */
    bool operator==(const test_class &other) const;

    /**
     * @brief get_value()
     *
     * Ritorna il valore memorizzato nella classe
     *
     * @return
     */
    int get_value() const;

    /**
     * @brief get_value_ptr()
     *
     * Ritorna il valore puntato dal puntatore
     *
     * @return
     */
    int get_value_ptr() const;

private:
    int value;
    int* ptr;
};

#endif //SPARSE_MATRIX_TEST_CLASS_H
