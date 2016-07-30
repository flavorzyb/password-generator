#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setApplication(const QApplication * app);
private:
    void initUI();
    void center();
    void initSettingsGroup();
    void initOuttingsGroup();
    void initOperatorGroup();
    void addEvent();
    void removeEvent();
    QVector<char> createPasswordSlat();
    bool checkSettings();
private slots:
    void updatePasswordLength();
    void copyPasswordToClipboard();
    void generaterPassword();
    void exit();
private:
    QWidget * mainWidget;
    QGroupBox * settingsGroup;
    QCheckBox * upperLetter;
    QCheckBox * lowerLetter;
    QCheckBox * numberLetter;
    QCheckBox * specialLetter;
    QSlider * passLength;
    QLineEdit * lePassLength;

    QGroupBox * outtingsGroup;
    QLineEdit * lePassword;
    QPushButton * pbCopyPassword;

    QGroupBox * operatorGroup;
    QPushButton * pbGenerator;
    QPushButton * pbExit;

    const QApplication * applicaton;
};

#endif // MAINWINDOW_H
