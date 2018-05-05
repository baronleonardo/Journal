#include "brushtool.h"
#include "paperview.h"

BrushTool::BrushTool()
{
	m_paper = nullptr;
	mypaint = MPHandler::handler();

	connect(mypaint, &MPHandler::newTile, this, &BrushTool::onNewTile);
	connect(mypaint, &MPHandler::updateTile, this, &BrushTool::onUpdateTile);
	connect(mypaint, &MPHandler::clearedSurface, this, &BrushTool::onClearedSurface);
}

void BrushTool::mousePressEvent(QGraphicsSceneMouseEvent *)
{
	MPHandler::handler()->startStroke();
}

void BrushTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF pt = event->scenePos();

	if(pt.x() < 0 || pt.y() < 0)
		return;

	MPHandler::handler()->strokeTo(pt.x(), pt.y());
}

void BrushTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
	MPHandler::handler()->endStroke();

	QImage stroke = MPHandler::handler()->renderImage(QSize(m_paper->width(), m_paper->height()));
	QPixmap strokePix;
	strokePix.convertFromImage(stroke);
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(strokePix);

	for(int i = 0; i < strokeItems.size(); i++)
	{
		m_paper->deleteItem(strokeItems[i]);
	}

	strokeItems.clear();
	MPHandler::handler()->clearSurface();

	m_paper->graphicsItems[item] = QUuid::createUuid().toString();

	m_paper->addItem(item);
	m_paper->emitItemModified(item);
}

void BrushTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	m_paper->graphicsSceneDoubleClickEvent(event);
}

void BrushTool::deselect()
{
	m_paper = nullptr;
}

void BrushTool::keyPressEvent(QKeyEvent *)
{

}

void BrushTool::onNewTile(MPSurface *surface, MPTile *tile)
{
	Q_UNUSED(surface);
	strokeItems.push_back(tile);
	m_paper->addItem(tile);
}

void BrushTool::onUpdateTile(MPSurface *surface, MPTile *tile)
{
	Q_UNUSED(surface);
	tile->update();
}

void BrushTool::onClearedSurface(MPSurface *surface)
{
	Q_UNUSED(surface);
}

void BrushTool::loadBrush(const QByteArray &content)
{
	MPHandler::handler()->loadBrush(content);
}
