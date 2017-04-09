#include "pentool.h"

PenTool::PenTool(QGraphicsScene* paper)
{
	m_paper = dynamic_cast<Paper*>(paper);
	inTheMiddleOfAStroke = false;
	currentStrokePath = nullptr;
	currentStrokeItem = nullptr;
	m_width = 3;
	m_color = Qt::black;
	m_qpen = QPen(m_color, m_width,
				 Qt::SolidLine, Qt::RoundCap,
				 Qt::RoundJoin);
}

void PenTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	currentStrokePath = new QPainterPath(event->scenePos());
	currentStrokeItem = m_paper->addPath(*currentStrokePath);
	currentStrokeItem->setPen(m_qpen);
	currentStrokeItem->setFlag(QGraphicsItem::ItemIsMovable);
	inTheMiddleOfAStroke = true;
	m_paper->insertIntoSavableItems(currentStrokeItem);
}

void PenTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton && inTheMiddleOfAStroke)
		drawLineTo(event->scenePos());
}

void PenTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && inTheMiddleOfAStroke)
	{
		drawLineTo(event->scenePos());
		inTheMiddleOfAStroke = false;
		delete currentStrokePath;
		currentStrokePath = nullptr;
		m_paper->emitItemModified(currentStrokeItem);
	}
}

void PenTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	m_paper->graphicsSceneDoubleClickEvent(event);
}

void PenTool::drawLineTo(const QPointF &endPoint)
{
	currentStrokePath->lineTo(endPoint);
	currentStrokeItem->setPath(*currentStrokePath);
}

void PenTool::keyPressEvent(QKeyEvent *event)
{

}
