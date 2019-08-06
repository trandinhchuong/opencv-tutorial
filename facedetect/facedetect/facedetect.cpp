#include "facedetect.h"
#include "ui_facedetect.h"

facedetect::facedetect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::facedetect)
{
    ui->setupUi(this);
}

facedetect::~facedetect()
{
    delete ui;
}
