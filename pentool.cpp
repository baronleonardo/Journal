#include "pentool.h"

PenTool::PenTool(QGraphicsScene* paper) : currentStrokeBoundingRectangle(QPoint(), QPoint())
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
	currentStrokeBoundingRectangle = BoundingRectangle(event->scenePos(), event->scenePos());
}

void PenTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton && inTheMiddleOfAStroke)
	{
		drawLineTo(event->scenePos());
		currentStrokeBoundingRectangle.updateRectangle(event->scenePos());
	}
}

void PenTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && inTheMiddleOfAStroke)
	{
		drawLineTo(event->scenePos());
		currentStrokeBoundingRectangle.updateRectangle(event->scenePos());
		inTheMiddleOfAStroke = false;
		delete currentStrokePath;
		currentStrokePath = nullptr;
		QPixmap pixmap = pathToPixmap(currentStrokeItem);
		m_paper->deleteItem(currentStrokeItem);
		QGraphicsPixmapItem* pixmapItem = m_paper->addPixmap(pixmap);
		m_paper->insertIntoSavableItems(pixmapItem);
		m_paper->emitItemModified(pixmapItem);
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

QPixmap PenTool::pathToPixmap(const QGraphicsPathItem* pathItem)
{
	// + 2 is a little padding to avoid having the stroke cut off
	QPixmap pixmap((int)currentStrokeBoundingRectangle.bottomLeft.x() + 2,
				   (int)currentStrokeBoundingRectangle.bottomLeft.y() + 2);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.setRenderHint( QPainter::Antialiasing );
	painter.setPen( m_qpen );
	painter.drawPath(pathItem->path());
	painter.end();
	return pixmap;
}

void PenTool::keyPressEvent(QKeyEvent *)
{

}

BoundingRectangle::BoundingRectangle(QPointF p_upperRight, QPointF p_bottomLeft) :
	upperRight(p_upperRight), bottomLeft(p_bottomLeft)
{

}

int BoundingRectangle::width()
{
	return (int)(bottomLeft.x() - upperRight.x());
}

int BoundingRectangle::height()
{
	return (int)(bottomLeft.y() - upperRight.y());
}

void BoundingRectangle::updateRectangle(QPointF point)
{
	if (point.x() < upperRight.x()) upperRight.setX(point.x());
	if (point.y() < upperRight.y()) upperRight.setY(point.y());
	if (point.y() > bottomLeft.y()) bottomLeft.setY(point.y());
	if (point.x() > bottomLeft.x()) bottomLeft.setX(point.x());
}
