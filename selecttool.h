#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "paper.h"
#include "tool.h"
#include "textbox.h"

class SelectTool : public Tool
{
	Paper* m_paper;
	QGraphicsItem* selectedItem;
	TextBox* m_textBox;
	QGraphicsItem* m_dragged;
	QPointF m_dragOffset;

	bool isAStroke(QGraphicsItem* item);

public:
	SelectTool(Paper* paper);
	~SelectTool();

	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // SELECTTOOL_H
