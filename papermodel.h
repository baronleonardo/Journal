#ifndef PAPERMODEL_H
#define PAPERMODEL_H

#include <QObject>

#include "paper.h"

class PaperModel : public QThread
{
	Q_OBJECT

private:
	const QString appDirectoryName;
	QString appDirectoryLocation;
	QJsonObject* paperJson;
	Paper* paper;
	QFile paperFile;

	QJsonValue itemToJson(QGraphicsItem* item);
	QGraphicsItem* itemFromJson(QJsonObject data);
	QPainterPath getPathFromJson(QJsonValue json);
	QPainterPath getPathFromPoints(QList<QVariant> points);
	bool dataIs(QVariantHash data, QString type);
	QList<QPointF> getPointsInPath(QPainterPath path);
	QJsonArray jsonArrayFromPath(QPainterPath path);
	QPixmap pixmapFrom(const QJsonValue & val);
	QJsonValue jsonValFromPixmap(const QPixmap & p);
	void saveToFile(QJsonDocument jsonDocument);

public slots:
	void onItemModified(QUuid id, QGraphicsItem* item);

protected:
	void run() override;

signals:

public:
	PaperModel(QObject* parent = 0);
	~PaperModel();

	Paper* loadPaper(QString path);
	void savePaper(Paper* paper);
};

#endif // PAPERMODEL_H
