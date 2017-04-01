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
//	paper = new Paper();
//	paper->setPaperID();
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

void MainWindow::penColor()
{
	QColor newColor = QColorDialog::getColor(paper->penColor());
	if (newColor.isValid())
		paper->setPenColor(newColor);
}

void MainWindow::penWidth()
{
	bool ok;
	int newWidth = QInputDialog::getInt(this, tr("Scribble"),
										tr("Select pen width:"),
										paper->penWidth(),
										1, 50, 1, &ok);
	if (ok)
		paper->setPenWidth(newWidth);
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Scribble"),
			tr("<p>The <b>Journal</b> app is a notes taking app inspired heavily by Microsoft OneNote.</p>"));
}

void MainWindow::on_actionDraw_triggered()
{
	paper->setDrawing();
}

void MainWindow::on_actionText_triggered()
{
	paper->setInsertingText();
}

void MainWindow::on_actionSelect_triggered()
{
	paper->setSelect();
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
