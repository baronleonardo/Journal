#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "papercontroller.h"
#include "tool.h"
#include "textbox.h"

class SelectTool : public Tool
{
	QGraphicsItem* selectedItem;
	TextBox* m_textBox;
	QGraphicsItem* m_dragged;
	QPointF m_dragOffset;

	bool isAStroke(QGraphicsItem* item);

public:
	SelectTool(PaperView* paper);
	~SelectTool();

	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event);
};

#endif // SELECTTOOL_H
