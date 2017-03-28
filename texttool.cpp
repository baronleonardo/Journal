#include "paper.h"

void Paper::onTextMousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && mode == InteractionMode::EditingText)
		handleMousePressWhileEditingText(event);

	if (event->button() == Qt::LeftButton && mode == InteractionMode::InsertingText)
	{
		//selectedItem = addText("");
		selectedItem = addSimpleText("");
		selectedItem->setPos(event->scenePos());
		selectedItem->setFlag(QGraphicsItem::ItemIsMovable);
		textEdit = new QTextEdit();
		connect(textEdit, &QTextEdit::textChanged,
				this, &Paper::textChanged);
		textEdit->move((int)event->scenePos().x() - 10, (int)event->scenePos().y());
		textEdit->setCursorWidth(3);
		textEdit->setFocus();
		proxyText = addWidget(textEdit);
		proxyText->setFocus();
		mode = InteractionMode::EditingText;
	}
}

void Paper::onTextMouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void Paper::onTextMouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(mode == InteractionMode::EditingText)
		QGraphicsScene::mouseReleaseEvent(event);
}
