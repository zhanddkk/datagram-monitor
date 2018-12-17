#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Log;
class SettingDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    void log()

public slots:
    void setting_action_triggered();

private:
    Ui::MainWindow *ui;
    SettingDialog *m_setting_dlg;
    Log *m_log;
};

#endif // MAINWINDOW_H
