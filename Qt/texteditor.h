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
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

signals:
    void str_found(bool is_found);

public slots:
    void search_text(QString match_str, bool match_case);


private slots:
    void on_btn_new_clicked();

    void on_btn_open_clicked();

    void on_btn_save_clicked();

    void on_btn_save_with_name_clicked();

    void on_btn_find_clicked();


private:
    Ui::TextEditor *ui;
    QFile *file;

    void set_file(QString file_name);
    void unset_file();
    void update();
};
#endif // TEXTEDITOR_H
