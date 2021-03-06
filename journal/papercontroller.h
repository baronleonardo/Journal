#ifndef PAPERCONTROLLER_H
#define PAPERCONTROLLER_H

#include <QWidget>
#include <memory>
#include <QtWidgets>
#include <math.h>
#include "papermodel.h"

#define CELL_SIZE 15

class PaperView;
class Tool;

class PaperController : public QObject
{
	Q_OBJECT

public:
	PaperView* paperView;
	std::unique_ptr<PaperModel> paper;

	PaperController(QString paperName, QWidget *parent = nullptr);
	PaperController(QWidget *parent = nullptr);

	void setTool(Tool* p_tool);
	void addSavableItem(QGraphicsItem* item, QUuid id);
	void emitItemModified(QGraphicsItem* item);
	void emitItemModified(QGraphicsItem* item, QString itemPath);
	void emitItemDeleted(QString itemId);
	void insertIntoSavableItems(QGraphicsItem* item);
	void deleteItem(QGraphicsItem* item);
    void generateId();
	QString name() const;

signals:
	void itemModified(QString itemID, QGraphicsItem* item, QString itemPath = "");
	void itemDeleted(QString itemID);

public slots:

private:
    QString generateRandomName();
};

#endif // PAPERCONTROLLER_H
