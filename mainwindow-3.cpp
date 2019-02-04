#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creation = new playlist;
    engine = new musicEngine;
    lib = new library;
    ui->tableOfSongs->setColumnCount(5);
    ui->tableOfSongs->setHorizontalHeaderLabels(QStringList()<<"Song Name"<<"Artist"<<"Album"<<"Year"<<"File");
    connectSignalsAndSlots();
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::connectSignalsAndSlots()
{
    connect(ui->editPlaylist,SIGNAL(clicked(bool)),this,SLOT(configurePlaylist(bool)));
   // connect(ui->playPlaylist,SIGNAL(clicked(bool)),this,SLOT(test()));
    connect(ui->importPlaylist,SIGNAL(clicked(bool)),this,SLOT(createLibrary()));
     connect(lib,SIGNAL(send(QString,QString,QString,QString,QString)),this,SLOT(update()));
     connect(ui->tableOfSongs,SIGNAL(cellClicked(int,int)),this,SLOT(test(int,int)));

     connect(ui->playButton,SIGNAL(clicked(bool)),this,SLOT(playCurrentSong()));
     connect(ui->pauseButton,SIGNAL(clicked(bool)),this,SLOT(pause()));
     connect(ui->volume,SIGNAL(sliderMoved(int)),this,SLOT(changeVolume(int)));
     connect(ui->resumeButton,SIGNAL(clicked(bool)),this,SLOT(resume()));
     connect(ui->nextButton,SIGNAL(clicked(bool)),this,SLOT(next()));
     connect(ui->previousButton,SIGNAL(clicked(bool)),this,SLOT(previous()));

     connect(engine->player,SIGNAL(durationChanged(qint64)),this,SLOT(songSliderLength(qint64)));
     connect(engine->player,SIGNAL(positionChanged(qint64)),this,SLOT(songSliderPos(qint64)));

     connect(ui->videoButton,SIGNAL(clicked(bool)),this,SLOT(video()));

     connect(engine,SIGNAL(endOfSong()),this,SLOT(maybe()));


}

void MainWindow::video()
{
    videoo = new musicVideo(this);
    videoo->show();
}

void MainWindow::next()
{
    currentSongName = nextSongName;
    updateSongName();
    engine->play(nextSong);
    if((pos+2)>=list.size())
    {
        nextSong = list[list.size()-1];
        previousSong = list[list.size()-2];
        nextSongName = list1[list.size()-1] + " " + list2[list.size()-1] + " " + list3[list.size()-1] + " " + list4[list.size()-1];
        previousSongName = list1[list.size()-2] + " " + list2[list.size()-2] + " " + list3[list.size()-2] + " " + list4[list.size()-2];
        pos = list.size() - 1;
    }
    else
    {
    nextSongName = list1[pos+2] + " " + list2[pos+2] + " " + list3[pos+2] + " " + list4[pos+2];
    previousSongName = list1[pos] + " " + list2[pos] + " " + list3[pos] + " " + list4[pos];
    nextSong = list[pos+2];
    currentSong = list[pos+1];
    previousSong = list[pos];
    pos++;
    }




}

void MainWindow::previous()
{
    currentSongName = previousSongName;
    updateSongName();
    engine->play(previousSong);
    if((pos-2) < 0)
    {
        nextSong = list[1];
        previousSong = list[0];
        nextSongName = list1[1] + " " + list2[1] + " " + list3[1] + " " + list4[1];
        previousSongName = list1[0] + " " + list2[0] + " " + list3[0] + " " + list4[0];
        pos = 0;
    }
    else
    {
    nextSongName = list1[pos] + " " + list2[pos] + " " + list3[pos] + " " + list4[pos];
    previousSongName = list1[pos-2] + " " + list2[pos-2] + " " + list3[pos-2] + " " + list4[pos-2];
    nextSong = list[pos];
    currentSong = list[pos-1];
    previousSong = list[pos-2];
    pos--;
    }

}

void MainWindow::resume()
{
    engine->resume();
}

void MainWindow::on_songStamp_sliderMoved(int value)
{
    engine->player->setPosition(value);
}
void MainWindow::songSliderLength(qint64 length)
{
    ui->songStamp->setMaximum(length);
}

void MainWindow::songSliderPos(qint64 pos)
{
    ui->songStamp->setValue(pos);
}


void MainWindow::updateSongName()
{
    ui->label_2->setText(currentSongName);
}

void MainWindow::maybe()
{

    for(int i = 0; i < list.size();i++)
    {
        if(list[i] == currentSong)
        {
            if(i == list.size() - 1 && ui->loopCheck->checkState() == Qt::Checked)
            {
               previousSong = list[list.size()-1];
               previousSongName = list1[list.size()-1] + " " + list2[list.size()-1] + " " + list3[list.size()-1] + " " + list4[list.size()-1];
                currentSong = list[0];
                nextSong = list[1];
                qDebug()<<"here1";
                currentSongName = list1[0] + " " + list2[0] + " " + list3[0] + " " + list4[0];
                nextSongName = list1[1] + " " + list2[1] + " " + list3[1] + " " + list4[1];
                pos = 0;

            }
            else if(i == list.size() - 1 && ui->loopCheck->checkState() == Qt::Unchecked)
            {
                engine->player->stop();
                break;
            }
            else
            {
                previousSong = list[i];
                pos = i+1;
                nextSong = list[i+2];
                currentSong = list[i+1];
                currentSongName = list1[i+1] + " " + list2[i+1] + " " + list3[i+1] + " " + list4[i+1];
                nextSongName = list1[i+2] + " " + list2[i+2] + " " + list3[i+2] + " " + list4[i+2];
                previousSongName = list1[i] + " " + list2[i] + " " + list3[i] + " " + list4[i];




            }
            updateSongName();
            engine->play(currentSong);
            break;
        }

    }



}

void MainWindow::changeVolume(int number)
{
    engine->volume(number);
}

QString MainWindow::getCurrentSong()
{
    return currentSong;
}

void MainWindow::pause()
{
    engine->pause();
}

void MainWindow::playCurrentSong()
{
    engine->play(currentSong);
    updateSongName();
}

void MainWindow::update()
{

    int row = ui->tableOfSongs->rowCount();
    ui->tableOfSongs->insertRow(row);
    ui->tableOfSongs->setItem(row,0, new QTableWidgetItem(lib->getName()));
    ui->tableOfSongs->setItem(row,1, new QTableWidgetItem(lib->getArtist()));
    ui->tableOfSongs->setItem(row,2, new QTableWidgetItem(lib->getAlbum()));
    ui->tableOfSongs->setItem(row,3, new QTableWidgetItem(lib->getYear()));
    ui->tableOfSongs->setItem(row,4, new QTableWidgetItem(lib->getFile()));
}

void MainWindow:: configurePlaylist(bool clicked)
{
    creation->show();
}

void MainWindow::createLibrary()
{
        lib->import();
         list =  lib->getListOfFile();
         list1 =  lib->getListOfSongs();
         list2 =  lib->getListOfArtist();
         list3 =  lib->getListOfAlbum();
         list4 =  lib->getListOfYear();
}
void MainWindow::test(int row,int col)
{

       QStringList list =  lib->getListOfFile();
       QStringList list1 =  lib->getListOfSongs();
       QStringList list2 =  lib->getListOfArtist();
       QStringList list3 =  lib->getListOfAlbum();
       QStringList list4 =  lib->getListOfYear();

       pos = row;

       if(pos == list.size() -1)
       {
           currentSongName = list1[row] + " " + list2[row] + " " + list3[row] + " " + list4[row];
           currentSong = list[row];

           nextSongName = list1[row] + " " + list2[row] + " " + list3[row] + " " + list4[row];
           nextSong = list[row];

           previousSongName = list1[row-1] + " " + list2[row-1] + " " + list3[row-1] + " " + list4[row-1];
           previousSong = list[row-1];
       }
       else if(pos == 0)
       {
           currentSongName = list1[row] + " " + list2[row] + " " + list3[row] + " " + list4[row];
           currentSong = list[row];

           nextSongName = list1[row+1] + " " + list2[row+1] + " " + list3[row+1] + " " + list4[row+1];
           nextSong = list[row+1];

           previousSongName = list1[row] + " " + list2[row] + " " + list3[row] + " " + list4[row];
           previousSong = list[row];
       }
       else
       {
       currentSongName = list1[row] + " " + list2[row] + " " + list3[row] + " " + list4[row];
       currentSong = list[row];

       nextSongName = list1[row+1] + " " + list2[row+1] + " " + list3[row+1] + " " + list4[row+1];
       nextSong = list[row+1];

       previousSongName = list1[row-1] + " " + list2[row-1] + " " + list3[row-1] + " " + list4[row-1];
       previousSong = list[row-1];
       }

}


MainWindow::~MainWindow()
{
    delete creation;
    delete lib;
    delete engine;
    delete ui;
}
