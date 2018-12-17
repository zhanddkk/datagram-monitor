#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QTextEdit>

class Log : public QObject
{
    Q_OBJECT
public:
enum LogLevel {
    E_LEVEL_PRINT= 0,
    E_LEVEL_INFO,
    E_LEVEL_WARNING,
    E_LEVEL_ERROR
};
    explicit Log(QTextEdit &editor, QObject *parent = nullptr);
    ~Log();

    void info(const char *fmt, ...);
    void warning(const char *fmt, ...);
    void error(const char *fmt, ...);
    void print(const char *fmt, ...);

signals:
    void put_log(int level, const QString *log);

private:
    bool m_is_print_block;
    QTextEdit *m_editor;

private slots:
    void process_log(int level, const QString *str);
};

#endif // LOG_H
