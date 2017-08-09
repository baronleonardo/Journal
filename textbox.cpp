#include "textbox.h"

void TextBox::setText()
{
	if (QGraphicsSimpleTextItem* item = simpleText_cast(m_textItem))
		m_textEdit->setText(item->text());
	else if (QGraphicsTextItem* item = text_cast(m_textItem))
		m_textEdit->setDocument(item->document());
}

QGraphicsTextItem* TextBox::text_cast(QGraphicsItem* textItem)
{
	return dynamic_cast<QGraphicsTextItem*>(textItem);
}

void TextBox::getTextWidthAndHeight(int &width, int &height)
{
	if(!m_textItem)
		return;

	if (QGraphicsSimpleTextItem* item = simpleText_cast(m_textItem))
		width = (int)item->boundingRect().size().width() + 20;
	else if (QGraphicsTextItem* item = text_cast(m_textItem))
		width = (int)item->document()->documentLayout()->documentSize().width() + 10;

	height = (int)m_textItem->boundingRect().size().height() + 10;
}

QGraphicsSimpleTextItem* TextBox::simpleText_cast(QGraphicsItem* textItem)
{
	return dynamic_cast<QGraphicsSimpleTextItem*>(textItem);
}

TextBox::TextBox() : QObject()
{
	m_paper = nullptr;
	m_textItem = nullptr;
	m_proxyText = nullptr;
	m_textEdit = nullptr;
}

TextBox::TextBox(Paper* paper, QGraphicsItem* textItem)
{
	m_paper = paper;
	m_textItem = textItem;
	m_proxyText = nullptr;
	m_textEdit = new QTextEdit();
	connect(m_textEdit, &QTextEdit::textChanged,
			this, &TextBox::textChanged);
	m_textEdit->move((int)m_textItem->scenePos().x(), (int)m_textItem->scenePos().y());
	m_textEdit->setCursorWidth(3);
	setText();

	int width = 0, height = 0;
	getTextWidthAndHeight(width, height);
	m_textEdit->resize(width, height);

    m_textEdit->setFocus();
	m_proxyText = m_paper->addWidget(m_textEdit);
    m_proxyText->setFocus();
}

TextBox::~TextBox()
{
	if (m_proxyText)
		m_paper->removeItem(m_proxyText);

	if (m_textEdit)
		delete m_textEdit;
}

bool TextBox::amIClicked(QGraphicsSceneMouseEvent *event)
{
	QPointF clickPosition = event->scenePos();

	qreal x = m_textEdit->pos().x();
	qreal y = m_textEdit->pos().y();
	qreal width = m_textEdit->width();
	qreal height = m_textEdit->height();

	if (clickPosition.x() > x			&&
		clickPosition.x() < x + width   &&
		clickPosition.y() > y			&&
		clickPosition.y() < y + height)
		return true;

	return false;
}

void TextBox::textChanged()
{
	QGraphicsTextItem* selectedTextItem = dynamic_cast<QGraphicsTextItem*>(m_textItem);

	if(selectedTextItem)
	{
		selectedTextItem->setDocument(m_textEdit->document());
		return;
	}

	QGraphicsSimpleTextItem* selectedSimpleTextItem = dynamic_cast<QGraphicsSimpleTextItem*>(m_textItem);

	if(selectedSimpleTextItem)
		selectedSimpleTextItem->setText(m_textEdit->document()->toPlainText());
}
