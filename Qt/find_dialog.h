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
    explicit find_dialog(QWidget *parent = nullptr);
    ~find_dialog();

signals:
    void find_btn_clicked(QString match_str, bool match_case);


private slots:
    void on_checkBox_stateChanged(int arg1);
    void on_find_btn_clicked();

private:
    Ui::find_dialog *ui;
    bool match_case;
};

#endif // FIND_DIALOG_H
