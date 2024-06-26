#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isAnimationStarted(false)
{

    ui->setupUi(this);
    font.setPointSize(14);
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));


    animation = new QPropertyAnimation(ui->warning, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(QRect(400, 580, 800, 50));
    animation->setEndValue(QRect(400, 40, 800, 50));

    holdTimer = new QTimer(this);
    holdTimer->setInterval(1000);
    holdTimer->setSingleShot(true);

    displayTimer = new QTimer(this);
    displayTimer->setInterval(100);  // 0.1 секунды
    displayTimer->setSingleShot(true);
    connect(displayTimer, &QTimer::timeout, this, &MainWindow::hidePlusLabel);

    connect(holdTimer, &QTimer::timeout, this, &MainWindow::onHoldTimeout);

    upgradeTimer = new QTimer(this);  // Новый таймер для апгрейда
    upgradeTimer->setInterval(1000);  // Каждую секунду

    connect(upgradeTimer, &QTimer::timeout, this, &MainWindow::onUpgradeTimeout);
    connect(ui->exit, &QAction::triggered, this, &MainWindow::on_exit_triggered);

    ui->pr1->setFont(font);
    ui->pr1->setText(QString::number(cost));
    ui->pr2->setFont(font);
    ui->pr2->setText(QString::number(cost2));
    ui->pr3->setFont(font);
    ui->pr3->setText(QString::number(cost3));

    ic1.addFile(":/images/checkmark3.png", QSize(100,100));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_clicked()
{
    ui->warning->hide();
    score += n;
    ui->score->setFont(font);
    ui->score->setText(QString::number(score));
    QString pls = "+" + QString::number(n);
    QFont ff;
    ff.setPointSize(24);
    ui->plus->setFont(ff);
    ui->plus->setText(pls);
    QPoint pp;
    pp.setX(rand() % 1000);
    pp.setY(rand() % 750);
    ui->plus->move(pp);
    ui->plus->show();
    displayTimer->start();
}

void MainWindow::on_pushButton_pressed()
{
    holdTimer->start();
}

void MainWindow::on_pushButton_released()
{
    holdTimer->stop();
    if (isAnimationStarted) {
        ui->warning->hide();
        animation->stop();
        isAnimationStarted = false;
    }
}

void MainWindow::onHoldTimeout()
{
    ui->warning->show();
    QFont f1;
    f1.setPointSize(24);
    ui->warning->setFont(f1);
    ui->warning->setText("Play fair!");
    animation->start();
    isAnimationStarted = true;
}

void MainWindow::hidePlusLabel()
{
    ui->plus->hide();
}

void MainWindow::on_upgrade_clicked()
{
    bool ok;
    long long c1;
    c1 = (ui->pr1->text()).toLongLong(&ok);
    if (score >= c1) {
        score -= c1;
        ui->score->setText(QString::number(score));
        c1 *= 2;
        ui->pr1->setText(QString::number(c1));
        n *= 2;
    }else{
        QFont f3;
        long long a=(c1-score);
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("You need "+QString::number(a));
        animation->start();
        if(animation->currentTime()==3000){
            ui->warning->hide();
        }
    }
}

void MainWindow::on_upgrade2_clicked()
{
    bool ok;
    long long c2;
    c2 = (ui->pr2->text()).toLongLong(&ok);
    if(upgr && score>=c2){
        upgr=false;
        if (score >= c2) {
            score -= c2;
            ui->score->setText(QString::number(score));
            c2 *= 2;
            ui->pr2->setText(QString::number(c2));


            if (!upgradeTimer->isActive()) {
                upgradeTimer->start();  // Запускаем таймер, если он еще не запущен
            }
        }

        ui->upgrade2->setText("");
        ui->upgrade2->setIcon(ic1);
        ui->upgrade2->setIconSize(QSize(81,81));
        ui->pr2->setText("-");
        ui->autoplus->setFont(font);
        ui->autoplus->setText(QString::number(k)+" auto");
        aut=true;
    }else{
        QFont f3;
        long long a=(c2-score);
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("You need "+QString::number(a));
        animation->start();
        if(animation->currentTime()==3000){
            ui->warning->hide();
        }
    }
}

void MainWindow::on_upgrade3_clicked()
{   if(aut){
    bool ok;
        long long c3;
        c3 = (ui->pr3->text()).toLongLong(&ok);
        if (score >= c3) {
            score -= c3;
            ui->score->setText(QString::number(score));
            c3 *= 2;
            ui->pr3->setText(QString::number(c3));
            k *= 2;
            ui->autoplus->setFont(font);
            ui->autoplus->setText(QString::number(k)+" auto");
        }else{
            QFont f3;
            long long a=(c3-score);
            f3.setPointSize(24);
            ui->warning->show();
            ui->warning->setFont(f3);
            ui->warning->setText("You need "+QString::number(a));
            animation->start();
            if(animation->currentTime()==3000){
                ui->warning->hide();
            }
        }
    }else{
        QFont f3;
        f3.setPointSize(24);
        ui->warning->show();
        ui->warning->setFont(f3);
        ui->warning->setText("Buy auto");
        animation->start();
        if(animation->currentTime()==3000){
            ui->warning->hide();
        }
    }
}

void MainWindow::onUpgradeTimeout()
{
    score += k;  // Увеличиваем score на k каждую секунду
    ui->score->setText(QString::number(score));
}
