#ifndef TEXT_BROWSER_H
#define TEXT_BROWSER_H

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

#endif // TEXT_BROWSER_H
