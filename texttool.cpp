#include "texttool.h"

TextTool::TextTool(Paper* paper)
{
	m_paper = paper;
	selectedItem = nullptr;
	m_textBox = nullptr;
}

TextTool::~TextTool()
{
	if (m_textBox) delete m_textBox;
}

void TextTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->button() != Qt::LeftButton)
		return;

	handleMousePressWhileEditingText(event);
	//selectedItem = addText("");
	selectedItem = m_paper->addSimpleText("");
	m_paper->insertIntoSavableItems(selectedItem);
	selectedItem->setPos(event->scenePos());
	selectedItem->setFlag(QGraphicsItem::ItemIsMovable);
	m_textBox = new TextBox(m_paper, selectedItem);
}

void TextTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

void TextTool::handleMousePressWhileEditingText(QGraphicsSceneMouseEvent *event)
{
	if (! m_textBox)
		return;

	if (m_textBox && m_textBox->amIClicked(event))
		return;

	if(m_textBox)
		delete m_textBox;
}

//void TextTool::keyPressEvent(QKeyEvent *event)
//{
//    m_textBox->keyPressEvent(event);
//}
