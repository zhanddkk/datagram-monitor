#include "log.h"
#include <QBrush>
#include <QScrollBar>
#include <stdio.h>

Log::Log(QTextEdit &editor, QObject *parent) : QObject(parent)
{
    m_editor = &editor;
    m_is_print_block = true;
    connect(this, &Log::put_log, this, &Log::process_log);
}

Log::~Log()
{

}

void Log::info(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    QString *str = new QString;
    str->vsprintf(fmt, args);
    emit put_log(E_LEVEL_INFO, str);
    va_end(args);
}

void Log::warning(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    QString *str = new QString;
    str->vsprintf(fmt, args);
    emit put_log(E_LEVEL_WARNING, str);
    va_end(args);
}

void Log::error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    QString *str = new QString;
    str->vsprintf(fmt, args);
    emit put_log(E_LEVEL_ERROR, str);
    va_end(args);
}

void Log::print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    QString *str = new QString;
    str->vsprintf(fmt, args);
    emit put_log(E_LEVEL_PRINT, str);
    va_end(args);
}

void Log::process_log(int level, const QString *str)
{
    if (str == nullptr)
        return;
    if (!str->isEmpty()) {
        bool isLineBreak = true;
        bool isColorChange = true;

        QTextCursor tmp_cursor(m_editor->document());
        QTextCursor cursor = m_editor->textCursor();
        QScrollBar *vbar = m_editor->verticalScrollBar();

        const bool atBottom = m_editor->isReadOnly() ?
            vbar->value() >= vbar->maximum() :
            m_editor->textCursor().atEnd();

        QTextCharFormat old_char_format = m_editor->currentCharFormat();
        QTextCharFormat tmp_char_format = old_char_format;

        QColor color;
        QString tag;
        switch (level)
        {
        case E_LEVEL_INFO:
            tag = "[   INFO]: ";
            color.setRgb(0, 180, 0);
            m_is_print_block = false;
            break;
        case E_LEVEL_WARNING:
            tag = "[WARNING]: ";
            color.setRgb(200, 180, 0);
            m_is_print_block = false;
            break;
        case E_LEVEL_ERROR:
            tag = "[  ERROR]: ";
            color.setRgb(200, 0, 0);
            m_is_print_block = false;
            break;
        default:
            isLineBreak = !m_is_print_block;
            m_is_print_block = true;
            isColorChange = false;
            break;
        }
        tmp_cursor.movePosition(QTextCursor::End);
        tmp_cursor.beginEditBlock();
        if (isLineBreak) {
            // add new block
            if (!m_editor->document()->isEmpty())
                tmp_cursor.insertBlock(cursor.blockFormat(), cursor.charFormat());
        }
        if (!tag.isEmpty()) {
            tmp_cursor.insertText(tag);
        }
        if (isColorChange) {
            tmp_char_format.setForeground(QBrush(color));
        }
        tmp_cursor.setCharFormat(tmp_char_format);
        tmp_cursor.insertText(*str);
        if (!m_editor->textCursor().hasSelection())
            m_editor->setCurrentCharFormat(old_char_format);
        tmp_cursor.endEditBlock();
        if (atBottom)
            vbar->setValue(vbar->maximum());
    }
    delete str;
}
