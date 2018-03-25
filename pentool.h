#ifndef PENTOOL_H
#define PENTOOL_H

#include "papercontroller.h"
#include "tool.h"

struct BoundingRectangle
{
	QPointF upperRight;
	QPointF bottomLeft;
	BoundingRectangle(QPointF p_upperRight, QPointF p_bottomLeft);
	int width();
	int height();
	void updateRectangle(QPointF point);
};

class PenTool : public Tool
{
	bool inTheMiddleOfAStroke;
	QPainterPath* currentStrokePath;
	QGraphicsPathItem* currentStrokeItem;
	int m_width;
	QPen m_qpen;
	QColor m_color;
	BoundingRectangle currentStrokeBoundingRectangle;
	void drawLineTo(const QPointF &endPoint);
	QPixmap pathToPixmap(const QGraphicsPathItem* pathItem);

public:
	PenTool(PaperView* paper);

	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event);

};

#endif // PENTOOL_H
