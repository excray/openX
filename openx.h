#ifndef OPENX_H
#define OPENX_H

#include <QWidget>

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
    void on_quitButton_clicked();

private:
    Ui::openX *ui;
};

#endif // OPENX_H
