#include "paper.h"

void Paper::onSelectMousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(event->button() == Qt::LeftButton && mode == InteractionMode::EditingText)
		handleMousePressWhileEditingText(event);

	else if (event->button() == Qt::LeftButton && mode == InteractionMode::Selecting)
	{
		QGraphicsScene::mousePressEvent(event);
		selectedItem = itemAt(event->scenePos(), QTransform());
		QGraphicsTextItem* selectedTextItem = dynamic_cast<QGraphicsTextItem*>(selectedItem);

		if(!selectedTextItem)
		{
			deselect();
			return;
		}

		textEdit = new QTextEdit();
		connect(textEdit, &QTextEdit::textChanged,
				this, &Paper::textChanged);
		textEdit->resize((int)selectedTextItem->boundingRect().size().width() + 5,
						 (int)selectedTextItem->boundingRect().size().height() + 5);
		textEdit->move((int)selectedTextItem->pos().x(), (int)selectedTextItem->pos().y());
		textEdit->setDocument(selectedTextItem->document());
		textEdit->setCursorWidth(3);
		textEdit->setFocus();
		proxyText = addWidget(textEdit);
		proxyText->setFocus();
		mode = InteractionMode::EditingText;
	}

	else if(mode == InteractionMode::Selecting)
		QGraphicsScene::mousePressEvent(event);
}

void Paper::onSelectMouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(mode == InteractionMode::Selecting)
		QGraphicsScene::mouseReleaseEvent(event);
}

void Paper::onSelectMouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(mode == InteractionMode::Selecting  || mode == InteractionMode::EditingText)
		QGraphicsScene::mouseReleaseEvent(event);
}
