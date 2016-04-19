#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include "tablemodel.h"
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	bfsRunner(new BFSRunner(this))
{
	ui->setupUi(this);
	setModule();
	initForm();

	connect(bfsRunner, SIGNAL(bfsDone()), this, SLOT(setFormEnable()));
	connect(bfsRunner, SIGNAL(newPages(QList<Page*>)), model, SLOT(newPages(QList<Page*>)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setModule()
{
	QTableView *tableView = ui->tableView;

	model = new TableModel();

	tableView->setModel(model);

	for (int column = 0; column < Page::COLUMNS; ++column)
	{
		QHeaderView::ResizeMode mode = column == Page::URL || column == Page::STATUS
				? QHeaderView::Stretch
				: QHeaderView::ResizeToContents;
		tableView->horizontalHeader()->setSectionResizeMode(column, mode);
	}

	connect(model, SIGNAL(layoutChanged()), tableView, SLOT(scrollToBottom()));
}

void MainWindow::initForm()
{
	ui->startButton->setEnabled(true);
	ui->stopButton->setEnabled(false);
	ui->urlEdit->clear();
	ui->findEdit->clear();
	ui->maxUrlslSpinBox->setMinimum(1);
	ui->maxUrlslSpinBox->setValue(1);
	ui->threadSpinBox->setMinimum(1);
	ui->threadSpinBox->setValue(1);
}

void MainWindow::setFormEnable(bool enable)
{
	ui->urlEdit->setEnabled(enable);
	ui->findEdit->setEnabled(enable);
	ui->threadSpinBox->setEnabled(enable);
	ui->maxUrlslSpinBox->setEnabled(enable);
	ui->startButton->setEnabled(enable);
	ui->stopButton->setEnabled(!enable);
}

void MainWindow::on_startButton_clicked()
{
	if (ui->urlEdit->text() == "" || ui->findEdit->text() == "") {
		return;
	}

	QString url = ui->urlEdit->text();
	QString text = ui->findEdit->text();
	quint32 threads = ui->threadSpinBox->value();
	quint32 urls = ui->maxUrlslSpinBox->value();

	setFormEnable(false);
	model->clear();
	bfsRunner->runBfs(url, text, threads, urls);
}

void MainWindow::on_stopButton_clicked()
{
	bfsRunner->stop();
	setFormEnable(true);
}
