#ifndef VIEWDOCUMENT_H
#define VIEWDOCUMENT_H

#include <QDialog>

namespace Ui {
class ViewDocument;
}

class ViewDocument : public QDialog
{
    Q_OBJECT

    class Document * document;
    QList<QString> scans;
    int scansCount;

public:
    explicit ViewDocument(Document * Document, QWidget *parent = nullptr);
    void setName(QString DocName);
    void on_document_clicked();
    ~ViewDocument();

private slots:
    void on_cansel_clicked();
    void on_save_clicked();

    void on_addScan_clicked();
    void on_removeScan_clicked();

private:
    Ui::ViewDocument *ui;
};

#endif // VIEWDOCUMENT_H
