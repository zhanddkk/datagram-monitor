#ifndef APPLICATIONSETTING_H
#define APPLICATIONSETTING_H

#include <QWidget>
#include <QSettings>
#include <QSettings>
#include "settingpage.h"

namespace Ui {
class ApplicationSetting;
}

class ApplicationSetting : public SettingPage
{
    Q_OBJECT

public:
    explicit ApplicationSetting(QSettings &settings, Log &log, QWidget *parent = nullptr);
    virtual ~ApplicationSetting();

public slots:
    virtual void save_settings();
    virtual void reset_settings();

private:
    Ui::ApplicationSetting *ui;
};

#endif // APPLICATIONSETTING_H
