#include <QtWidgets>
#include <iostream>

#include "paper.h"

Paper::Paper(QWidget *parent) : QGraphicsScene(parent), mCellSize(15, 15)
{
	mode = InteractionMode::Selecting; // general mode is drawing
	inTheMiddleOfAStroke = false;				 // but at this very moment we're not drawing
	myPenWidth = 3;
	myPenColor = Qt::black;
	myPen = QPen(myPenColor, myPenWidth,
				 Qt::SolidLine, Qt::RoundCap,
				 Qt::RoundJoin);
	selectedItem = nullptr;
	textEdit = nullptr;
	proxyText = nullptr;
	currentStrokePath = nullptr;
	currentStrokeItem = nullptr;
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
	myPen.setColor(QColor(190,190,190,50));
	painter->setPen(myPen);
	myPen.setColor(myPenColor);
	painter->drawLines(lines.data(), lines.size());
}

void Paper::setPenColor(const QColor &newColor)
{
	myPenColor = newColor;
}

void Paper::setPenWidth(int newWidth)
{
	myPenWidth = newWidth;
}

void Paper::setDrawing()
{
	mode = InteractionMode::Drawing;
	tool = Tool::Pen;
}

void Paper::setInsertingText()
{
	mode = InteractionMode::InsertingText;
	tool = Tool::Text;
}

void Paper::setSelect()
{
	mode = InteractionMode::Selecting;
	tool = Tool::Select;
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

void Paper::handleMousePressWhileEditingText(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

	if(!item || (item != selectedItem && item != proxyText))
	{
		deselect();
		mode = InteractionMode::Selecting;
		tool = Tool::Select;
	}

	QGraphicsScene::mousePressEvent(event);
}

bool Paper::isAStroke(QGraphicsItem* item)
{
	QGraphicsPathItem* tmp = qgraphicsitem_cast<QGraphicsPathItem*>(item);
	return (tmp == nullptr) ? false : true;
}

void Paper::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	mDragged = qgraphicsitem_cast<QGraphicsItem*>(itemAt(event->scenePos(), QTransform()));

	if (mDragged) mDragOffset = event->scenePos() - mDragged->pos();
	else QGraphicsScene::mousePressEvent(event);

	if(tool == Tool::Select)
		onSelectMousePressEvent(event);
	else if (tool == Tool::Text)
		onTextMousePressEvent(event);
	else if (tool == Tool::Pen)
		onPenMousePressEvent(event);
}

void Paper::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (mDragged)
		// Ensure that the item's offset from the mouse cursor stays the same.
		mDragged->setPos(event->scenePos() - mDragOffset);
	else
		QGraphicsScene::mouseMoveEvent(event);

	if(tool == Tool::Select)
		onSelectMouseMoveEvent(event);
	else if (tool == Tool::Text)
		onTextMouseMoveEvent(event);
	else if (tool == Tool::Pen)
		onPenMouseMoveEvent(event);
}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (mDragged && ! isAStroke(mDragged))
	{
		int x, y;
		roundToNearestCell(x, y, mDragged->scenePos());
		mDragged->setPos(x, y);
		mDragged = 0;
	}
	else
		QGraphicsScene::mouseReleaseEvent(event);

	if(tool == Tool::Select)
		onSelectMouseReleaseEvent(event);
	else if (tool == Tool::Text)
		onTextMouseReleaseEvent(event);
	else if (tool == Tool::Pen)
		onPenMouseReleaseEvent(event);
}

void Paper::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void Paper::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	if(mode == InteractionMode::Selecting)
		QGraphicsScene::dropEvent(event);

	QGraphicsItem* item;

	if(event->mimeData()->hasUrls()) //TODO: make sure it's a photo and add support to all file types ever
		item = new QGraphicsPixmapItem(* new QPixmap(event->mimeData()->urls()[0].toLocalFile()));

	else if (event->mimeData()->hasHtml())
	{
		item = new QGraphicsTextItem();
		((QGraphicsTextItem *)item)->setHtml(event->mimeData()->html());
	}

	else if(event->mimeData()->hasText())
			item = new QGraphicsSimpleTextItem(event->mimeData()->text());

	else if(event->mimeData()->hasImage())
	{
		QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
		item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	}

	else return;

	item->setFlag(QGraphicsItem::ItemIsMovable);
	// snaps to nearest grid line
	int x, y;
	roundToNearestCell(x, y, event->scenePos());
	item->setPos(x, y);
	addItem(item);
	addSavableItem(item);
}

void Paper::roundToNearestCell(int &x, int &y, QPointF pos)
{
	x = round(pos.x() / mCellSize.width()) * mCellSize.width();
	y = round(pos.y() / mCellSize.height()) * mCellSize.height();
}

void Paper::addSavableItem(QGraphicsItem *item)
{
	savableItems.insert(item, QUuid::createUuid());
}

void Paper::drawLineTo(const QPointF &endPoint)
{
	currentStrokePath->lineTo(endPoint);
	currentStrokeItem->setPath(*currentStrokePath);
}

void Paper::deselect()
{
	if (proxyText)
	{
		removeItem(proxyText);
		proxyText = nullptr;
	}

	if (textEdit)
	{
		delete textEdit;
		textEdit = nullptr;
	}

	if (selectedItem)
		selectedItem = nullptr;
}

void Paper::textChanged()
{
	QGraphicsTextItem* selectedTextItem = dynamic_cast<QGraphicsTextItem*>(selectedItem);

	if(selectedTextItem)
	{
		selectedTextItem->setDocument(textEdit->document());
		return;
	}

	QGraphicsSimpleTextItem* selectedSimpleTextItem = dynamic_cast<QGraphicsSimpleTextItem*>(selectedItem);

	if(selectedSimpleTextItem)
		selectedSimpleTextItem->setText(textEdit->document()->toPlainText());
}
