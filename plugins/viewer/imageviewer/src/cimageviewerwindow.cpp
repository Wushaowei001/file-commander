#include "cimageviewerwindow.h"
#include "ui_cimageviewerwindow.h"

DISABLE_COMPILER_WARNINGS
#include <QFileDialog>
#include <QLabel>
#include <QShortcut>
#include <QTimer>
RESTORE_COMPILER_WARNINGS

CImageViewerWindow::CImageViewerWindow() :
	CPluginWindow(),
	ui(new Ui::CImageViewerWindow)
{
	ui->setupUi(this);
	_imageInfoLabel = new QLabel(this);
	statusBar()->addWidget(_imageInfoLabel);

	connect(ui->actionOpen, &QAction::triggered, [this](){
		const QString filtersString = tr("All files (*.*);; GIF (*.gif);; JPEG (*.jpg *.jpeg);; TIFF (*.tif);; PNG (*.png)");
		const QString fileName = QFileDialog::getOpenFileName(this, QString(), QString(), filtersString);
		if (!fileName.isEmpty())
			displayImage(fileName);
	});

	connect(ui->actionReload, &QAction::triggered, [this]() {
		displayImage(_currentImagePath);
	});

	connect(ui->actionClose, &QAction::triggered, this, &QMainWindow::close);

	auto escScut = new QShortcut(QKeySequence("Esc"), this, SLOT(close()));
	connect(this, &QAction::destroyed, escScut, &QShortcut::deleteLater);
}

CImageViewerWindow::~CImageViewerWindow()
{
	delete ui;
}

bool CImageViewerWindow::displayImage(const QString& imagePath, const QImage& image /* = QImage() */)
{
	_currentImagePath = imagePath;
	if (!ui->_imageViewerWidget->displayImage(imagePath, image))
		return false;

	_imageInfoLabel->setText(ui->_imageViewerWidget->imageInfoString());
	setWindowTitle(imagePath);

	QTimer::singleShot(10, [this](){
		static const QList<QSize> requiredIconSizes = { { 16, 16 }, { 32, 32 } };
		setWindowIcon(ui->_imageViewerWidget->imageIcon(requiredIconSizes));
	});

	return true;
}
