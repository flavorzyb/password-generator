#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>
#include <QBoxLayout>
#include <QString>
#include <QTime>
#include <QClipboard>
#include <QMessageBox>

#include "mainwindow.h"

static const char * const SPECIAL_LETTER = "!@#$%^&*";
static const size_t SPECIAL_LETTER_LEN = strlen(SPECIAL_LETTER);

bool isSpecialLetter(char s) {
    for (size_t i = 0; i < SPECIAL_LETTER_LEN; i++) {
        if (s == *(SPECIAL_LETTER + i)) {
            return true;
        }
    }

    return false;
}

QVector<char> randLetter(const QVector<char> &slat)
{
    QVector<char> result;
    int len = 0;
    int slatSize = slat.size();
    char * s = NULL;
    int index;
    do {
        index = qrand() % slatSize;

        if ((NULL == s) || (*s != slat.at(index))) {
            len++;
            result.append(slat.at(index));
        }
    }while(len < 2);

    return result;
}

bool isMoreThanLetter(const QVector<char> & data, char s)
{
    int times = 0;
    int size = data.size();
    for (int i = 0; i < size; i++) {
        if (s == data.at(i)) {
            times ++;
        }

        if (times >= 2) {
            return true;
        }
    }

    return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      applicaton(NULL)
{
    initSettingsGroup ();
    initOuttingsGroup ();
    initOperatorGroup();
    initUI();
    center();
    addEvent();
}

MainWindow::~MainWindow()
{
    removeEvent ();
}

void MainWindow::initUI()
{
    mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    setWindowTitle(tr("密码生成工具"));
    setMinimumSize(800, 600);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(settingsGroup);
    mainLayout->addWidget(outtingsGroup);
    mainLayout->addWidget(operatorGroup);
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
    specialLetter->setText (tr(SPECIAL_LETTER));

    QLabel * lbLength = new QLabel();
    lbLength->setText (tr("密码长度:"));
    lbLength->setAlignment (Qt::AlignRight | Qt::AlignHCenter);

    lePassLength = new QLineEdit;
    lePassLength->setText (tr("16"));
    lePassLength->setReadOnly (true);

    passLength = new QSlider;
    passLength->setMinimum (10);
    passLength->setMaximum (50);
    passLength->setTickInterval (1);
    passLength->setValue(16);
    passLength->setOrientation (Qt::Horizontal);

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

void MainWindow::initOuttingsGroup ()
{
    QLabel * lbType = new QLabel();
    lbType->setText (tr("生成结果:"));
    lbType->setAlignment (Qt::AlignRight | Qt::AlignHCenter);

    lePassword = new QLineEdit;
    lePassword->setReadOnly (true);
    lePassword->setText (tr("请点击生成密码按钮生成密码"));
    lePassword->setEnabled (false);

    pbCopyPassword = new QPushButton;
    pbCopyPassword->setText (tr("拷贝密码"));
    pbCopyPassword->setEnabled(false);

    QGridLayout * layout = new QGridLayout();

    layout->setColumnStretch (0, 2);
    layout->setColumnStretch (1, 6);
    layout->setColumnStretch (2, 2);

    layout->addWidget (lbType, 0, 0);
    layout->addWidget (lePassword, 0, 1);
    layout->addWidget (pbCopyPassword, 0, 2);

    outtingsGroup = new QGroupBox;
    outtingsGroup->setTitle (tr("结果"));
    outtingsGroup->setAutoFillBackground (true);
    outtingsGroup->setLayout (layout);
}

void MainWindow::initOperatorGroup()
{
    pbGenerator = new QPushButton;
    pbGenerator->setText (tr("生成密码"));
    pbGenerator->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    pbExit = new QPushButton;
    pbExit->setText (tr("退出程序"));
    pbExit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QGridLayout * layout = new QGridLayout();

    layout->setColumnStretch (0, 5);
    layout->setColumnStretch (1, 5);

    layout->addWidget (pbGenerator, 0, 0);
    layout->addWidget (pbExit, 0, 1);

    operatorGroup = new QGroupBox;
    operatorGroup->setTitle (tr("操作"));
    operatorGroup->setAutoFillBackground (true);
    operatorGroup->setLayout (layout);
}

void MainWindow::addEvent()
{
    connect(passLength, SIGNAL(valueChanged(int)), this, SLOT(updatePasswordLength()));
    connect(pbCopyPassword, SIGNAL(pressed()), this, SLOT(copyPasswordToClipboard()));
    connect(pbGenerator, SIGNAL(pressed()), this, SLOT(generaterPassword()));
    connect(pbExit, SIGNAL(pressed()), this, SLOT(exit()));
}

void MainWindow::removeEvent()
{
    disconnect(passLength, SIGNAL(valueChanged(int)), this, SLOT(updatePasswordLength()));
    disconnect(pbCopyPassword, SIGNAL(pressed()), this, SLOT(copyPasswordToClipboard()));
    disconnect(pbGenerator, SIGNAL(pressed()), this, SLOT(generaterPassword()));
    disconnect(pbExit, SIGNAL(pressed()), this, SLOT(exit()));
}

void MainWindow::copyPasswordToClipboard()
{
    QClipboard * clipboard = QApplication::clipboard();
    clipboard->setText(lePassword->text());
}

void MainWindow::generaterPassword()
{
    pbCopyPassword->setEnabled(false);
    lePassword->setEnabled(false);
    if (!checkSettings()) {
        QMessageBox mb(this);
        mb.setWindowTitle("错误");
        mb.setText(tr("生成密码的字符不得低于2种"));
        mb.exec();
        return ;
    }
    pbCopyPassword->setEnabled(true);
    lePassword->setEnabled(true);

    lePassword->setText(createPassword());
}

const QString MainWindow::createPassword()
{
    int length = passLength->value();
    QVector<char> passVector = createPasswordPrefix();
    QVector<char> slat = createPasswordSlat();
    int index;
    int slatSize = slat.size();
    char s;
    length -= getLetterNumber() * 2;
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < length; i++) {
        for (int j = 0; j< 20; j++) {
            index = qrand() % slatSize;
            s = slat.at(index);
            if (!isMoreThanLetter(passVector, s)) {
                passVector.append(s);
                break;
            }
        }
    }

    QString result;
    length = passLength->value();
    // first letter
    qsrand(QTime::currentTime().msec());
    do {
        index = qrand() % passVector.size();
        s = passVector.at(index);
        if (!isSpecialLetter(s)) {
            result.append(s);
            passVector.removeAt(index);
            break;
        }
    }while(true);

    // last letter
    qsrand(QTime::currentTime().msec());
    char last;
    do {
        index = qrand() % passVector.size();
        last = passVector.at(index);
        if (!isSpecialLetter(last)) {
            passVector.removeAt(index);
            break;
        }
    }while(true);

    length = passVector.size();
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < length; i++) {
        index = qrand() % passVector.size();
        s = passVector.at(index);
        passVector.removeAt(index);
        result.append(s);
    }

    result.append(last);
    return result;
}

void MainWindow::setApplication(const QApplication *app)
{
    applicaton = app;
}

void MainWindow::exit()
{
    if (applicaton) {
        applicaton->quit();
    }
}

QVector<char> MainWindow::createPasswordPrefix()
{
    QVector<char> result;
    QVector<char> slat;

    if (upperLetter->isChecked()) {
        for (char i = 'A'; i <= 'Z'; i++) {
            slat.append(i);
        }

        result += randLetter(slat);
    }

    slat.clear();
    if (lowerLetter->isChecked()) {
        for (char i = 'a'; i <= 'z'; i++) {
            slat.append(i);
        }

        result += randLetter(slat);
    }

    slat.clear();
    if (numberLetter->isChecked()) {
        for (char i = '0'; i <= '9'; i++) {
            slat.append(i);
        }

        result += randLetter(slat);
    }

    slat.clear();
    if (specialLetter->isChecked()) {
        for (size_t i = 0; i < SPECIAL_LETTER_LEN; i++) {
            slat.append(*(SPECIAL_LETTER + i));
        }

        result += randLetter(slat);
    }

    return result;
}

QVector<char> MainWindow::createPasswordSlat()
{
    QVector<char> result;
    if (upperLetter->isChecked()) {
        for (char i = 'A'; i <= 'Z'; i++) {
            result.append(i);
        }
    }

    if (lowerLetter->isChecked()) {
        for (char i = 'a'; i <= 'z'; i++) {
            result.append(i);
        }
    }

    if (numberLetter->isChecked()) {
        for (char i = '0'; i <= '9'; i++) {
            result.append(i);
        }
    }

    if (specialLetter->isChecked()) {
        for (size_t i = 0; i < SPECIAL_LETTER_LEN; i++) {
            result.append(*(SPECIAL_LETTER + i));
        }
    }

    return result;
}

int MainWindow::getLetterNumber() const
{
    int result = 0;
    if (upperLetter->isChecked()) {
        result++;
    }

    if (lowerLetter->isChecked()) {
        result++;
    }

    if (numberLetter->isChecked()) {
        result++;
    }

    if (specialLetter->isChecked()) {
        result++;
    }

    return result;
}

bool MainWindow::checkSettings() const
{
    return getLetterNumber() > 1;
}
