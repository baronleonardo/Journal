#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->tabWidget->initialize(":brushes");
	ui->actionSelect->setChecked(true);
	ui->graphicsView->setSceneRect(getScreenSize());

	setWindowSize();
	setWindowTitle(tr("Notix Journal"));

	diskIOThread.start();
	currentTool = &selectTool;
	currentPaper = nullptr;

	QStringList paperIDs = PaperModel::getAllPaperIDs();
	QStringList labels;

	if(paperIDs.size() == 0)
	{
		createNewPaper();
	}
	else
	{
		for(QString paperID : paperIDs)
		{
			PaperController* newPaper = new PaperController(paperID, this);
			newPaper->paper->moveToThread(&diskIOThread);
			allPapers.push_back( newPaper );
			labels.push_back( newPaper->name() );
		}

		ui->listWidget->addItems(labels);
		setCurrentPaper(allPapers[0]);
	}
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
	currentPaper->setTool(&brushTool);
	currentTool = &brushTool;
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
	if (currentPaper)
	{
		disconnect(ui->tabWidget, &MPBrushSelector::brushSelected, &brushTool, &BrushTool::loadBrush);
	}

	currentPaper = p_paper;
	currentPaper->setTool(currentTool);

	ui->graphicsView->setScene((QGraphicsScene*)currentPaper->paperView);
	QPixmap texture(":assets/paper_3_6.png");
	QBrush brush(texture);
	ui->graphicsView->setBackgroundBrush(brush);


	connect(ui->tabWidget, &MPBrushSelector::brushSelected, &brushTool, &BrushTool::loadBrush);
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
	setCurrentPaper(allPapers[ ui->listWidget->currentIndex().row() ]);
}

void MainWindow::on_newPaperButton_clicked()
{
	createNewPaper();
}

void MainWindow::on_actionBlue_triggered()
{
	brushTool.mypaint->setBrushColor(QColor(62, 82, 169));
}

void MainWindow::on_actionBlack_triggered()
{
	brushTool.mypaint->setBrushColor(QColor(46, 50, 53));
}

void MainWindow::on_actionRed_triggered()
{
	brushTool.mypaint->setBrushColor(QColor(218, 37, 78));
}

void MainWindow::on_actionGreen_triggered()
{
	brushTool.mypaint->setBrushColor(QColor(169, 172, 41));
}
