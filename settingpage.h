#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QWidget>
#include <QSettings>

class SettingPage: public QWidget
{
    Q_OBJECT
public:
    explicit SettingPage(QSettings &settings, QWidget *parent = nullptr);
    virtual ~SettingPage();

public slots:
    virtual void save_settings() = 0;
    virtual void reset_settings() = 0;

protected:
    QSettings *m_settings;
};

#endif // SETTINGPAGE_H
