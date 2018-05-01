#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "papercontroller.h"
#include "tool.h"
#include "textbox.h"

class SelectTool : public Tool
{
	QGraphicsItem* selectedItem;
	std::unique_ptr<TextBox> m_textBox;
	QGraphicsItem* m_dragged;
	QPointF m_dragOffset;

	bool isAStroke(QGraphicsItem* item);

public:
	SelectTool();
	~SelectTool();

	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void deselect() Q_DECL_OVERRIDE;
};

#endif // SELECTTOOL_H
