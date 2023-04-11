#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_matButton01_clicked();

    void on_matButton11_clicked();

    void on_matButton21_clicked();

    void on_matButton31_clicked();

    void on_matButton02_clicked();

    void on_matButton12_clicked();

    void on_matButton22_clicked();

    void on_matButton32_clicked();

    void on_matButton03_clicked();

    void on_matButton13_clicked();

    void on_matButton23_clicked();

    void on_matButton33_clicked();

    void on_matButton04_clicked();

    void on_matButton14_clicked();

    void on_matButton24_clicked();

    void on_matButton34_clicked();

    void on_submitButton_clicked();

    void on_clearButton_clicked();

    void on_sendPathButton_clicked();

    void update_taskTextBrowser(QString text);


    void on_connectMqttButton_clicked();

    void on_disconnectMqttButton_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
