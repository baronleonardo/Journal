#ifndef PAPERMODEL_H
#define PAPERMODEL_H

#include "paper.h"

class PaperModel
{
private:
	const QString appDirectoryName;
	QString appDirectoryLocation;

	QJsonObject itemToVariant(QGraphicsItem* item, QUuid id);
	QGraphicsItem* itemFromJson(QJsonObject data);
	QPainterPath getPathFromJson(QJsonValue json);
	QPainterPath getPathFromPoints(QList<QVariant> points, QPointF position);
	bool dataIs(QVariantHash data, QString type);
	QList<QVariant> getPointsInPath(QPainterPath path);
	QPixmap pixmapFrom(const QJsonValue & val);
	QJsonValue jsonValFromPixmap(const QPixmap & p);

public:
	PaperModel();

	Paper* loadPaper(QString path);
	void savePaper(Paper* paper);
};

#endif // PAPERMODEL_H
