#include "textbox.h"

void TextBox::setText()
{
	QGraphicsSimpleTextItem* item = dynamic_cast<QGraphicsSimpleTextItem*>(m_textItem);
	if (item)
		m_textEdit->setText(item->text());
}

TextBox::TextBox() : QObject()
{
	m_paper = nullptr;
	m_textItem = nullptr;
	m_proxyText = nullptr;
	m_textEdit = nullptr;
}

TextBox::TextBox(Paper * paper, QGraphicsItem * textItem)
{
	m_paper = paper;
	m_textItem = textItem;
	m_proxyText = nullptr;
	m_textEdit = new QTextEdit();
	connect(m_textEdit, &QTextEdit::textChanged,
			this, &TextBox::textChanged);
	m_textEdit->move((int)m_textItem->scenePos().x() - 10, (int)m_textItem->scenePos().y());
	m_textEdit->setCursorWidth(3);
	setText();
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

	if (clickPosition.x() > m_textEdit->pos().x() &&
		clickPosition.x() < m_textEdit->width()   &&
		clickPosition.y() > m_textEdit->pos().y() &&
		clickPosition.y() < m_textEdit->height())
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
