#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "paperview.h"

class TextBox : public QObject
{
	Q_OBJECT

	QTextEdit* m_textEdit;
	QGraphicsProxyWidget* m_proxyText;

	void setText();
	QGraphicsSimpleTextItem* simpleText_cast(QGraphicsItem*);
	QGraphicsTextItem* text_cast(QGraphicsItem*);
	void getTextWidthAndHeight(int &width, int &height);

public:
	PaperView* m_paper;
	QGraphicsItem* m_textItem;

	TextBox();
	TextBox(PaperView *, QGraphicsItem *);
	~TextBox();
	bool amIClicked(QGraphicsSceneMouseEvent *event);
	void textChanged();
    void keyPressEvent(QKeyEvent *event);
};

#endif // TEXTBOX_H
