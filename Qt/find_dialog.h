#ifndef FIND_DIALOG_H
#define FIND_DIALOG_H

#include <QDialog>
#include "texteditor.h"

namespace Ui {
class find_dialog;
}

class find_dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief find_dialog
     *
     * Costruttore che inizializza la ui del dialog
     *
     * @param parent
     */
    explicit find_dialog(QWidget *parent = nullptr);

    /**
     * @brief ~find_dialog
     *
     * Distuttore della classe, dealloca la ui
     *
     */
    ~find_dialog();

signals:
    /**
     * @brief find_btn_clicked
     *
     * Segnala che il bottone find è stato cliccato
     *
     * @param match_str stringa da cercare nel testo
     * @param match_case applica la ricerca all'intera ricerca
     */
    void find_btn_clicked(const QString &match_str, bool match_case);

public slots:
    /**
     * @brief on_str_found
     *
     * Riceve l'evento che la stringa è stata trovata o meno
     *
     * @param is_found se true la stringa cercata è stata trovata almeno una volta
     */
    void str_found(bool is_found);

private slots:
    /**
     * @brief on_checkBox_stateChanged
     *
     * Evento invocato al cambiamento di stato del checkbox
     *
     * @param arg1 parametro che indica in che stato si trova il checkbox
     */
    void on_checkBox_stateChanged(int arg1);

    /**
     * @brief on_find_btn_clicked
     *
     * Evento invocato alla pressione del tasto find
     */
    void on_find_btn_clicked();

private:
    Ui::find_dialog *ui; //!< puntatore alla ui del dialog
    bool match_case; //!< parametro per sapere se la ricerca deve rispettare il match_case
};

#endif // FIND_DIALOG_H
