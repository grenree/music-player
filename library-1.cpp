#include "library.h"
#include "ui_library.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

library::library() : ui(new Ui::library)
{
    ui->setupUi(this);
}

library::~library()
{
    delete ui;
}



void library::import()
{
    QString playlist1 = QFileDialog::getOpenFileName(NULL, "Music File", QString(), "*.playlist");
    if(playlist1.isNull())
        return;
    if (QFileInfo(playlist1).suffix().isEmpty())
      playlist1.append(".playlist");
    QFile in(playlist1);
    QXmlStreamReader reader;
    QMap<QString, QString> items;
    if(!in.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("File Input Error");
        msgBox.setText("File cannot be read.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        qDebug() << "Cannot read file" << in.errorString();
        return;
    }
    reader.setDevice(&in);
    //ui->tableOfSongs->setRowCount(0);
    //come back to this because i might need to restart this
    while(!reader.atEnd())
    {
        reader.readNextStartElement();
        if(reader.name() == "song")
        {
           do
            {
                reader.readNext() ;
                if(reader.tokenType() == QXmlStreamReader::EndElement)
                    break;
                items[reader.name().toString()] = reader.readElementText();
            }while(true);
            //updatePlayListItems(items["songName"],items["artist"],items["album"], items["year"], items["file"]);
           songName = items["songname"];
           artist = items["artist"];
           album = items["album"];
                 year = items["year"];
                  file = items["file"];
                  listOfAlbum<<items["album"];
                  listOfArtist<<items["artist"];
                  listOfSongs<<items["songname"];
                  listOfYear<<items["year"];
                  listOfFiles<<items["file"];

            emit send(items["songname"],items["artist"],items["album"], items["year"], items["file"]);
        }
    }
    in.close();
}
QStringList library::getListOfSongs()
{
    return listOfSongs;
}
QStringList library::getListOfArtist()
{
    return listOfArtist;
}
QStringList library::getListOfYear()
{
    return listOfYear;
}
QStringList library::getListOfAlbum()
{
    return listOfAlbum;
}

QStringList library::getListOfFile()
{
    return listOfFiles;
}

QString library::getName()
{
    return songName;
}

QString library::getArtist()
{
    return artist;
}

QString library::getAlbum()
{
    return album;
}

QString library::getYear()
{
    return year;
}

QString library::getFile()
{
    return file;
}
