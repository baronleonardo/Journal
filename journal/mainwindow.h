#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "papermodel.h"
#include "brushtool.h"
#include "selecttool.h"
#include "texttool.h"
#include "paperlist.h"
#include "mpbrushselector.h"

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

    void on_listWidget_itemSelectionChanged();

	void on_newPaperButton_clicked();

	void on_actionBlue_triggered();

	void on_actionBlack_triggered();

	void on_actionRed_triggered();

	void on_actionGreen_triggered();

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:

	QThread diskIOThread;
	Tool* currentTool;
	SelectTool selectTool;
	MPBrushSelector *mp_brushes;
	BrushTool brushTool;
	TextTool textTool;
	Ui::MainWindow *ui;
    PaperList *paperList;
	PaperController *currentPaper;
	QVector<PaperController*> allPapers;
	QRectF getScreenSize();
	void setWindowSize();
	void uncheckAllExcept(QAction* action);
    void createNewPaper();
	void setCurrentPaper(PaperController* p_paper);
};

#endif // MAINWINDOW_H
