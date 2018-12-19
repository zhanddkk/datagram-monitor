#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QVector>
#include <QListWidgetItem>
#include <QSettings>

#include "settingpage.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

private:
    Ui::SettingDialog *ui;
    QSettings *m_setting_data;
    QVector<SettingPage *> m_setting_pages;

private slots:
    void current_item_change(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // SETTINGDIALOG_H
