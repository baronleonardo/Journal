#include <QtWidgets>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include "huge_dictionary.h"
#include "papercontroller.h"

#include "tool.h"
#include "paperview.h"

PaperController::PaperController(QString paperName, QWidget *parent) : QObject(parent)
{
	paper = std::unique_ptr<PaperModel>( new PaperModel(paperName) );
	paperView = new PaperView(this, paper->getMapOfGraphicsItems());

	connect(this, &PaperController::itemModified, paper.get(), &PaperModel::onItemModified);
	connect(this, &PaperController::itemDeleted, paper.get(), &PaperModel::onItemDeleted);
}

PaperController::PaperController(QWidget* parent) : QObject(parent)
{
	paper = std::unique_ptr<PaperModel>( new PaperModel() );
	paper->setName(generateRandomName());

	paperView = new PaperView(this);

	connect(this, &PaperController::itemModified, paper.get(), &PaperModel::onItemModified);
	connect(this, &PaperController::itemDeleted, paper.get(), &PaperModel::onItemDeleted);
}

void PaperController::setTool(Tool* p_tool)
{
	paperView->setTool(p_tool);
}

void PaperController::emitItemModified(QGraphicsItem *item)
{	
	if (!paperView->itemExists(item))
	{
		return;
	}

	QString id = paperView->graphicsItems.find(item).value();

	emit itemModified(id, item);
}

void PaperController::emitItemModified(QGraphicsItem *item, QString itemPath)
{
	if (!paperView->itemExists(item))
	{
		return;
	}

	emit itemModified(paperView->graphicsItems.find(item).value(), item, itemPath);
}

void PaperController::emitItemDeleted(QString itemId)
{
	emit itemDeleted(itemId);
}

QString PaperController::name() const
{
	return paper->getName();
}

QString PaperController::generateRandomName()
{
	srand (time(NULL));
    int index = rand() % 9903;
    QString newName = QString::fromStdString(huge_dictionary[index] + " ");
    index = rand() % 9903;
    newName += QString::fromStdString(huge_dictionary[index]);
    return newName;
}
