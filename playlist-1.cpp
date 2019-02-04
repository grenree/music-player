#include "playlist.h"
#include "ui_playlist.h"

/*playlist::playlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playlist)
{
    ui->setupUi(this);
}*/

playlist::playlist() :ui(new Ui::playlist)
{
    ui->setupUi(this);
    input = new inputWidget;
    ui->playlistItems->setColumnCount(5);
    ui->playlistItems->setHorizontalHeaderLabels(QStringList()<<"Song Name"<<"Artist"<<"Album"<<"Year"<<"File");
    songData <<"songname"<<"artist"<<"album"<<"year"<<"file";
    connectSignalsAndSlots();

}

playlist::~playlist()
{
    delete input;
    delete ui;
}



void playlist::quit(bool t)
{
    this->close();
}

void playlist::connectSignalsAndSlots()
{
    connect(ui->addFileToPlaylist,SIGNAL(clicked(bool)),this,SLOT(addFileToPlaylist(bool)));
    connect(ui->quit,SIGNAL(clicked(bool)),this,SLOT(quit(bool)));
    connect(input,SIGNAL(done(bool)),this,SLOT(process(bool)));
    connect(ui->openPlaylist,SIGNAL(clicked(bool)),this,SLOT(openPlayList(bool)));
    connect(ui->savePlaylist,SIGNAL(clicked(bool)),this,SLOT(savePlayList(bool)));
}


void playlist::process(bool t)
{
    input->hide();
    qDebug()<<"OK pressed? "<<t;
    if(!t)
        return;
    updatePlayListItems(input->getSongName(),input->getArtist(),input->getAlbum(),input->getYear(),input->getFile());
    input->reset();
}

void playlist::updatePlayListItems(const QString &songName,const QString &artist, const QString &album, const QString &year, const QString &file)
{

    int row = ui->playlistItems->rowCount();
    ui->playlistItems->insertRow(row);
    ui->playlistItems->setItem(row,0, new QTableWidgetItem(songName));
    ui->playlistItems->setItem(row,1, new QTableWidgetItem(artist));
    ui->playlistItems->setItem(row,2, new QTableWidgetItem(album));
    ui->playlistItems->setItem(row,3, new QTableWidgetItem(year));
    ui->playlistItems->setItem(row,4, new QTableWidgetItem(file));
}


void playlist::savePlayList(bool clicked)
{
    QXmlStreamWriter writer;
    QString fileName = QFileDialog::getSaveFileName(NULL, "Playlist File", QString(), "*.playlist");
    if(fileName.isNull())
        return;
    if (QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".playlist");
    QFile out(fileName);
    out.open(QFile::WriteOnly);
    writer.setDevice(&out);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("playlist");
    for(int i = 0; i < ui->playlistItems->rowCount(); ++i)
    {
        writer.writeStartElement("song");
        for(int j = 0; j < songData.size(); ++j)
            writer.writeTextElement(songData[j],ui->playlistItems->item(i,j)->text());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    out.close();
}

void playlist::addFileToPlaylist(bool clicked)
{
    input->show();
}

void playlist::openPlayList(bool clicked)
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
    ui->playlistItems->setRowCount(0);
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
            updatePlayListItems(items["songname"],items["artist"],items["album"], items["year"], items["file"]);
        }
    }
    in.close();
}
