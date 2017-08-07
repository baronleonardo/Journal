#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "papermodel.h"
#include "pentool.h"
#include "selecttool.h"
#include "texttool.h"
#include "paperlist.h"

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

protected:

private slots:
	void on_actionDraw_triggered();
	void on_actionText_triggered();
	void on_actionSelect_triggered();

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	PaperModel *paperModel;
    PaperList *paperList;
	Paper *paper;
	QRectF getScreenSize();
	void setWindowSize();
	void uncheckAllExcept(QAction* action);
};

#endif // MAINWINDOW_H
