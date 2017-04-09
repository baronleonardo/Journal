#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
						QMainWindow(parent),
						ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//this->setStyleSheet("background-color: #f8f8f8;");
	setWindowSize();
	paperModel = new PaperModel("default_paper");
	paper = paperModel->getPaper();
	connect(paper, &Paper::itemModified, paperModel, &PaperModel::onItemModified, Qt::QueuedConnection);

	SelectTool* selectTool = new SelectTool(paper);
	paper->setTool(selectTool);
	ui->actionSelect->setChecked(true);

	ui->graphicsView->setScene(paper);
	ui->graphicsView->setSceneRect(getScreenSize());

	setWindowTitle(tr("Journal"));
}

MainWindow::~MainWindow()
{
	delete ui;
	delete paper;
	delete paperModel;
}

void MainWindow::on_actionDraw_triggered()
{
	uncheckAllExcept(ui->actionDraw);

	PenTool* penTool = new PenTool(paper);
	paper->setTool(penTool);
}

void MainWindow::on_actionText_triggered()
{	
	uncheckAllExcept(ui->actionText);

	TextTool* textTool = new TextTool(paper);
	paper->setTool(textTool);
}

void MainWindow::on_actionSelect_triggered()
{
	uncheckAllExcept(ui->actionSelect);

	SelectTool* selectTool = new SelectTool(paper);
	paper->setTool(selectTool);
}

QRectF MainWindow::getScreenSize()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	return QRectF(screen->geometry());
}

void MainWindow::setWindowSize()
{
	QRectF screenSize = getScreenSize();
	resize(screenSize.width(), screenSize.height());
}

void MainWindow::uncheckAllExcept(QAction* action)
{
	foreach (QAction* a, ui->mainToolBar->actions())
		a->setChecked(false);

	action->setChecked(true);
}
