#ifndef PENTOOL_H
#define PENTOOL_H

#include "paper.h"
#include "tool.h"

class PenTool : public Tool
{

	Paper* m_paper;

	bool inTheMiddleOfAStroke;
	QPainterPath* currentStrokePath;
	QGraphicsPathItem* currentStrokeItem;
	int m_width;
	QPen m_qpen;
	QColor m_color;

	void drawLineTo(const QPointF &endPoint);

public:
	PenTool(QGraphicsScene* paper);

	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event);

};

#endif // PENTOOL_H
