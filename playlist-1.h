#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QMainWindow>
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QWidget>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include "ui_inputwidget.h"
#include "inputwidget.h"

namespace Ui {
class playlist;
}

class playlist : public QWidget
{
    Q_OBJECT

public:

    playlist();
    ~playlist();


private:
    Ui::playlist *ui;
    inputWidget *input;
    QString playlist1;
    QStringList songData;


    void readContents();
    void connectSignalsAndSlots();
    void updatePlayListItems(const QString &songName,const QString &artist, const QString &album, const QString &year, const QString &file);

private slots:
    void openPlayList(bool clicked);
    void addFileToPlaylist(bool clicked);
    void quit(bool t);
    void process(bool t);
    void savePlayList(bool clicked);

};

#endif // PLAYLIST_H
