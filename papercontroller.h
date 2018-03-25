#ifndef PAPERCONTROLLER_H
#define PAPERCONTROLLER_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include <vector>
#include <QGraphicsView>
#include <QTextEdit>
#include <memory>
#include <QtWidgets>
#include <math.h>

#define CELL_SIZE 15

class Paper;
class PaperView;
class Tool;

class PaperController : public QObject
{
	Q_OBJECT

public:
	PaperView* paperView;
	Paper* paper;

	PaperController(QString paperName, QWidget *parent = nullptr);
	PaperController(QWidget *parent = nullptr);

	void setTool(Tool* p_tool);
	void addSavableItem(QGraphicsItem* item, QUuid id);
	void emitItemModified(QGraphicsItem* item);
	void emitItemModified(QGraphicsItem* item, QString itemPath);
	void emitItemDeleted(QGraphicsItem* item);
	void insertIntoSavableItems(QGraphicsItem* item);
	void deleteItem(QGraphicsItem* item);
    void generateId();
	QString name();

signals:
	void itemModified(QUuid itemID, QGraphicsItem* item, QString itemPath = "");
	void itemDeleted(QUuid itemID, QGraphicsItem* item, QString itemPath = "");

public slots:

private:
    QString generateRandomName();
};

#endif // PAPERCONTROLLER_H
