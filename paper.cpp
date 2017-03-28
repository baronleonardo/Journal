#include <QtWidgets>
#include <iostream>

#include "paper.h"

Paper::Paper(QWidget *parent) : QGraphicsScene(parent)
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

void Paper::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(tool == Tool::Select)
		onSelectMousePressEvent(event);
	else if (tool == Tool::Text)
		onTextMousePressEvent(event);
	else if (tool == Tool::Pen)
		onPenMousePressEvent(event);
}

void Paper::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(tool == Tool::Select)
		onSelectMouseMoveEvent(event);
	else if (tool == Tool::Text)
		onTextMouseMoveEvent(event);
	else if (tool == Tool::Pen)
		onPenMouseMoveEvent(event);
}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
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

	item->setPos(event->scenePos());
	item->setFlag(QGraphicsItem::ItemIsMovable);
	addItem(item);
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
