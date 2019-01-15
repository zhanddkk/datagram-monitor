#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingdialog.h"
#include "log.h"

#if defined(Q_OS_WIN32)
#define LOG_FONT_FAMILY     "Consolas"
#elif defined(Q_OS_MAC)
#define LOG_FONT_FAMILY     "Monaco"
#elif define(Q_OS_LINUX)
#define LOG_FONT_FAMILY     "Courier"
#else
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QIcon logo = QIcon::fromTheme("logo", QIcon(":/images/logo.png"));
    setWindowIcon(logo);

    m_log = new Log(*ui->text_edit_sys_log, this);
    m_setting_dlg = new SettingDialog(*m_log, this);
#ifdef LOG_FONT_FAMILY
    ui->text_edit_sys_log->setFontFamily(LOG_FONT_FAMILY);
#endif
    connect(ui->action_setting, &QAction::triggered, this, &MainWindow::setting_action_triggered);
    for (uint32_t i = 0; i < 10; i++)
    {
        m_log->print("%d, ", i);
    }
    m_log->print("\n");
    m_log->info("Datagram Monitor Utility Ver 0.0.0.1");
    m_log->warning("Datagram Monitor Utility Ver 0.0.0.1");
    m_log->error("Datagram Monitor Utility Ver 0.0.0.1");
    for (uint32_t i = 0; i < 10; i++)
    {
        m_log->print("%d, ", i);
    }
    m_log->print("\n");
    m_log->warning("===========End==========");
}

MainWindow::~MainWindow()
{
    delete m_log;
    delete m_setting_dlg;
    delete ui;
}

void MainWindow::setting_action_triggered()
{
    m_setting_dlg->exec();
}
