#ifndef ImportWPConvert_H
#define ImportWPConvert_H

#include <QWizardPage>

namespace IFCC {
	class IFCReader;
}

namespace Ui {
class ImportWPConvert;
}

class ImportWPConvert : public QWizardPage
{
	Q_OBJECT

public:
	explicit ImportWPConvert(QWidget *parent, IFCC::IFCReader* reader);
	~ImportWPConvert();

	/*! Checks for valid inputs. */
	virtual bool isComplete() const override;

protected:

private slots:

	void on_pushButtonConvert_clicked();

private:
	void initializePage() override;

	Ui::ImportWPConvert *ui;

	IFCC::IFCReader*	m_reader;

	bool m_convertSuccessfully;
};

#endif // ImportWPConvert_H
