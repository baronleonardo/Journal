#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>

#include <QtWidgets>
#include <math.h>

enum InteractionMode
{
	Drawing,
	Selecting,
	InsertingText,
	EditingText
};

enum Tool
{
	Select,
	Pen,
	Text
};

class Paper : public QGraphicsScene
{
	Q_OBJECT

public:
	QUuid id;
	InteractionMode mode;
	Tool tool;
	QHash<QGraphicsItem*, QUuid> savableItems;

	Paper(QWidget *parent = 0);

	void setPenColor(const QColor &newColor);
	void setPenWidth(int newWidth);

	QColor penColor() const { return myPenColor; }
	int penWidth() const { return myPenWidth; }
	void setMoving();
	void setDrawing();
	void setInsertingText();
	void setSelect();
	void setPaperID(QUuid id);
	void setPaperID();
	void addSavableItem(QGraphicsItem* item, QUuid id);

signals:
	void paperModified(Paper* paper, QUuid itemID);

public slots:

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

private:
	void drawLineTo(const QPointF &endPoint);
	void deselect();

	void onSelectMousePressEvent(QGraphicsSceneMouseEvent *event);
	void onTextMousePressEvent(QGraphicsSceneMouseEvent *event);
	void onPenMousePressEvent(QGraphicsSceneMouseEvent *event);

	void onSelectMouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void onTextMouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void onPenMouseMoveEvent(QGraphicsSceneMouseEvent *event);

	void onSelectMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void onTextMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void onPenMouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	void handleMousePressWhileEditingText(QGraphicsSceneMouseEvent *event);

	bool isAStroke(QGraphicsItem* item);
	void roundToNearestCell(int &x, int &y, QPointF pos);
	void addSavableItem(QGraphicsItem* item);

	void textChanged();

	bool inTheMiddleOfAStroke;
	int myPenWidth;
	QGraphicsItem* selectedItem;
	QTextEdit* textEdit;
	QGraphicsProxyWidget *proxyText;
	QColor myPenColor;
	QPointF lastPoint;
	QPen myPen;
	QPainterPath* currentStrokePath;
	QGraphicsPathItem* currentStrokeItem;
	const QSize mCellSize;
	QGraphicsItem *mDragged;
	QPointF mDragOffset;
};

#endif
