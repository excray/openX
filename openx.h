#ifndef OPENX_H
#define OPENX_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class openX;
}

class openX : public QWidget
{
    Q_OBJECT

public:
    explicit openX(QWidget *parent = 0);
    ~openX();

private slots:
    void handleButton();

private:
    Ui::openX *ui;
    QLineEdit *lineEdit;
    QPushButton *launchButton;

    void GetProcessList(QStringList& wordList);
    bool showError();

};

#endif // OPENX_H
