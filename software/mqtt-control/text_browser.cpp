#include "text_browser.h"

TextBrowser::TextBrowser()
{

}

void TextBrowser::emitTaskTextBrowser(QString text)
{
    emit signalTaskTextBrowser(text);
}

void TextBrowser::emitFeedbackTextBrowser(QString text)
{
    emit signalFeeadBackTextBrowser(text);
}


