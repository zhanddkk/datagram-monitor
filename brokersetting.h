#ifndef BROKERSETTING_H
#define BROKERSETTING_H

#include <QWidget>
#include <QList>
#include <QSettings>
#include <QListWidgetItem>
#include "settingpage.h"

namespace Ui {
class BrokerSetting;
}

class BrokerSetting : public SettingPage
{
    Q_OBJECT

public:
    struct BrokerAttribute {
        QString tag;
        QString ip;
        int port;
        QString user;
        QString password;
        QString ca_path;
    };
    explicit BrokerSetting(QSettings &settings, QWidget *parent = nullptr);
    virtual ~BrokerSetting();

public slots:
    virtual void save_settings();
    virtual void reset_settings();
    void add_broker();
    void remove_broker();
    void update_tag();
    void update_ip();
    void update_port();
    void update_user();
    void update_password();
    void update_ca_path();
    void current_ba_changed(QListWidgetItem *current, QListWidgetItem *previous);
    void select_ca_file();

private:
    Ui::BrokerSetting *ui;
    struct BrokerAttribute *m_current_ba;
    QList<struct BrokerAttribute *> m_brokers;

    void load_settings();
};

#endif // BROKERSETTING_H
