#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>

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

namespace Ui {
class library;
}

class library : public QWidget
{
    Q_OBJECT

public:
    library();
    ~library();

    QString getArtist();
    QString getYear();
    QString getAlbum();
    QString getFile();
    QString getName();
    void import();
    QStringList getListOfFile();
    QStringList getListOfSongs();
    QStringList getListOfAlbum();
    QStringList getListOfArtist();
    QStringList getListOfYear();
signals:
    void send(const QString &songName,const QString &artist, const QString &album, const QString &year, const QString &file);
private:
    Ui::library *ui;
    QString playlist1;
    QStringList songData;
    QStringList listOfFiles;
    QStringList listOfSongs;
    QStringList listOfArtist;
    QStringList listOfAlbum;
    QStringList listOfYear;

    QString songName;
    QString album;
    QString artist;
    QString year;
    QString file;
    //void updatePlayListItems(const QString &songName,const QString &artist, const QString &album, const QString &year, const QString &file);
};

#endif // LIBRARY_H
