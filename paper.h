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

#include "tool.h"

#define CELL_SIZE 15

class Paper : public QGraphicsScene
{
	Q_OBJECT

public:
	QUuid id;
    QString name;
	QHash<QGraphicsItem*, QUuid> savableItems;

	Paper(QWidget *parent = 0);

	void setTool(Tool* p_tool);
    void setPaperID(QString id);
	void setPaperID(QUuid id);
	void setPaperID();
	void addSavableItem(QGraphicsItem* item, QUuid id);
	void emitItemModified(QGraphicsItem* item);
	void emitItemDeleted(QGraphicsItem* item);
	void insertIntoSavableItems(QGraphicsItem* item);
	void graphicsScenePressEvent(QGraphicsSceneMouseEvent *event);
	void graphicsSceneMoveEvent(QGraphicsSceneMouseEvent *event);
	void graphicsSceneReleaseEvent(QGraphicsSceneMouseEvent *event);
	void graphicsSceneDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	void roundToNearestCell(int &x, int &y, QPointF pos);
	void deleteItem(QGraphicsItem* item);

signals:
	void itemModified(QUuid itemID, QGraphicsItem* item, QString itemPath = "");
	void itemDeleted(QUuid itemID, QGraphicsItem* item, QString itemPath = "");

public slots:

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
	void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:

	void onMediaFileDropEvent(QGraphicsSceneDragDropEvent *event);
	void onSimpleTextDropEvent(QGraphicsSceneDragDropEvent *event);
	void onTextDropEvent(QGraphicsSceneDragDropEvent *event);
	void initializeAndAddItemToScene(QGraphicsItem* item, QPointF position);
	void textChanged();

	Tool* currentTool;
	QPointF lastPoint;
	const QSize mCellSize;
};

#endif
