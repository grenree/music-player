#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H
#include <QWidget>
#include <QString>
#include <QFileDialog>
#include "ui_inputwidget.h"

class inputWidget : public QWidget
{
    Q_OBJECT

    public:
        inputWidget();
        ~inputWidget();

        QString getArtist();
        QString getYear();
        QString getAlbum();
        QString getFile();
        QString getSongName();
        void reset();

   signals:
        void done(bool yes);

    public slots:
        void getInput();

   private:
        Ui::inputWidget *in;

        void connectSignalsAndSlots();

   private slots:
        void updateFileLabel(bool t);
        void entryDone();
};

#endif // INPUTWIDGET_H

