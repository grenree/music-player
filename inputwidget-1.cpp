#include "inputwidget.h"

inputWidget::inputWidget() : in(new Ui::inputWidget)
{
    in->setupUi(this);
    reset();
    connectSignalsAndSlots();
}

inputWidget::~inputWidget()
{
    delete in;
}

void inputWidget::connectSignalsAndSlots()
{
    connect(in->cancelButton,SIGNAL(clicked(bool)),this,SLOT(entryDone()));
    connect(in->okButton,SIGNAL(clicked(bool)),this,SLOT(entryDone()));
    connect(in->selectFile,SIGNAL(clicked(bool)),this,SLOT(updateFileLabel(bool)));
}

QString inputWidget::inputWidget::getArtist()
{
    return in->artist->text();
}

QString inputWidget::inputWidget::getYear()
{
    return in->year->text();
}

QString inputWidget::getAlbum()
{
    return in->album->text();
}

QString inputWidget::getFile()
{
    return in->file->text();
}

QString inputWidget::getSongName()
{
    return in->songname->text();
}

void inputWidget::reset()
{
    in->file->setText("Select file");
    in->album->clear();
    in->year->clear();
    in->artist->clear();
    in->songname->clear();
}

void inputWidget::getInput()
{
    show();
}

void inputWidget::updateFileLabel(bool t)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Music File", QString(), "*.mp3");
    if(fileName.isNull())
        return;
    in->file->setText(fileName);
}

void inputWidget::entryDone()
{
    emit done(QObject::sender() == in->okButton);
}
