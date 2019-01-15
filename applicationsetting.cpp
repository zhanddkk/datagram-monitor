#include <QIcon>
#include "applicationsetting.h"
#include "ui_applicationsetting.h"
#include "log.h"

ApplicationSetting::ApplicationSetting(QSettings &settings, Log &log, QWidget *parent) :
    SettingPage(settings, log, parent),
    ui(new Ui::ApplicationSetting)
{
    ui->setupUi(this);
    const QIcon logo = QIcon::fromTheme("broker-setting", QIcon(":/images/applications.png"));
    setWindowIcon(logo);
}

ApplicationSetting::~ApplicationSetting()
{
    delete ui;
}

void ApplicationSetting::save_settings()
{

}

void ApplicationSetting::reset_settings()
{

}
