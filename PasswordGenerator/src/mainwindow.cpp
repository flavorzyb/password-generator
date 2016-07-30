#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>
#include <QBoxLayout>
#include <QString>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initSettingsGroup ();
    initUI();
    center();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    setWindowTitle(tr("密码生成工具"));
    setMinimumSize(600, 400);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(settingsGroup);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    mainWidget->setLayout(mainLayout);

}

void MainWindow::center()
{
    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

void MainWindow::initSettingsGroup ()
{
    QLabel * lbType = new QLabel();
    lbType->setText (tr("所用字符:"));
    lbType->setAlignment (Qt::AlignRight | Qt::AlignHCenter);

    upperLetter = new QCheckBox;
    upperLetter->setText (tr("A-Z"));
    upperLetter->setChecked (true);

    lowerLetter = new QCheckBox;
    lowerLetter->setText (tr("a-z"));
    lowerLetter->setChecked (true);

    numberLetter = new QCheckBox;
    numberLetter->setText (tr("0-9"));
    numberLetter->setChecked (true);

    specialLetter = new QCheckBox;
    specialLetter->setText (tr("0-9"));

    QLabel * lbLength = new QLabel();
    lbLength->setText (tr("密码长度:"));
    lbLength->setAlignment (Qt::AlignRight | Qt::AlignHCenter);

    lePassLength = new QLineEdit;
    lePassLength->setText (tr("10"));
    lePassLength->setReadOnly (true);

    passLength = new QSlider;
    passLength->setMinimum (10);
    passLength->setMaximum (50);
    passLength->setTickInterval (1);
    passLength->setOrientation (Qt::Horizontal);

    connect (passLength, SIGNAL(valueChanged(int)), this, SLOT(updatePasswordLength()));

    QGridLayout * layout = new QGridLayout();

    layout->setColumnStretch (0, 2);
    layout->setColumnStretch (1, 2);
    layout->setColumnStretch (2, 2);
    layout->setColumnStretch (3, 2);
    layout->setColumnStretch (4, 2);

    layout->addWidget (lbType, 0, 0);
    layout->addWidget (upperLetter, 0, 1);
    layout->addWidget (lowerLetter, 0, 2);
    layout->addWidget (numberLetter, 0, 3);
    layout->addWidget (specialLetter, 0, 4);

    layout->addWidget (lbLength, 1, 0);
    layout->addWidget (lePassLength, 1, 1);
    layout->addWidget (passLength, 1, 2, 1, 3);

    settingsGroup = new QGroupBox;
    settingsGroup->setTitle (tr("密码选项"));
    settingsGroup->setAutoFillBackground (true);
    settingsGroup->setLayout (layout);
}

void MainWindow::updatePasswordLength ()
{
    QString value = QString::number (passLength->value ());
    lePassLength->setText (value);
}
