#ifndef PENTOOL_H
#define PENTOOL_H

#include "papercontroller.h"
#include "tool.h"
#include "mphandler.h"
#include "mpbrush.h"
#include "mpsurface.h"
#include "mptile.h"

class BrushTool : public Tool
{
	QVector<QGraphicsItem*> strokeItems;

public:
	BrushTool();

	MPHandler *mypaint;

	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void deselect() Q_DECL_OVERRIDE;

public slots:
	void onNewTile(MPSurface *surface, MPTile *tile);
	void onUpdateTile(MPSurface *surface, MPTile *tile);
	void onClearedSurface(MPSurface *surface);
	void loadBrush(const QByteArray& content);
};

#endif // PENTOOL_H
