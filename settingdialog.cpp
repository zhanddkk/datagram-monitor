#include <QIcon>

#include "settingdialog.h"
#include "ui_settingdialog.h"

#include "applicationsetting.h"
#include "brokersetting.h"
#include "log.h"

SettingDialog::SettingDialog(Log &log, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    const QIcon logo = QIcon::fromTheme("setting-dlg-logo", QIcon(":/images/settings.png"));
    setWindowIcon(logo);

    m_setting_data = new QSettings("config.ini", QSettings::IniFormat);
    m_log = &log;

    ApplicationSetting *app_setting_page = new ApplicationSetting(*m_setting_data, log, this);
    m_setting_pages.append(app_setting_page);

    BrokerSetting *broker_setting_page = new BrokerSetting(*m_setting_data, log, this);
    m_setting_pages.append(broker_setting_page);

    for (QVector<SettingPage *>::iterator i = m_setting_pages.begin(); i != m_setting_pages.end(); i++) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon((*i)->windowIcon());
        item->setText((*i)->windowTitle());
        ui->list_widget_setting_items->addItem(item);
        ui->stacked_widget_setting_pages->addWidget(*i);
    }
    ui->list_widget_setting_items->setCurrentRow(0);
    connect(ui->list_widget_setting_items, &QListWidget::currentItemChanged, this, &SettingDialog::current_item_change);
    connect(ui->push_button_cancel, &QPushButton::clicked, this, &SettingDialog::reject);
    connect(ui->push_button_ok, &QPushButton::clicked, this, &SettingDialog::accept);
    connect(ui->push_button_apply, &QPushButton::clicked, this, &SettingDialog::apply);
}

SettingDialog::~SettingDialog()
{
    delete m_setting_data;
    delete ui;
}

void SettingDialog::current_item_change(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current == nullptr) {
        current = previous;
    }
    ui->stacked_widget_setting_pages->setCurrentIndex(ui->list_widget_setting_items->row(current));
}

void SettingDialog::apply()
{
    for (QVector<SettingPage *>::iterator i = m_setting_pages.begin(); i != m_setting_pages.end(); i++) {
        (*i)->save_settings();
    }
}

void SettingDialog::accept()
{
    apply();
    QDialog::accept();
}

void SettingDialog::reject()
{
    for (QVector<SettingPage *>::iterator i = m_setting_pages.begin(); i != m_setting_pages.end(); i++) {
        (*i)->reset_settings();
    }
    QDialog::reject();
}
