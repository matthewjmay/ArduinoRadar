#include "serialportdialog.h"
#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

serialPortDialog::serialPortDialog(QWidget *parent) : QDialog(parent)
{
    button = new QPushButton("Open");
    button -> setDefault(true);
    cancelButton = new QPushButton("Abort");
    label = new QLabel("Enter serial port name:");
    invalidmsg = new QLabel;
    invalidmsg->setVisible(false);
    line = new QLineEdit;
    button -> setEnabled(false);

    connect(line, &QLineEdit::textChanged, this, &serialPortDialog::enablebutton);
    connect(button, &QPushButton::clicked, this, &serialPortDialog::buttonpressed);
    connect(cancelButton, &QPushButton::clicked, parent, &QWidget::close);
    connect(cancelButton, &QPushButton::clicked, this, &QWidget::close);

    rightlayout = new QVBoxLayout;
    rightlayout->addWidget(button);
    rightlayout->addWidget(cancelButton);

    mainlayout = new QHBoxLayout;
    mainlayout->addWidget(label);
    mainlayout->addWidget(line);
    mainlayout->addLayout(rightlayout);

    invalidlayout = new QVBoxLayout;
    invalidlayout->addLayout(mainlayout);
    invalidlayout->addWidget(invalidmsg);

    setLayout(invalidlayout);
    setWindowTitle("Serial Port Manager");
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void serialPortDialog::buttonpressed(){
    emit entered(line->text());
}
void serialPortDialog::enablebutton(const QString& text){
    button->setEnabled(!text.isEmpty());
}

void serialPortDialog::invalidname(const QString &port){
    invalidmsg->setText("Port " + port + " could not be opened");
    invalidmsg->setVisible(true);
}
