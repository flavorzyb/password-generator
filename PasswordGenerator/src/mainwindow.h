#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initUI();
    void center();
    void initSettingsGroup();
    void initOuttingsGroup();

private slots:
    void updatePasswordLength();

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

    QPushButton * pbGenerator;
};

#endif // MAINWINDOW_H
