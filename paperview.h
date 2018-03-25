#ifndef PAPERVIEW_H
#define PAPERVIEW_H

#include <QGraphicsScene>
#include <QVector>
#include "tool.h"

class PaperController;

class PaperView : public QGraphicsScene
{
public:
	PaperView(PaperController* controller);
	PaperView(PaperController *controller, QVector<QGraphicsItem*> items);

	void setTool(Tool* tool);
	void deleteItem(QGraphicsItem* item);

	void emitItemModified(QGraphicsItem* item);
	void emitItemModified(QGraphicsItem* item, QString itemPath);
	void emitItemDeleted(QGraphicsItem* item);

	void graphicsSceneDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	void graphicsScenePressEvent(QGraphicsSceneMouseEvent *event);
	void graphicsSceneMoveEvent(QGraphicsSceneMouseEvent *event);
	void graphicsSceneReleaseEvent(QGraphicsSceneMouseEvent *event);
	void roundToNearestCell(int &x, int &y, QPointF pos);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

private:
	void onMediaFileDropEvent(QGraphicsSceneDragDropEvent *event);
	void onSimpleTextDropEvent(QGraphicsSceneDragDropEvent *event);
	void onTextDropEvent(QGraphicsSceneDragDropEvent *event);
	void initializeAndAddItemToScene(QGraphicsItem* item, QPointF position);

	PaperController* controller;
	std::unique_ptr<Tool> currentTool;
	QPointF lastPoint;
	const QSize mCellSize;
};

#endif // PAPERVIEW_H
