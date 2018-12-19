#include <QIcon>
#include "applicationsetting.h"
#include "ui_applicationsetting.h"

ApplicationSetting::ApplicationSetting(QSettings &settings, QWidget *parent) :
    SettingPage(settings, parent),
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
