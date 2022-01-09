#include "texteditor.h"
#include "ui_texteditor.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCharFormat>
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

void TextEditor::set_file(QString &file_name)
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
    connect(this, &TextEditor::str_found, &find, &find_dialog::str_found);

    find.setModal(true);
    find.exec();

}

void TextEditor::search_text(const QString &match_str, bool match_case)
{

    QTextDocument *document = ui->text_editor->document();


    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    bool found(false);

    QTextCharFormat format = QTextCharFormat();
    format.setBackground(Qt::transparent);

    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(ui->text_editor->toPlainText().length(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);
    cursor.setPosition(0, QTextCursor::MoveAnchor);


    format.setForeground(Qt::yellow);

    cursor.beginEditBlock();
    cursor.setCharFormat(format);

    while(!highlight_cursor.isNull() && !highlight_cursor.atEnd()){
        if(match_case)
            highlight_cursor = document->find(match_str, highlight_cursor, QTextDocument::FindWholeWords);
        else
            highlight_cursor = document->find(match_str, highlight_cursor);

        if(!highlight_cursor.isNull()) {
            found = true;
            highlight_cursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
            highlight_cursor.mergeCharFormat(format);
        }
    }

    cursor.endEditBlock();

    emit str_found(!found);

}
