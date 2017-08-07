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
    currentPaper = paperModel->getPaper();
    connect(currentPaper, &Paper::itemModified, paperModel, &PaperModel::onItemModified, Qt::QueuedConnection);
    connect(currentPaper, &Paper::itemDeleted, paperModel, &PaperModel::onItemDeleted, Qt::QueuedConnection);
    SelectTool* selectTool = new SelectTool(currentPaper);
    currentPaper->setTool(selectTool);
	ui->actionSelect->setChecked(true);

    ui->graphicsView->setScene(currentPaper);
	ui->graphicsView->setSceneRect(getScreenSize());

    allPapers = paperModel->getAllPapers();

    QStringList labels;
    for (auto storedPaper : allPapers)
        labels.push_back(storedPaper->id.toString());

    ui->listWidget->addItems(labels);

	setWindowTitle(tr("Journal"));
}

MainWindow::~MainWindow()
{
	delete ui;
    delete currentPaper;
	delete paperModel;
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

void MainWindow::on_listWidget_itemSelectionChanged()
{
    currentPaper = allPapers[ui->listWidget->currentIndex().row()];
    ui->graphicsView->setScene(currentPaper);
    connect(currentPaper, &Paper::itemModified, paperModel, &PaperModel::onItemModified, Qt::QueuedConnection);
    connect(currentPaper, &Paper::itemDeleted, paperModel, &PaperModel::onItemDeleted, Qt::QueuedConnection);
}
