#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QMediaPlayer>
#include <QMediaObject>


#include "playlist.h"
#include "ui_playlist.h"
#include "musicengine.h"
#include "ui_musicengine.h"
#include "library.h"
#include "ui_library.h"
#include "musicvideo.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QString getCurrentSong();
    ~MainWindow();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

        void connectSignalsAndSlots();

    playlist *creation;
    QMediaPlayer *player;
    library *lib;
    musicEngine *engine;
    musicVideo *videoo;

    QString currentFileClicked;
    QString currentSong;
    QString nextSong;
    QString previousSong;
    QString currentSongName;
    QString nextSongName;
    QString previousSongName;

    QStringList list;
    QStringList list1;
    QStringList list2;
    QStringList list3;
    QStringList list4;

    int pos;

    void updateSongName();





private slots:
    void configurePlaylist(bool clicked);
    void test(int row,int col);
    void update();
    void createLibrary();
    void playCurrentSong();
    void pause();
    void resume();
    void maybe();
    void video();
    void previous();
    void next();
    void changeVolume(int number);
    void songSliderLength(qint64 length);
    void songSliderPos(qint64 pos);
    void on_songStamp_sliderMoved(int value);

};

#endif // MAINWINDOW_H
