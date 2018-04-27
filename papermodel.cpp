#include "papermodel.h"

#include <QStandardPaths>
#include <QTextDocument>
#include <QFile>
#include <QDir>
#include <QJsonDocument>

const QString Paper::appDirectoryName = "journal/";
QString Paper::configLocation = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + '/';
QString Paper::appDirectoryLocation = configLocation + appDirectoryName;
QString Paper::papersDirectoryLocation = appDirectoryLocation + "papers/";
QString Paper::imagesDirectoryLocation = appDirectoryLocation + "images/";

QJsonValue Paper::itemToJson(QGraphicsItem* item)
{
	QJsonObject data;

	data["posx"] = item->pos().x();
	data["posy"] = item->pos().y();

	if (pixmap_cast(item))
		data["type"] = "pixmap";

	else if (QGraphicsTextItem* textItem = text_cast(item))
	{
		data["type"] = "richtext";
		data["document"] = textItem->document()->toHtml();
	}
	else if (QGraphicsSimpleTextItem* simpleTextItem = simpleText_cast(item))
	{
		data["type"] = "simpletext";
		data["text"] = simpleTextItem->text();
	}
	else return QJsonValue();

	return QJsonValue(data);
}

QGraphicsItem* Paper::itemFromJson(QJsonObject data, QString mediaFileLocation = "")
{
	QGraphicsItem* result;

	if (data["type"] == "pixmap")
		result = new QGraphicsPixmapItem(QPixmap(mediaFileLocation));
	else if(data["type"] == "simpletext")
		result = new QGraphicsSimpleTextItem(data["text"].toString());
	else if(data["type"] == "richtext")
	{
		result = new QGraphicsTextItem();
		((QGraphicsTextItem *)result)->setHtml(data["document"].toString());
	}
	else return nullptr;

	result->setPos(data["posx"].toDouble(), data["posy"].toDouble());
	return result;
}

void Paper::onItemModified(QUuid id, QGraphicsItem *item, QString itemPath = "")
{
	if (itemPath.size())
	{
		itemPath = copyMediaFileToJournal(id, itemPath);
	}
	else if (QGraphicsPixmapItem* pixmapItem = pixmap_cast(item))
	{
		pixmapItem->pixmap().save(imagesDirectoryLocation + id.toString(), "PNG");
	}

	QJsonValue itemJson = itemToJson(item);

	paperJson[id.toString()] = itemJson;

	save();
}

void Paper::onItemDeleted(QUuid id, QGraphicsItem *item, QString itemPath)
{
	QJsonObject::Iterator i = paperJson.find(id.toString());

	if(i == paperJson.end())
		return;

	if (i.value().toObject()["type"] == "pixmap")
	{
		QFile photo(imagesDirectoryLocation + i.key());
		if (photo.exists())
			photo.remove();
	}

	paperJson.remove(i.key());

	save();
}

QString Paper::copyMediaFileToJournal(QUuid id, QString path)
{
	QFile mediaFile(path);
	if (!mediaFile.exists())
		return "";
	QString mediaFilePath = imagesDirectoryLocation + id.toString();

	mediaFile.copy(mediaFilePath);

	return mediaFilePath;
}

// gets absolute path to assets within the journal directory, returns an empty string if it does not exist.
QString Paper::getAssetPath(QString relativePath)
{
	QFile file(imagesDirectoryLocation + relativePath);
	if (file.exists())
		return imagesDirectoryLocation + relativePath;
	return "";
}

QGraphicsPixmapItem* Paper::pixmap_cast(QGraphicsItem *item)
{
	return dynamic_cast<QGraphicsPixmapItem*>(item);
}

QGraphicsSimpleTextItem* Paper::simpleText_cast(QGraphicsItem *item)
{
	return dynamic_cast<QGraphicsSimpleTextItem*>(item);
}

QGraphicsTextItem* Paper::text_cast(QGraphicsItem *item)
{
	return dynamic_cast<QGraphicsTextItem*>(item);
}

Paper::Paper(QString paperID) : Paper()
{
	QFile paperFile(papersDirectoryLocation + paperID);
	paperFile.open(QIODevice::ReadOnly);

	QByteArray byteArray = paperFile.readAll();

	QJsonDocument jsonDocument(QJsonDocument::fromJson(byteArray));
	paperJson = QJsonObject(jsonDocument.object());

	setPaperID(paperID);
	name = paperJson.value("name").toString();
}

Paper::Paper() : QObject(nullptr)
{
	QDir dir;
	if (!dir.exists(appDirectoryLocation))		dir.mkdir(appDirectoryLocation);
	if (!dir.exists(papersDirectoryLocation))	dir.mkdir(papersDirectoryLocation);
	if (!dir.exists(imagesDirectoryLocation))	dir.mkdir(imagesDirectoryLocation);
	id = QUuid::createUuid();
}

Paper::~Paper()
{
}

QString Paper::getName() const
{
	return this->name;
}

void Paper::setName(QString name)
{
	this->name = name;
	paperJson["name"] = name;
}

QStringList Paper::getAllPaperIDs()
{
	QDir dir(papersDirectoryLocation);
	return dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);
}

QHash<QGraphicsItem*, QString> Paper::getMapOfGraphicsItems()
{
	QHash<QGraphicsItem*, QString> graphicsItems;
	QJsonObject::Iterator i;

	for(i = paperJson.begin(); i != paperJson.end(); i++)
	{
		QString itemPath = getAssetPath(i.key());
		QGraphicsItem* item = itemFromJson(i.value().toObject(), itemPath);
		if(item)
			graphicsItems.insert(item, i.key());
	}

	return graphicsItems;
}

void Paper::setPaperID(QString p_id)
{
	QUuid id(p_id);
	setPaperID(id);
}

void Paper::setPaperID(QUuid p_id)
{
	id = p_id;
}

void Paper::save()
{
	QJsonDocument jsonDocument(paperJson);
	QFile paperFile(papersDirectoryLocation + id.toString());
	paperFile.open(QIODevice::WriteOnly);
	paperFile.write(jsonDocument.toJson());
}
