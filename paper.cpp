#include <QtWidgets>
#include <iostream>

#include "paper.h"

Paper::Paper(QWidget *parent) : QGraphicsScene(parent), mCellSize(15, 15)
{
	currentTool = nullptr;
}

// Efficiently draws a grid in the background.
// For more information: http://www.qtcentre.org/threads/5609-Drawing-grids-efficiently-in-QGraphicsScene?p=28905#post28905
void Paper::drawBackground(QPainter *painter, const QRectF &rect)
{
	qreal left = int(rect.left()) - (int(rect.left()) % mCellSize.width());
	qreal top = int(rect.top()) - (int(rect.top()) % mCellSize.height());

	QVarLengthArray<QLineF, 100> lines;

	for (qreal x = left; x < rect.right(); x += mCellSize.width())
		lines.append(QLineF(x, rect.top(), x, rect.bottom()));
	for (qreal y = top; y < rect.bottom(); y += mCellSize.height())
		lines.append(QLineF(rect.left(), y, rect.right(), y));
	QPen myPen(QColor(190,190,190,50));
	painter->setPen(myPen);
	painter->drawLines(lines.data(), lines.size());
}

void Paper::setTool(Tool* p_tool)
{
	if(currentTool)
		delete currentTool;

	currentTool = p_tool;
}

void Paper::setPaperID(QUuid id)
{
	this->id = id;
}

void Paper::setPaperID()
{
	id = QUuid::createUuid();
}

void Paper::addSavableItem(QGraphicsItem *item, QUuid id)
{
	addItem(item);
	savableItems.insert(item, id);
}

void Paper::emitItemModified(QGraphicsItem *item)
{
	emit itemModified(savableItems.find(item).value(), item);
}

void Paper::emitItemDeleted(QGraphicsItem *item)
{
	emit itemDeleted(savableItems.find(item).value(), item);
}

void Paper::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mousePressEvent(event);
}

void Paper::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mouseMoveEvent(event);
}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mouseReleaseEvent(event);
}

void Paper::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mouseDoubleClickEvent(event);
}

void Paper::keyPressEvent(QKeyEvent *event)
{
    if (currentTool) currentTool->keyPressEvent(event);
}

void Paper::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void Paper::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	QGraphicsScene::dropEvent(event);

	if(event->mimeData()->hasUrls()) //TODO: make sure it's a photo and add support to all file types ever
		onMediaFileDropEvent(event);

	else if (event->mimeData()->hasHtml())
		onTextDropEvent(event);

	else if(event->mimeData()->hasText())
		onSimpleTextDropEvent(event);

	else return;
}

void Paper::roundToNearestCell(int &x, int &y, QPointF pos)
{
	x = round(pos.x() / mCellSize.width()) * mCellSize.width();
	y = round(pos.y() / mCellSize.height()) * mCellSize.height();
}

void Paper::deleteItem(QGraphicsItem *item)
{
	emitItemDeleted(item);
	removeItem(item);
	savableItems.remove(item);
}

void Paper::insertIntoSavableItems(QGraphicsItem *item)
{
	savableItems.insert(item, QUuid::createUuid());
}

void Paper::graphicsScenePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mousePressEvent(event);
}

void Paper::graphicsSceneMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);
}

void Paper::graphicsSceneReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);
}

void Paper::graphicsSceneDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseDoubleClickEvent(event);
}


void Paper::initializeAndAddItemToScene(QGraphicsItem *item, QPointF position)
{
	item->setFlag(QGraphicsItem::ItemIsMovable);

	// snaps to nearest grid line
	int x, y;
	roundToNearestCell(x, y, position);
	item->setPos(x, y);

	addItem(item);
	insertIntoSavableItems(item);
}

void Paper::onMediaFileDropEvent(QGraphicsSceneDragDropEvent *event)
{
	QString itemPath = event->mimeData()->urls()[0].toLocalFile();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(* new QPixmap(itemPath));
	initializeAndAddItemToScene(item, event->scenePos());
	emit itemModified(savableItems.find(item).value(), item, itemPath);
}

void Paper::onSimpleTextDropEvent(QGraphicsSceneDragDropEvent *event)
{
	QGraphicsSimpleTextItem* item = new QGraphicsSimpleTextItem(event->mimeData()->text());
	initializeAndAddItemToScene(item, event->scenePos());
	emit itemModified(savableItems.find(item).value(), item);
}

void Paper::onTextDropEvent(QGraphicsSceneDragDropEvent *event)
{
	QGraphicsTextItem* item = new QGraphicsTextItem();
	item->setHtml(event->mimeData()->html());
	initializeAndAddItemToScene(item, event->scenePos());
	emit itemModified(savableItems.find(item).value(), item);
}
