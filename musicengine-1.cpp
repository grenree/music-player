#include "musicengine.h"
#include "ui_musicengine.h"





musicEngine::musicEngine() : ui(new Ui::musicEngine)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    player->setVolume(0);
    connectSignalsAndSlots();
}

musicEngine::~musicEngine()
{
    delete ui;
}

void musicEngine::connectSignalsAndSlots()
{
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this, SLOT(whenTimed(QMediaPlayer::MediaStatus)));
}

void musicEngine::whenTimed(QMediaPlayer::MediaStatus none)
{
    if(none == QMediaPlayer::EndOfMedia)
    {
        emit endOfSong();
    }
}
void musicEngine::play(QString name)
{

    player->setMedia(QUrl::fromLocalFile(name));
    player->play();

}

void musicEngine::pause()
{
    player->pause();
}

void musicEngine::resume()
{
    player->play();
}

void musicEngine::volume(int number)
{
    player->setVolume(number);
}


