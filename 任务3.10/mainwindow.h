#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "videosurface.h"
#include <QVideoFrame>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onShowImage(QVideoFrame frame);

private slots:
    void on_openBtnOne_clicked();

    void on_playBtnOne_clicked();

    void on_stopBtnOne_clicked();

    void on_snapBtnOne_clicked();

    void on_openBtnTwo_clicked();

    void on_playBtnTwo_clicked();

    void on_stopBtnTwo_clicked();

    void on_snapBtnTwo_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* m_pplayerOne;
    QVideoWidget * m_pWgtOne;
    QMediaPlayer* m_pplayerTwo;
    QVideoWidget * m_pWgtTwo;
//    QMediaPlaylist *playlist;

    VideoSurface *m_videoSurfaceOne;
    //VideoSurface *m_videoSurfaceTwo;
};
#endif // MAINWINDOW_H
