#ifndef TOOL_H
#define TOOL_H

#include <QGraphicsScene>
#include <QTextEdit>
#include <QtWidgets>
#include <QObject>

class PaperView;

class Tool : public QObject
{
	Q_OBJECT

protected:

public:
	explicit Tool();
	PaperView* m_paper;
	void setPaper(PaperView* paper) { m_paper = paper; }

	virtual void keyPressEvent(QKeyEvent *event) = 0;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) = 0;
	virtual void deselect() = 0;

signals:

public slots:
};

#endif // TOOL_H
