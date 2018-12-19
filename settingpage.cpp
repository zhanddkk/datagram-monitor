#include "settingpage.h"

SettingPage::SettingPage(QSettings &settings, QWidget *parent) : QWidget(parent)
{
    m_settings = &settings;
}

SettingPage::~SettingPage()
{

}
