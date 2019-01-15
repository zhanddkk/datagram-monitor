#include <QSpinBox>
#include <QFileDialog>
#include "brokersetting.h"
#include "ui_brokersetting.h"
#include "log.h"

BrokerSetting::BrokerSetting(QSettings &settings, Log &log, QWidget *parent) :
    SettingPage(settings, log, parent),
    ui(new Ui::BrokerSetting)
{
    m_current_ba = nullptr;
    ui->setupUi(this);
    const QIcon logo = QIcon::fromTheme("broker-setting", QIcon(":/images/brokers.png"));
    setWindowIcon(logo);
    load_settings();
    connect(ui->push_button_create_broker, &QPushButton::clicked, this, &BrokerSetting::add_broker);
    connect(ui->push_button_remove_broker, &QPushButton::clicked, this, &BrokerSetting::remove_broker);
    connect(ui->line_edit_tag, &QLineEdit::editingFinished, this, &BrokerSetting::update_tag);
    connect(ui->line_edit_ip, &QLineEdit::editingFinished, this, &BrokerSetting::update_ip);
    connect(ui->spin_box_port, &QSpinBox::editingFinished, this, &BrokerSetting::update_port);
    connect(ui->line_edit_user, &QLineEdit::editingFinished, this, &BrokerSetting::update_user);
    connect(ui->line_edit_password, &QLineEdit::editingFinished, this, &BrokerSetting::update_password);
    connect(ui->line_edit_ca, &QLineEdit::editingFinished, this, &BrokerSetting::update_ca_path);
    connect(ui->list_widget_broker, &QListWidget::currentItemChanged, this, &BrokerSetting::current_ba_changed);
    connect(ui->push_button_open_ca, &QPushButton::clicked, this, &BrokerSetting::select_ca_file);
}

BrokerSetting::~BrokerSetting()
{
    delete ui;
    for (QList<struct BrokerAttribute *>::iterator i = m_brokers.begin(); i != m_brokers.end(); i++) {
        BrokerAttribute *ba = *i;
        if (ba) {
            delete ba;
        }
    }
}

void BrokerSetting::save_settings()
{
    int _i = 0;

    m_settings->beginGroup("brokers");
    m_settings->remove("");
    m_settings->endGroup();
    m_settings->beginWriteArray("brokers");
    for (QList<struct BrokerAttribute *>::iterator i = m_brokers.begin(); i != m_brokers.end(); i++) {
        BrokerAttribute *ba = *i;
        m_settings->setArrayIndex(_i);
        m_settings->setValue("tag", ba->tag);
        m_settings->setValue("ip", ba->ip);
        m_settings->setValue("port", ba->port);
        m_settings->setValue("user", ba->user);
        m_settings->setValue("password", ba->password);
        m_settings->setValue("ca", ba->ca_path);
        _i++;
    }
    m_settings->endArray();
    m_settings->sync();
}

void BrokerSetting::reset_settings()
{
    ui->list_widget_broker->clear();
    for (QList<struct BrokerAttribute *>::iterator i = m_brokers.begin(); i != m_brokers.end(); i++) {
        BrokerAttribute *ba = *i;
        if (ba) {
            delete ba;
        }
    }
    m_brokers.clear();
    load_settings();
}

void BrokerSetting::load_settings()
{
    int len = m_settings->beginReadArray("brokers");
    for (int i = 0; i < len; i++) {
        m_settings->setArrayIndex(i);
        struct BrokerAttribute *ba = new struct BrokerAttribute;
        Q_ASSERT(ba != nullptr);
        ba->tag = m_settings->value("tag").toString();
        ba->ip = m_settings->value("ip").toString();
        ba->port = m_settings->value("port").toInt();
        if (ba->tag.isEmpty() || ba->ip.isEmpty()) {
            delete ba;
        } else {
            ba->user = m_settings->value("user").toString();
            ba->password = m_settings->value("password").toString();
            ba->ca_path = m_settings->value("ca").toString();
            m_brokers.append(ba);
        }
    }
    m_settings->endArray();
    for (QList<struct BrokerAttribute *>::iterator i = m_brokers.begin(); i != m_brokers.end(); i++) {
        BrokerAttribute *ba = *i;
        ui->list_widget_broker->addItem(ba->tag);
    }
    if (m_brokers.size() > 0) {
        ui->list_widget_broker->setCurrentRow(0);
    }
}

void BrokerSetting::add_broker()
{
    struct BrokerAttribute *ba = new struct BrokerAttribute;
    Q_ASSERT(ba != nullptr);
    ba->ip = "127.0.0.1";
    ba->port = 1883;
    ba->tag.sprintf("default_tag_%d", m_brokers.length());
    m_brokers.append(ba);
    ui->list_widget_broker->addItem(ba->tag);
    ui->list_widget_broker->setCurrentRow(m_brokers.indexOf(ba));
}

void BrokerSetting::remove_broker()
{
    if (m_current_ba) {
        int row = m_brokers.indexOf(m_current_ba);
        m_brokers.removeOne(m_current_ba);
        delete m_current_ba;
        m_current_ba = nullptr;
        ui->list_widget_broker->takeItem(row);
    }
}

void BrokerSetting::update_tag()
{
    if (m_current_ba) {
        QString content = ui->line_edit_tag->text();
        if (content.isEmpty()) {
            ui->line_edit_tag->setText(m_current_ba->tag);
        } else {
            m_current_ba->tag = content;
            ui->list_widget_broker->currentItem()->setText(content);
        }
    }
}

void BrokerSetting::update_ip()
{
    if (m_current_ba) {
        QString content = ui->line_edit_ip->text();
        if (content.isEmpty()) {
            ui->line_edit_ip->setText(m_current_ba->ip);
        } else {
            m_current_ba->ip = content;
        }
    }
}

void BrokerSetting::update_port()
{
    if (m_current_ba) {
        m_current_ba->port = ui->spin_box_port->value();
    }
}

void BrokerSetting::update_user()
{
    if (m_current_ba) {
        m_current_ba->user = ui->line_edit_user->text().trimmed();
    }
}

void BrokerSetting::update_password()
{
    if (m_current_ba) {
        m_current_ba->password = ui->line_edit_password->text().trimmed();
    }
}

void BrokerSetting::update_ca_path()
{
    if (m_current_ba) {
        m_current_ba->ca_path = ui->line_edit_ca->text().trimmed();
    }
}

void BrokerSetting::current_ba_changed(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous);
    if (current) {
        int index = ui->list_widget_broker->row(current);
        if (index >= 0) {
            m_current_ba = m_brokers[index];
            ui->line_edit_tag->setText(m_current_ba->tag);
            ui->line_edit_ip->setText(m_current_ba->ip);
            ui->spin_box_port->setValue(m_current_ba->port);
            ui->line_edit_user->setText(m_current_ba->user);
            ui->line_edit_password->setText(m_current_ba->password);
            ui->line_edit_ca->setText(m_current_ba->ca_path);
        }
    }
}

void BrokerSetting::select_ca_file()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CA File"), ui->line_edit_ca->text(), tr("CA File (*.crt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->line_edit_ca->setText(fileName);
        emit ui->line_edit_ca->editingFinished();
    }
}
