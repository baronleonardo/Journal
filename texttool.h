#ifndef TEXTTOOL_H
#define TEXTTOOL_H

#include "tool.h"
#include "textbox.h"

class TextTool : public Tool
{
	QGraphicsItem* selectedItem;
	TextBox* m_textBox;

	void handleMousePressWhileEditingText(QGraphicsSceneMouseEvent *event);


public:
	TextTool(PaperView* paper);
	~TextTool();

	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    //void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

};

#endif // TEXTTOOL_H
