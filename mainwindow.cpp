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

	diskIOThread.start();

    QVector<Paper*> paperVector = PaperModel().getAllPapers();

    if(paperVector.size() == 0)
    {
        Paper* tmp = new Paper();
        tmp->generateId();
        paperVector.push_back(tmp );
        PaperModel(tmp->id.toString()).savePaper(tmp);
    }

    QStringList labels;
    for (Paper* storedPaper : paperVector)
    {
        labels.push_back(storedPaper->name);
        allPapers.push_back(paperAndModelPair(storedPaper, new PaperModel(storedPaper->id.toString())));
    }

    setCurrentPaper(allPapers[0]);

    SelectTool* selectTool = new SelectTool(currentPaper);
    currentPaper->setTool(selectTool);

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
    delete currentPaper;
	delete currentPaperModel;
}

void MainWindow::on_actionDraw_triggered()
{
	uncheckAllExcept(ui->actionDraw);

    PenTool* penTool = new PenTool(currentPaper);
    currentPaper->setTool(penTool);
}

void MainWindow::on_actionText_triggered()
{	
	uncheckAllExcept(ui->actionText);

    TextTool* textTool = new TextTool(currentPaper);
    currentPaper->setTool(textTool);
}

void MainWindow::on_actionSelect_triggered()
{
	uncheckAllExcept(ui->actionSelect);

    SelectTool* selectTool = new SelectTool(currentPaper);
    currentPaper->setTool(selectTool);
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

void MainWindow::createNewPaper()
{
    currentPaper = new Paper();
    currentPaper->generateId();
    allPapers.push_back(paperAndModelPair(currentPaper, currentPaperModel = new PaperModel(currentPaper->id.toString())));
    ui->listWidget->addItem(currentPaper->name);
    ui->graphicsView->setScene(currentPaper);
	currentPaperModel->moveToThread(&diskIOThread);
	connect(currentPaper, &Paper::itemModified, currentPaperModel, &PaperModel::onItemModified);
	connect(currentPaper, &Paper::itemDeleted, currentPaperModel, &PaperModel::onItemDeleted);
    currentPaperModel->savePaper(currentPaper);
}

void MainWindow::setCurrentPaper(paperAndModelPair p_paper)
{
    currentPaper = p_paper.first;
    currentPaperModel = p_paper.second;
    ui->graphicsView->setScene(currentPaper);
	connect(currentPaper, &Paper::itemModified, currentPaperModel, &PaperModel::onItemModified);
	connect(currentPaper, &Paper::itemDeleted, currentPaperModel, &PaperModel::onItemDeleted);
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    if (ui->listWidget->currentIndex().row() == 0)
        createNewPaper();
    else
        setCurrentPaper( // -1 because the first item is to add a new paper
                    allPapers[ ui->listWidget->currentIndex().row() - 1 ] );
}
