#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablemodel.h"
#include "bfsrunner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void setModule();
	void initForm();

public slots:
	void setFormEnable(bool enable = true);

private slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();

private:
	Ui::MainWindow *ui;
	TableModel *model;
	BFSRunner *bfsRunner;
};

#endif // MAINWINDOW_H
