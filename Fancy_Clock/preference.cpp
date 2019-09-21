#include <QSettings>
#include "preference.h"
#include "ui_preference.h"

Preference::Preference(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preference)
{
    ui->setupUi(this);

    QSettings sts;
    //Set current colour to colour from settings
    ui->colourBox->setCurrentIndex(sts.value("Colour").toInt());

    //Run onAccepted function when preference has been accepted
    connect(ui->buttonBox,
            &QDialogButtonBox::accepted,
            this,
            &Preference::onAccepted);

}

Preference::~Preference()
{
    delete ui;
}

void Preference::onAccepted(){
    QSettings sts;
    sts.setValue("Colour", ui->colourBox->currentIndex());
    this->accept();
}
