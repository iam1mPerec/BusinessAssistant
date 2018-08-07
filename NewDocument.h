#ifndef NEWDOCUMENT_H
#define NEWDOCUMENT_H

#include <QDialog>

namespace Ui {
class NewDocument;
}

class NewDocument : public QDialog
{
    Q_OBJECT

public:
    explicit NewDocument(class Document &Document, QWidget *parent = nullptr);
    ~NewDocument();

private slots:

    void on_cansel_clicked();
    void on_addScan_clicked();
    void on_document_clicked();

    void on_removeScan_clicked();

private:
    Ui::NewDocument *ui;
    QLayout *documentsListLayout;
    QWidget *widget;
    class Document &document;
};

#endif // NEWDOCUMENT_H
