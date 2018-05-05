/*
Copyright (c) 2016, François Téchené
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "mpsurface.h"

static void freeTiledSurface(MyPaintSurface *surface)
{
    MPSurface *self = (MPSurface *)surface;
    mypaint_tiled_surface_destroy(self);

    free(self->null_tile);
    free(self);
}

static void defaultUpdateFunction(MPSurface *surface, MPTile *tile)
{
    Q_UNUSED(surface);
    Q_UNUSED(tile);
    // Things to do if no update callback has been affected
}

static void onTileRequestStart(MyPaintTiledSurface *tiled_surface, MyPaintTileRequest *request)
{
    MPSurface *self = (MPSurface *)tiled_surface;

    const int tx = request->tx;
    const int ty = request->ty;
	uint16_t *tile_pointer = nullptr;

	if (tx < 0 || ty < 0) {
        // Give it a tile which we will ignore writes to
        tile_pointer = self->null_tile;
    } else {
        MPTile* tile = self->getTileFromIdx(QPoint(tx,ty));
		tile_pointer = tile ? tile->Bits(false) : nullptr;
    }

    request->buffer = tile_pointer;
}

static void onTileRequestEnd(MyPaintTiledSurface *tiled_surface, MyPaintTileRequest *request)
{
    MPSurface *self = (MPSurface *)tiled_surface;

    const int tx = request->tx;
    const int ty = request->ty;

    MPTile* tile = self->getTileFromIdx(QPoint(tx,ty));
    if (tile) tile->updateCache();

    self->onUpdateTileFunction(self, tile);
}

MPSurface::MPSurface()
{
    // Init callbacks
    //
	this->onUpdateTileFunction   = defaultUpdateFunction;
	this->onNewTileFunction      = defaultUpdateFunction;

    // MPSurface vfuncs
    this->parent.destroy = freeTiledSurface;

    mypaint_tiled_surface_init((MyPaintTiledSurface *)this, onTileRequestStart, onTileRequestEnd);
}

MPSurface::~MPSurface()
{

}

void MPSurface::setOnUpdateTile(MPOnUpdateTileFunction onUpdateFunction)
{
    this->onUpdateTileFunction = onUpdateFunction;
}

void MPSurface::setOnNewTile(MPOnUpdateTileFunction onNewTileFunction)
{
    this->onNewTileFunction = onNewTileFunction;
}

void MPSurface::setOnClearedSurface(MPOnUpdateSurfaceFunction onClearedSurfaceFunction)
{
    this->onClearedSurfaceFunction = onClearedSurfaceFunction;
}

void MPSurface::loadImage(const QImage &image)
{
    QSize tileSize = QSize(MYPAINT_TILE_SIZE, MYPAINT_TILE_SIZE);

    int nbTilesOnWidth = ceil((float)this->width / (float)tileSize.width());
    int nbTilesOnHeight = ceil((float)this->height / (float)tileSize.height());

    QImage sourceImage = image.scaled(this->size(), Qt::IgnoreAspectRatio);

    int nbTiles = 0;

    for (int h=0; h < nbTilesOnHeight; h++) {

        for (int w=0; w < nbTilesOnWidth; w++) {

            QPoint idx(w, h);
            QPoint tilePos = getTilePos(idx) ;

            QRect tileRect = QRect(tilePos, tileSize);
            QImage tileImage = sourceImage.copy(tileRect);

            // Optimization : Fully transparent (empty) tiles
            // don't need to be created.
            //
            if (!isFullyTransparent(tileImage)) {

                nbTiles ++;

                MPTile *tile = getTileFromIdx(idx);
                tile->setImage(tileImage);

                this->onUpdateTileFunction(this, tile);
            }
        }
    }
}

void MPSurface::setSize(QSize size)
{
    free(this->null_tile);

	//resetSurface(size);
}

QSize MPSurface::size()
{
    return QSize(width, height);
}

void MPSurface::clear()
{
    QHashIterator<QPoint, MPTile*> i(m_Tiles);
    while (i.hasNext()) {
        i.next();
        MPTile *tile = i.value();
        if (tile)
        {
            // Clear the content of the tile
            //
            tile->clear();

            // Removes blank tile from the scene for output optimization
            //
            // A tile without a scene is not re-created but onNewTile is
            // called when this tile is to be shown again.
            //
            QGraphicsScene* scene = tile->scene();
            if (scene) {
                scene->removeItem(tile);
            }
        }
    }

    this->onClearedSurfaceFunction(this);
}

QImage MPSurface::renderImage(QSize sceneSize)
{
	QHashIterator<QPoint, MPTile*> i(m_Tiles);
	QGraphicsScene surfaceScene;
	surfaceScene.setSceneRect(QRect(QPoint(0,0), sceneSize));

    while (i.hasNext()) {
        i.next();
        MPTile *tile = i.value();
        if (tile)
        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem( QPixmap::fromImage(tile->image()));
			item->setPos(tile->pos());

			surfaceScene.addItem(item);
        }
	}

	QPixmap renderedImage = QPixmap(sceneSize);
	renderedImage.fill(QColor(Qt::transparent));

    QPainter painter;
    painter.begin(&renderedImage);
    surfaceScene.render(&painter);
    painter.end();

    surfaceScene.clear();

    return renderedImage.toImage();
}

void MPSurface::resetNullTile()
{
    memset(this->null_tile, 0, this->tile_size);
}

bool MPSurface::isFullyTransparent(QImage image)
{
    image.convertToFormat(QImage::Format_ARGB32);

    for (int x = 0 ; x < image.width() ; x++) {

        for (int y = 0 ; y < image.height() ; y++) {

            QRgb currentPixel = (image.pixel(x, y));

            if (qAlpha(currentPixel) != 0) {
                return false;

            }
        }
    }
    return true;
}

MPTile* MPSurface::getTileFromPos(const QPoint& pos)
{
    return getTileFromIdx(getTileIndex(pos));
}

MPTile* MPSurface::getTileFromIdx(const QPoint& idx)
{

	MPTile* selectedTile = nullptr;

	// Ok, valid index. Does it exist already ?
	selectedTile = m_Tiles.value(idx, nullptr);

	if (!selectedTile) {
		// Time to allocate it, update table and insert it as a QGraphicsItem in scene:
		selectedTile = new MPTile();
		m_Tiles.insert(idx, selectedTile);

		QPoint tilePos ( getTilePos(idx) );
		selectedTile->setPos(tilePos);
	}
	if (!selectedTile->scene()) {
		this->onNewTileFunction(this, selectedTile);
	}

    return selectedTile;
}

inline bool MPSurface::checkIndex(uint n)
{
    return ((int)n<k_max);
}

inline QPoint MPSurface::getTilePos(const QPoint& idx)
{
    return QPoint(MYPAINT_TILE_SIZE*idx.x(), MYPAINT_TILE_SIZE*idx.y());
}

inline QPoint MPSurface::getTileIndex(const QPoint& pos)
{
    return QPoint(pos.x()/MYPAINT_TILE_SIZE, pos.y()/MYPAINT_TILE_SIZE);
}

inline QPointF MPSurface::getTileFIndex(const QPoint& pos)
{
    return QPointF((qreal)pos.x()/MYPAINT_TILE_SIZE, (qreal)pos.y()/MYPAINT_TILE_SIZE);
}
