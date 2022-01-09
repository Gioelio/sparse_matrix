#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QFile>
#include "find_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief TextEditor::TextEditor
     *
     * Costruttore di TextEditor, inizializza la ui
     *
     * @param parent: puntatore al parent
     */
    TextEditor(QWidget *parent = nullptr);

    /**
     * @brief TextEditor::~TextEditor
     *
     * Disturttore della classe, dealloca la ui e il file a cui punta e setta il puntatore a nullptr
     */
    ~TextEditor();

signals:
    /**
     * @brief str_found
     *
     * Segnala che è stata trovata o meno qualche occorrenza all'interno del testo
     *
     * @param is_found
     */
    void str_found(bool is_found);

public slots:

    /**
     * @brief search_text
     *
     * Slot per cercare la stringa match_str nel testo del text editor
     *
     * @param match_str stringa da cercare nel textEditor
     * @param match_case true rende la ricerca limitata al match completo della parola
     */
    void search_text(const QString &match_str, bool match_case);


private slots:

    /**
     * @brief TextEditor::on_btn_new_clicked
     *
     * Pulisce il textEditor e scollega il file a cui era collegato.
     *
     */
    void on_btn_new_clicked();

    /**
     * @brief TextEditor::on_btn_open_clicked
     *
     * Richiede un file all'utente attraverso la window del sistema operativo
     */
    void on_btn_open_clicked();

    /**
     * @brief TextEditor::on_btn_save_clicked
     *
     * Salva il testo dell'editor nel file puntato dal puntatore
     *
     */
    void on_btn_save_clicked();

    /**
     * @brief TextEditor::on_btn_save_with_name_clicked
     *
     * Crea un file txt chiedendo all'utente il nome del file e scrive al suo interno il contenuto del TextEditor
     */
    void on_btn_save_with_name_clicked();

    /**
     * @brief TextEditor::on_btn_find_clicked
     *
     * Apre una dialog per chiedere all'utente come vuole fare la ricerca e su quali parole
     */
    void on_btn_find_clicked();


private:
    Ui::TextEditor *ui; //!< puntatore alla ui
    QFile *file; //!< punta al file nel quale sarà memorizzato il contenuto del textEditor


    /**
     * @brief TextEditor::set_file
     *
     * Imposta un puntatore al file
     *
     * @param file_name: nome del file a cui punta il textEditor
     */
    void set_file(QString file_name);

    /**
     * @brief TextEditor::unset_file
     *
     * Scollega il puntatore dal file
     */
    void unset_file();

    /**
     * @brief TextEditor::update
     *
     * Aggiorna la grafica:
     *  se non c'è un file in cui salvare il testo, disabilita il tasto per salvare
     */
    void update();
};
#endif // TEXTEDITOR_H
