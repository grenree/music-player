#ifndef MUSICVIDEO_H
#define MUSICVIDEO_H

#include <QWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class musicVideo;
}

class musicVideo : public QDialog
{
    Q_OBJECT

public:
    explicit musicVideo(QWidget *parent = 0);
    ~musicVideo();

signals:


private slots:
    void addVideo();
    void runVideo();



private:

    QMediaPlayer *player;
    Ui::musicVideo *ui;
    QString fileName;
    QString website;
    void playVideo();
    void playWebVideo();
    void connectSignalsAndSlots();
    QVideoWidget *vid;
    bool running;
   void reject();
    bool close();




};

#endif // MUSICVIDEO_H
