#ifndef FACEDETECT_H
#define FACEDETECT_H

#include <QMainWindow>

namespace Ui {
class facedetect;
}

class facedetect : public QMainWindow
{
    Q_OBJECT

public:
    explicit facedetect(QWidget *parent = nullptr);
    ~facedetect();

private:
    Ui::facedetect *ui;
};

#endif // FACEDETECT_H
