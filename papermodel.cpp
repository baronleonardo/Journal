#include "papermodel.h"

Paper *PaperModel::getPaper() const
{
	return paper;
}

QJsonValue PaperModel::itemToJson(QGraphicsItem* item)
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
	else if (QGraphicsPathItem* pathItem = pathItem_cast(item))
	{
		data["type"] = "stroke";
		data["path"] = jsonArrayFromPath(pathItem->path());
	}
	else return QJsonValue();

	return QJsonValue(data);
}

QGraphicsItem* PaperModel::itemFromJson(QJsonObject data, QString mediaFileLocation = "")
{
	QGraphicsItem* result;

	if (data["type"] == "pixmap")
		result = new QGraphicsPixmapItem(QPixmap(mediaFileLocation));
	else if(data["type"] == "stroke")
		result = new QGraphicsPathItem(getPathFromJson(data["path"]));
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

void PaperModel::onItemModified(QUuid id, QGraphicsItem *item, QString itemPath = "")
{
	QJsonObject::Iterator i = paperJson->find(id.toString());

	if (itemPath.size())
		itemPath = copyMediaFileToJournal(id, itemPath);

	QJsonValue itemJson = itemToJson(item);

	if(i == paperJson->end())
		paperJson->insert(id.toString(), itemJson);
	else
		i.value() = itemJson;
	saveToFile(QJsonDocument(*paperJson));
}

QString PaperModel::copyMediaFileToJournal(QUuid id, QString path)
{
	QFile mediaFile(path);
	if (!mediaFile.exists())
		return "";
	QString mediaFilePath = appDirectoryLocation + id.toString();

	mediaFile.copy(mediaFilePath);

	return mediaFilePath;
}

// gets absolute path to assets within the journal directory, returns an empty string if it does not exist.
QString PaperModel::getAbsolutePath(QString relativePath)
{
	QFile file(appDirectoryLocation + relativePath);
	if (file.exists())
		return appDirectoryLocation + relativePath;
	return "";
}

QGraphicsPixmapItem* PaperModel::pixmap_cast(QGraphicsItem *item)
{
	return dynamic_cast<QGraphicsPixmapItem*>(item);
}

QGraphicsPathItem* PaperModel::pathItem_cast(QGraphicsItem *item)
{
	return dynamic_cast<QGraphicsPathItem*>(item);
}

QGraphicsSimpleTextItem* PaperModel::simpleText_cast(QGraphicsItem *item)
{
	return dynamic_cast<QGraphicsSimpleTextItem*>(item);
}

QGraphicsTextItem* PaperModel::text_cast(QGraphicsItem *item)
{
	return dynamic_cast<QGraphicsTextItem*>(item);
}

void PaperModel::run()
{

}

void PaperModel::saveToFile(QJsonDocument jsonDocument)
{
	paperFile->open(QIODevice::WriteOnly);
	paperFile->write(jsonDocument.toJson());
	paperFile->close();
}

QList<QPointF> PaperModel::getPointsInPath(QPainterPath path)
{
	QList<QPointF> points;
	for(int i = 0; i < path.elementCount(); i++)
		points.append(QPointF(path.elementAt(i).x, path.elementAt(i).y));
	return points;
}

QJsonArray PaperModel::jsonArrayFromPath(QPainterPath path)
{
	QList<QPointF> points = getPointsInPath(path);
	QVariantList pointPositions;


	foreach(QPointF point, points)
	{
		pointPositions.append(QVariant(point.x()));
		pointPositions.append(QVariant(point.y()));
	}

	QJsonArray tmp = QJsonArray::fromVariantList(pointPositions);
	return tmp;
}

QPainterPath PaperModel::getPathFromJson(QJsonValue json)
{
	QList<QVariant> points = json.toArray().toVariantList();
	return getPathFromPoints(points);
}

QPainterPath PaperModel::getPathFromPoints(QList<QVariant> points)
{
	QPointF position(points[0].toDouble(), points[1].toDouble());
	QPainterPath path(position);

	// it's a list of [x, y, x, y, x, y...]
	for (int i = 2; i < points.size() - 1; i+=2)
	{
		QPointF point(points[i].toDouble(), points[i+1].toDouble());
		path.lineTo(point);
	}

	return path;
}

PaperModel::PaperModel(QString path) : QThread(), appDirectoryName("/journal/")
{
	QString configLocation = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
	appDirectoryLocation = configLocation + appDirectoryName;

	QDir dir;
	if(!dir.exists(appDirectoryLocation))
		dir.mkdir(appDirectoryLocation);

	paperFile = new QFile(appDirectoryLocation + path);
	paper = loadPaper(path);
}

PaperModel::~PaperModel()
{
	paperFile->close();
}

Paper *PaperModel::loadPaper(QString path)
{
	Paper* newPaper = new Paper();

	newPaper->setPaperID(path);

	paperFile->open(QIODevice::ReadOnly);

	QByteArray byteArray = paperFile->readAll();

	paperFile->close();

	QJsonDocument jsonDocument(QJsonDocument::fromJson(byteArray));
	paperJson = new QJsonObject(jsonDocument.object());

	QJsonObject::Iterator i;

	for(i = paperJson->begin(); i != paperJson->end(); i++)
	{
		QString itemPath = getAbsolutePath(i.key());
		QGraphicsItem* item = itemFromJson(i.value().toObject(), itemPath);
		newPaper->addSavableItem(item, QUuid(i.key()));
	}

	return newPaper;
}

void PaperModel::savePaper(Paper *paper)
{
	this->paper = paper;
	paperJson = new QJsonObject();

	QHashIterator<QGraphicsItem*, QUuid> i(paper->savableItems);
	while (i.hasNext())
	{
		i.next();
		paperJson->insert(i.value().toString(), itemToJson(i.key()));
	}

	QJsonDocument jsonDocument(*paperJson);

	saveToFile(jsonDocument);
}
