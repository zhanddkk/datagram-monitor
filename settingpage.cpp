#include "settingpage.h"
#include "log.h"

SettingPage::SettingPage(QSettings &settings, Log &log, QWidget *parent) : QWidget(parent)
{
    m_settings = &settings;
    m_log = &log;
}

SettingPage::~SettingPage()
{

}
