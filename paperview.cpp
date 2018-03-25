#include "paperview.h"
#include "papercontroller.h"

PaperView::PaperView(PaperController* parent) : QGraphicsScene(parent),  mCellSize(15, 15), controller(parent)
{
}

PaperView::PaperView(PaperController* parent, QVector<QGraphicsItem*> items) : QGraphicsScene(parent),  mCellSize(15, 15), controller(parent)
{
	for(int i = 0; i < items.size(); i++)
		addItem(items[i]);
}

void PaperView::setTool(Tool* tool)
{
	currentTool = std::unique_ptr<Tool>(tool);
}

void PaperView::deleteItem(QGraphicsItem* item)
{
	removeItem(item);
	controller->deleteItem(item);
}

void PaperView::emitItemModified(QGraphicsItem* item)
{
	controller->emitItemModified(item);
}

void PaperView::emitItemModified(QGraphicsItem* item, QString itemPath)
{
	controller->emitItemModified(item, itemPath);
}

void PaperView::emitItemDeleted(QGraphicsItem* item)
{
	controller->emitItemDeleted(item);
}

// Draws a grid in the background.
// http://www.qtcentre.org/threads/5609-Drawing-grids-efficiently-in-QGraphicsScene?p=28905#post28905
void PaperView::drawBackground(QPainter *painter, const QRectF &rect)
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

void PaperView::roundToNearestCell(int &x, int &y, QPointF pos)
{
	x = round(pos.x() / mCellSize.width()) * mCellSize.width();
	y = round(pos.y() / mCellSize.height()) * mCellSize.height();
}

void PaperView::initializeAndAddItemToScene(QGraphicsItem *item, QPointF position)
{
	item->setFlag(QGraphicsItem::ItemIsMovable);

	// snaps to nearest grid line
	int x, y;
	roundToNearestCell(x, y, position);
	item->setPos(x, y);

	addItem(item);
	controller->emitItemModified(item);
}

void PaperView::graphicsScenePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mousePressEvent(event);
}

void PaperView::graphicsSceneMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);
}

void PaperView::graphicsSceneReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);
}

void PaperView::graphicsSceneDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseDoubleClickEvent(event);
}

void PaperView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mousePressEvent(event);
}

void PaperView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mouseMoveEvent(event);
}

void PaperView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mouseReleaseEvent(event);
}

void PaperView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if (currentTool) currentTool->mouseDoubleClickEvent(event);
}

void PaperView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void PaperView::dropEvent(QGraphicsSceneDragDropEvent *event)
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

void PaperView::onMediaFileDropEvent(QGraphicsSceneDragDropEvent *event)
{
	QString itemPath = event->mimeData()->urls()[0].toLocalFile();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(* new QPixmap(itemPath));
	initializeAndAddItemToScene(item, event->scenePos());
}

void PaperView::onSimpleTextDropEvent(QGraphicsSceneDragDropEvent *event)
{
	QGraphicsSimpleTextItem* item = new QGraphicsSimpleTextItem(event->mimeData()->text());
	initializeAndAddItemToScene(item, event->scenePos());
}

void PaperView::onTextDropEvent(QGraphicsSceneDragDropEvent *event)
{
	QGraphicsTextItem* item = new QGraphicsTextItem();
	item->setHtml(event->mimeData()->html());
	initializeAndAddItemToScene(item, event->scenePos());
}
