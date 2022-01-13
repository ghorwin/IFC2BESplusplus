#include "ImportWPRead.h"
#include "ui_ImportWPRead.h"

#include <QFileDialog>

#include <IFCC_IFCReader.h>

#include <IBK_Path.h>

ImportWPRead::ImportWPRead(QWidget *parent, IFCC::IFCReader* reader) :
	QWizardPage(parent),
	ui(new Ui::ImportWPRead),
	m_reader(reader),
	m_readSuccessfully(false)
{
	ui->setupUi(this);
	setTitle(tr("Read IFC file"));
	setSubTitle(tr("You can load an IFC file."));

	ui->pushButtonRead->setEnabled(false);

}

ImportWPRead::~ImportWPRead() {
	delete ui;
}

bool ImportWPRead::isComplete() const {
	return m_readSuccessfully;
}

void ImportWPRead::on_toolButtonOpenIFCFile_clicked() {
	  QString filename = QFileDialog::getOpenFileName(this, tr("Open ifc file"), QString(), tr("ifc STEP file (*.ifc)"));
	  if(!filename.isEmpty()) {
		  ui->lineEditIFCFile->setText(filename);
		  ui->pushButtonRead->setEnabled(true);
	  }
	  else {
		  ui->lineEditIFCFile->clear();
		  ui->pushButtonRead->setEnabled(false);
	  }
}


void ImportWPRead::on_pushButtonRead_clicked() {
	m_readSuccessfully = false;
	if(ui->lineEditIFCFile->text().isEmpty())
		return;


	ui->textEdit->setText(tr("Reading ..."));
	ui->textEdit->update();
	IBK::Path ifcfilename(ui->lineEditIFCFile->text().toStdString());
	bool res = m_reader->read(ifcfilename);
	if(res) {
		int number = m_reader->totalNumberOfIFCEntities();
		ui->textEdit->clear();
		ui->textEdit->setText(tr("File read successfully with %1 IFC entities.").arg(number));
		m_readSuccessfully = true;
	}
	else {
		QStringList text;
		text << tr("Read not successful.");
		text << tr("Error:");
		text << QString::fromStdString(m_reader->m_errorText);
		text << tr("Warnings:");
		text << QString::fromStdString(m_reader->m_warningText);
		ui->textEdit->setText(text.join("\n"));
	}
	emit completeChanged();
}
