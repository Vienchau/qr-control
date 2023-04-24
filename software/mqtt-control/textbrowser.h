#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QObject>
#include <QString>

class TextBrowser: public QObject
{
    Q_OBJECT
public:
    TextBrowser();

    void emitTaskTextBrowser(QString text);
    void emitFeedbackTextBrowser(QString text);

signals:
    void signalTaskTextBrowser(QString text);
    void signalFeeadBackTextBrowser(QString text);
};

#endif // TEXTBROWSER_H
