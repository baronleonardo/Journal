#include "selecttool.h"
#include "paperview.h"

bool SelectTool::isAStroke(QGraphicsItem *item)
{
	QGraphicsPathItem* tmp = dynamic_cast<QGraphicsPathItem*>(item);
	return (tmp == nullptr) ? false : true;
}

SelectTool::SelectTool()
{
	m_paper = nullptr;
    selectedItem = nullptr;
	m_textBox = nullptr;
	m_dragged = nullptr;
}

SelectTool::~SelectTool()
{
}

void SelectTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() != Qt::LeftButton)
		return;

	if(m_textBox && !m_textBox->amIClicked(event))
	{
		m_paper->emitItemModified(m_textBox->m_textItem);
		m_textBox = nullptr;
		return;
	}

	selectedItem = m_paper->itemAt(event->scenePos(), QTransform());
	m_dragged = selectedItem;

	if (m_dragged)
		m_dragOffset = event->scenePos() - m_dragged->pos();

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
		m_paper->emitItemModified(selectedItem);
		m_textBox = nullptr;
	}

	selectedItem = m_paper->itemAt(event->scenePos(), QTransform());
	QGraphicsTextItem* selectedTextItem = dynamic_cast<QGraphicsTextItem*>(selectedItem);

	if(selectedTextItem)
	{
		m_textBox = std::unique_ptr<TextBox>( new TextBox(m_paper, selectedItem) );
		return;
	}

	QGraphicsSimpleTextItem* selectedSimpleTextItem = dynamic_cast<QGraphicsSimpleTextItem*>(selectedItem);

	if(selectedSimpleTextItem)
	{
		m_textBox = std::unique_ptr<TextBox>( new TextBox(m_paper, selectedItem) );
		return;
	}
}

void SelectTool::deselect()
{
	if(m_textBox)
	{
		m_paper->emitItemModified(selectedItem);
	}

	m_paper = nullptr;
	selectedItem = nullptr;
	m_textBox = nullptr;
	m_dragged = nullptr;
}

void SelectTool::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
		if (selectedItem)
		{
			m_paper->deleteItem(selectedItem);
			selectedItem = nullptr;
        }
}

