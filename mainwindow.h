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

typedef std::pair<Paper*, PaperModel*> paperAndModelPair;

class MainWindow : public QMainWindow
{
	Q_OBJECT

protected:

private slots:
	void on_actionDraw_triggered();
	void on_actionText_triggered();
	void on_actionSelect_triggered();

    void on_listWidget_itemSelectionChanged();

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:

	QThread workerThread;
	Ui::MainWindow *ui;
    PaperList *paperList;
    Paper *currentPaper;
    PaperModel *currentPaperModel;
    QVector<paperAndModelPair> allPapers;
	QRectF getScreenSize();
	void setWindowSize();
	void uncheckAllExcept(QAction* action);
    void createNewPaper();
    void setCurrentPaper(paperAndModelPair p_paper);
};

#endif // MAINWINDOW_H
