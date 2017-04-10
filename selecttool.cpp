#include "selecttool.h"

bool SelectTool::isAStroke(QGraphicsItem *item)
{
	QGraphicsPathItem* tmp = dynamic_cast<QGraphicsPathItem*>(item);
	return (tmp == nullptr) ? false : true;
}

SelectTool::SelectTool(Paper* paper)
{
	m_paper = paper;
    selectedItem = nullptr;
	m_textBox = nullptr;
	m_dragged = nullptr;
}

SelectTool::~SelectTool()
{
	if (m_textBox) delete m_textBox;
}

void SelectTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() != Qt::LeftButton)
		return;

	selectedItem = m_paper->itemAt(event->scenePos(), QTransform());
	m_dragged = selectedItem;

	if (m_dragged)
		m_dragOffset = event->scenePos() - m_dragged->pos();

	if(m_textBox && !m_textBox->amIClicked(event))
	{
		delete m_textBox;
		m_textBox = nullptr;
		return;
	}

	m_paper->graphicsScenePressEvent(event);
}

void SelectTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	// Ensure that the item's offset from the mouse cursor stays the same.
	if (m_dragged)
		m_dragged->setPos(event->scenePos() - m_dragOffset);
	else
		m_paper->graphicsSceneMoveEvent(event);
}

void SelectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_dragged && ! isAStroke(m_dragged))
	{
		int x, y;
		m_paper->roundToNearestCell(x, y, m_dragged->scenePos());
		m_dragged->setPos(x, y);
	}

	if(m_dragged)
		m_paper->emitItemModified(m_dragged);

	m_dragged = nullptr;

	m_paper->graphicsSceneReleaseEvent(event);
}

void SelectTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_textBox && !m_textBox->amIClicked(event))
	{
		delete m_textBox;
		m_textBox = nullptr;
	}

	selectedItem = m_paper->itemAt(event->scenePos(), QTransform());
	QGraphicsTextItem* selectedTextItem = dynamic_cast<QGraphicsTextItem*>(selectedItem);

	if(selectedTextItem)
	{
		m_textBox = new TextBox(m_paper, selectedItem);
		return;
	}

	QGraphicsSimpleTextItem* selectedSimpleTextItem = dynamic_cast<QGraphicsSimpleTextItem*>(selectedItem);

	if(selectedSimpleTextItem)
	{
		m_textBox = new TextBox(m_paper, selectedItem);
		return;
	}

	//m_paper->graphicsSceneDoubleClickEvent(event);
}

void SelectTool::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Delete)
    {
        if (selectedItem){
            // Still need to remove the "selectedItem" from "savableItems"
            delete selectedItem;
        }
    }
}

