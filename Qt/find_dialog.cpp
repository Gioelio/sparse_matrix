#include "find_dialog.h"
#include "ui_find_dialog.h"
#include "texteditor.h"

find_dialog::find_dialog(QWidget *parent) : QDialog(parent), ui(new Ui::find_dialog), match_case(false) {
    ui->setupUi(this);
}


find_dialog::~find_dialog()
{
    delete ui;
}

void find_dialog::on_checkBox_stateChanged(int arg1)
{
    match_case = bool(arg1);
}

void find_dialog::on_find_btn_clicked(){
    emit find_btn_clicked(ui->match_str_line_edit->text(), this->match_case);
}
