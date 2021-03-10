#ifndef NEWDOCUMENT_H
#define NEWDOCUMENT_H

#include <QDialog>

namespace Ui {
class NewDocument;
}

class NewDocument : public QDialog
{
    Q_OBJECT
    int count;

public:
    explicit NewDocument(class Document* Document, QWidget *parent = nullptr);
    void setName(QString DocName);
    void on_document_clicked();
    ~NewDocument();

private slots:

    void on_cansel_clicked();
    void on_addScan_clicked();
    void on_removeScan_clicked();
    void on_save_clicked();

private:
    Ui::NewDocument *ui;
    QLayout *documentsListLayout;
    QWidget *widget;
    class Document *document;
};

#endif // NEWDOCUMENT_H
