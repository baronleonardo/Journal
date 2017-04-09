#include "paper.h"

void Paper::onPenMousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && mode == InteractionMode::Drawing)
	{
		currentStrokePath = new QPainterPath(event->scenePos());
		currentStrokeItem = addPath(*currentStrokePath);
		currentStrokeItem->setPen(myPen);
		currentStrokeItem->setFlag(QGraphicsItem::ItemIsMovable);
		inTheMiddleOfAStroke = true;
		insertIntoSavableItems(currentStrokeItem);
	}
}

void Paper::onPenMouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton && inTheMiddleOfAStroke && mode == InteractionMode::Drawing)
		drawLineTo(event->scenePos());
}

void Paper::onPenMouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && inTheMiddleOfAStroke && mode == InteractionMode::Drawing)
	{
		drawLineTo(event->scenePos());
		inTheMiddleOfAStroke = false;
		delete currentStrokePath;
		emit itemModified(savableItems.find(currentStrokeItem).value(), currentStrokeItem);
	}
}
