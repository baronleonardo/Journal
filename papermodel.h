#ifndef PAPERMODEL_H
#define PAPERMODEL_H

#include <QObject>
#include <QJsonObject>
#include <QGraphicsItem>
#include <QUuid>
#include <QMutex>

class Paper : public QObject
{
	Q_OBJECT

private:
	QUuid id;
	QString name;

	static const QString appDirectoryName;
	static QString configLocation;
	static QString appDirectoryLocation;
	static QString papersDirectoryLocation;
	static QString imagesDirectoryLocation;

	QJsonObject paperJson;

	QJsonValue itemToJson(QGraphicsItem* item);
	QGraphicsItem* itemFromJson(QJsonObject data, QString mediaFileLocation);

	QString copyMediaFileToJournal(QUuid id, QString path);

	QString getAssetPath(QString relativePath);

	QGraphicsPixmapItem* pixmap_cast(QGraphicsItem* item);
	QGraphicsSimpleTextItem* simpleText_cast(QGraphicsItem* item);
	QGraphicsTextItem* text_cast(QGraphicsItem* item);

	void setPaperID(QString id);
	void setPaperID(QUuid p_id);

public slots:
	void onItemModified(QUuid id, QGraphicsItem* item, QString itemPath = "");
	void onItemDeleted(QUuid id);

public:
	Paper();
	Paper(QString paperID);
	~Paper();

	QString getName() const;
	void setName(QString name);

	static QStringList getAllPaperIDs();
	QHash<QGraphicsItem*, QString> getMapOfGraphicsItems();
	void save();
};

#endif // PAPERMODEL_H
