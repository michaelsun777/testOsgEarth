#include "osggisdlg.h"
#include "ui_osggisdlg.h"

OsgGisDlg::OsgGisDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OsgGisDlg)
{
    ui->setupUi(this);
}

OsgGisDlg::~OsgGisDlg()
{
    delete ui;
}
