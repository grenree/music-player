#include "musicvideo.h"
#include "ui_musicvideo.h"

musicVideo::musicVideo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::musicVideo)
{
    ui->setupUi(this);
     vid = new QVideoWidget();
    connectSignalsAndSlots();
}

musicVideo::~musicVideo()
{

    delete ui;
}

void musicVideo::connectSignalsAndSlots()
{
    connect(ui->fileButton,SIGNAL(clicked(bool)),this,SLOT(addVideo()));
    connect(ui->enterButton,SIGNAL(clicked(bool)),this,SLOT(runVideo()));
    //connect(vid->parent(),SIGNAL(destroyed(QObject*)),player,SLOT(stop()));





}

void musicVideo::reject()
{
    player->stop();
    QDialog::reject();

}

bool musicVideo::close()
{
    qDebug()<<"here";
    player->stop();
    return QWidget::close();
}



void musicVideo::runVideo()
{
    website = ui->webLink->text();
    playWebVideo();
}

void musicVideo::playWebVideo()
{
    player = new QMediaPlayer();
    //vid = new QVideoWidget();
    vid->setAttribute( Qt::WA_DeleteOnClose );

    player->setVideoOutput(vid);


    player->setMedia(QUrl(website));

    vid->setGeometry(0,25,1920,1055);
    vid->show();
     running = true;
    player->play();
}
void musicVideo::addVideo()
{
    fileName = QFileDialog::getOpenFileName(this, "Music Video File", QString(), "*.mp4");
    if(fileName.isNull())
        return;
    playVideo();
}

void musicVideo::playVideo()
{
    player = new QMediaPlayer();
    //vid = new QVideoWidget();
    vid->setAttribute( Qt::WA_DeleteOnClose );

    player->setVideoOutput(vid);

    player->setMedia(QUrl::fromLocalFile(fileName));

    vid->setGeometry(0,25,1920,1055);
    vid->show();
     running = true;
    player->play();


}

