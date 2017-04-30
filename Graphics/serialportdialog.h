#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;

class serialPortDialog : public QDialog
{
    Q_OBJECT

public:
    serialPortDialog(QWidget* parent = 0);
signals:
    void entered(const QString &);
private slots:
    void buttonpressed();
    void enablebutton(const QString&);
public slots:
    void invalidname(const QString& port);
private:
    QPushButton* button, *cancelButton;
    QLabel* label, *invalidmsg;
    QLineEdit* line;
    QVBoxLayout* rightlayout, *invalidlayout;
    QHBoxLayout* mainlayout;
};

#endif // SERIALPORTDIALOG_H
