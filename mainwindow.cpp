#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowSize();

	diskIOThread.start();

	QStringList paperIDs = Paper::getAllPaperIDs();
	QStringList labels;

	if(paperIDs.size() == 0)
	{
		allPapers.push_back( new PaperController(this) );
		labels.push_back( allPapers[0]->name() );
	}


	for(QString paperID : paperIDs)
	{
		PaperController* newPaper = new PaperController(paperID, this);
		newPaper->paper->moveToThread(&diskIOThread);
		allPapers.push_back( newPaper );
		labels.push_back( newPaper->name() );
	}


	currentTool = &selectTool;
	setCurrentPaper(allPapers[0]);

	ui->actionSelect->setChecked(true);
	ui->graphicsView->setSceneRect(getScreenSize());
	ui->listWidget->addItems(labels);

	setWindowTitle(tr("Journal"));
}

MainWindow::~MainWindow()
{
	diskIOThread.quit();
	diskIOThread.wait();

	delete ui;
}

void MainWindow::on_actionDraw_triggered()
{
	uncheckAllExcept(ui->actionDraw);
	currentPaper->setTool(&penTool);
	currentTool = &penTool;
}

void MainWindow::on_actionText_triggered()
{	
	uncheckAllExcept(ui->actionText);
	currentPaper->setTool(&textTool);
	currentTool = &textTool;
}

void MainWindow::on_actionSelect_triggered()
{
	uncheckAllExcept(ui->actionSelect);
	currentPaper->setTool(&selectTool);
	currentTool = &selectTool;
}

QRectF MainWindow::getScreenSize()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	return QRectF(screen->geometry());
}

void MainWindow::setWindowSize()
{
	this->setWindowState(Qt::WindowMaximized);
}

void MainWindow::uncheckAllExcept(QAction* action)
{
	foreach (QAction* a, ui->mainToolBar->actions())
		a->setChecked(false);

	action->setChecked(true);
}

void MainWindow::createNewPaper()
{
	currentPaper = new PaperController(this);
	allPapers.push_back(currentPaper);
	currentPaper->setTool(currentTool);
	ui->listWidget->addItem(currentPaper->name());
	ui->graphicsView->setScene((QGraphicsScene*)currentPaper->paperView);
	currentPaper->paper->moveToThread(&diskIOThread);
}

void MainWindow::setCurrentPaper(PaperController* p_paper)
{
	currentPaper = p_paper;
	currentPaper->setTool(currentTool);
	ui->graphicsView->setScene((QGraphicsScene*)currentPaper->paperView);
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
	setCurrentPaper(allPapers[ ui->listWidget->currentIndex().row() ]);
}

void MainWindow::on_newPaperButton_clicked()
{
	createNewPaper();
}
