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
	paper = std::unique_ptr<Paper>( new Paper(paperName) );
	paperView = new PaperView(this, paper->getVectorOfGraphicsItems());

	connect(this, &PaperController::itemModified, paper.get(), &Paper::onItemModified);
	connect(this, &PaperController::itemDeleted, paper.get(), &Paper::onItemDeleted);
}

PaperController::PaperController(QWidget* parent) : QObject(parent)
{
	paper = std::unique_ptr<Paper>( new Paper() );
	paper->name = generateRandomName();

	paperView = new PaperView(this);

	connect(this, &PaperController::itemModified, paper.get(), &Paper::onItemModified);
	connect(this, &PaperController::itemDeleted, paper.get(), &Paper::onItemDeleted);
}

void PaperController::setTool(Tool* p_tool)
{
	paperView->setTool(p_tool);
}

void PaperController::emitItemModified(QGraphicsItem *item)
{
	emit itemModified(paper->graphicsItems.find(item).value(), item);
}

void PaperController::emitItemModified(QGraphicsItem *item, QString itemPath)
{
	emit itemModified(paper->graphicsItems.find(item).value(), item, itemPath);
}

void PaperController::emitItemDeleted(QGraphicsItem *item)
{
	emit itemDeleted(paper->graphicsItems.find(item).value(), item);
}

void PaperController::deleteItem(QGraphicsItem *item)
{
	emitItemDeleted(item);
}

QString PaperController::name()
{
	return paper->name;
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
