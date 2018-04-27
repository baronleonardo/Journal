#include "texttool.h"
#include "paperview.h"

TextTool::TextTool()
{
	m_paper = nullptr;
	selectedItem = nullptr;
	m_textBox = nullptr;
}

TextTool::~TextTool()
{
}

void TextTool::keyPressEvent(QKeyEvent*)
{

}

void TextTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->button() != Qt::LeftButton)
		return;

	handleMousePressWhileEditingText(event);
	selectedItem = m_paper->addSimpleText("");
	selectedItem->setPos(event->scenePos());
	selectedItem->setFlag(QGraphicsItem::ItemIsMovable);
	m_textBox = std::unique_ptr<TextBox>( new TextBox(m_paper, selectedItem) );
}

void TextTool::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{

}

void TextTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	m_paper->graphicsSceneReleaseEvent(event);
}

void TextTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	m_paper->graphicsSceneDoubleClickEvent(event);
}

void TextTool::deselect()
{
	if(selectedItem)
		m_paper->emitItemModified(selectedItem);

	m_paper = nullptr;
	selectedItem = nullptr;
	m_textBox = nullptr;
}

void TextTool::handleMousePressWhileEditingText(QGraphicsSceneMouseEvent *event)
{
	if (! m_textBox)
		return;

	if (m_textBox && m_textBox->amIClicked(event))
		return;

	if(selectedItem)
		m_paper->emitItemModified(selectedItem);

	m_textBox = nullptr;
}
