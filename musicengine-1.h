#ifndef MUSICENGINE_H
#define MUSICENGINE_H

#include <QWidget>
#include<QMediaPlayer>
#include <QTimer>

namespace Ui {
class musicEngine;
}

class musicEngine : public QWidget
{
    Q_OBJECT

public:
    musicEngine();
    ~musicEngine();

    void play(QString name);
    void pause();
    void resume();
    QMediaPlayer *player;
    void volume(int number);

signals:
    void endOfSong();

private slots:
    void whenTimed(QMediaPlayer::MediaStatus none);

private:
    Ui::musicEngine *ui;
    void connectSignalsandSlots();

    QTimer *time;
    void connectSignalsAndSlots();





};

#endif // MUSICENGINE_H
