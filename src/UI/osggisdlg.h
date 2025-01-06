#ifndef OSGGISDLG_H
#define OSGGISDLG_H

#include <QDialog>

namespace Ui {
class OsgGisDlg;
}

class OsgGisDlg : public QDialog
{
    Q_OBJECT

public:
    explicit OsgGisDlg(QWidget *parent = nullptr);
    ~OsgGisDlg();

private:
    Ui::OsgGisDlg *ui;
};

#endif // OSGGISDLG_H
