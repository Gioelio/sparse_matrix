#include "texteditor.h"
#include "ui_texteditor.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCharFormat>
#include <iostream> //TODO: da rimuovere
#include <string>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TextEditor), file(nullptr)
{
    ui->setupUi(this);

}

TextEditor::~TextEditor()
{
    delete ui;
    delete file;
    ui = nullptr;
    file = nullptr;
}

void TextEditor::unset_file(){
    delete this->file;
    this->file = nullptr;
}

void TextEditor::set_file(QString file_name)
{
    this->unset_file();
    this->file = new QFile(file_name);
}

void TextEditor::on_btn_new_clicked()
{
    this->unset_file();
    ui->text_editor->clear();
    update();
}


void TextEditor::on_btn_open_clicked()
{
    QString file_content;

    QString file_name = QFileDialog::getOpenFileName(this, "Scegli il file", "/", "*.txt");

    if(file_name.isEmpty())
        return;

    this->set_file(file_name);

    if(!this->file->open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(this->file);

    file_content = in.readAll();

    this->file->close();

    ui->text_editor->clear();
    ui->text_editor->setPlainText(file_content);
    update();
}



void TextEditor::on_btn_save_clicked()
{
    if(file == nullptr)
        return;

    if(!file->open(QIODevice::ReadWrite | QIODevice::WriteOnly))
        return;


    QTextStream out(file);
    out << ui->text_editor->toPlainText();
    file->close();

    update();
}

void TextEditor::update(){
    bool there_is_file = file == nullptr;

    ui->btn_save->setDisabled(there_is_file);
}


void TextEditor::on_btn_save_with_name_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Salva il file", "/", "Text File(*.txt)");

    if(file_name.isEmpty())
        return;

    set_file(file_name);
    on_btn_save_clicked();
    update();
}


void TextEditor::on_btn_find_clicked()
{
    find_dialog find;

    connect(&find, &find_dialog::find_btn_clicked, this, &TextEditor::search_text);

    find.setModal(true);
    find.exec();

}

void TextEditor::search_text(QString match_str, bool match_case)
{
    std::string text;

    if(!match_case){
        match_str = match_str.toLower();
        text = ui->text_editor->toPlainText().toLower().toStdString();
    }
    else
        text = ui->text_editor->toPlainText().toStdString();

    QTextCursor cursor(ui->text_editor->document());
    std::size_t found = text.find(match_str.toStdString());

    QTextCharFormat format = QTextCharFormat();
    format.setBackground(Qt::transparent);

    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(text.length(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);

    format.setBackground(Qt::yellow);

    while(found != std::string::npos){
        cursor.setPosition(found, QTextCursor::MoveAnchor);
        cursor.setPosition(found + match_str.length(), QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);

        found = text.find(match_str.toStdString(), found + 1);
    }

}
