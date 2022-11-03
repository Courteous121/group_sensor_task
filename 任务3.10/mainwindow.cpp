#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pplayerOne = new QMediaPlayer(this);
    m_pWgtOne = new QVideoWidget(ui->videoWgtOne);

    m_pplayerTwo = new QMediaPlayer(this);
    m_pWgtTwo = new QVideoWidget(ui->videoWgtTwo);

    m_videoSurfaceOne = new VideoSurface(this);
    //m_videoSurfaceTwo = new VideoSurface(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}
//将QvideoFrame格式转换为QImage格式
static QImage imageFromVideoFrame(const QVideoFrame& buffer)
{
    QImage img;
    QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(
                frame.pixelFormat());
    if (imageFormat != QImage::Format_Invalid) {
        img = QImage(frame.bits(),
                     frame.width(),
                     frame.height(),
                     // frame.bytesPerLine(),
                     imageFormat);
    } else {
        // e.g. JPEG
        int nbytes = frame.mappedBytes();
        img = QImage::fromData(frame.bits(), nbytes);
    }
    frame.unmap();
    return img;
}


void MainWindow::onShowImage(QVideoFrame frame)
{
    static int num = 1;
    if(sender() == m_videoSurfaceOne)
    {
        disconnect(m_videoSurfaceOne,SIGNAL(showImage(QVideoFrame)),
                this, SLOT(onShowImage(QVideoFrame)));

        QImage img = imageFromVideoFrame(frame);
        img.save(QString("frame%1.jpg").arg(num));
        m_pplayerOne->setVideoOutput(m_pWgtOne);
    }

    else{return;}
    num++;
}


void MainWindow::on_openBtnOne_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("open file"),tr(""),tr("video (*.mp4)"));


    m_pWgtOne->resize(1104, 622);
    m_pplayerOne->setMedia(QUrl::fromLocalFile(QFileInfo(fileName).absoluteFilePath()));
    m_pplayerOne->setVideoOutput(m_pWgtOne);
    m_pplayerOne->play();
}


void MainWindow::on_playBtnOne_clicked()
{
    m_pplayerOne->play();
}


void MainWindow::on_stopBtnOne_clicked()
{
    m_pplayerOne->pause();
}

#include <QDateTime>
#include <QScreen>
//保存截图
void MainWindow::on_snapBtnOne_clicked()
{
    m_pplayerOne->pause();
    // 保存整个屏幕为QPixmap
    QScreen *screen = QGuiApplication::primaryScreen();
    QString filePathName = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
    filePathName += ".png";

    QPixmap pixmap = screen->grabWindow(0);
    // 计算视频的位置和大小
    qDebug()<<"Full pixmap width: "<<pixmap.width()<<" height: "<<pixmap.height()<<endl;
    QRect geo = this->geometry();
    QRect appGeo = geo; // 整个应用程序在图片中的位置。

    geo = ui->videoWgtOne->geometry(); // 播放视频在图片中的位置。

    QWidget *centerWidget = centralWidget(); // QMainWindow在应用程序的位置
    QRect centerRect = centerWidget->geometry();
    qDebug()<<"center x: "<<centerRect.x()<<" y: "<<centerRect.y()<<" width: "<<centerRect.width()<<" height: "<<centerRect.height()<<endl;

    QRect copyGeo;
    copyGeo.setX(geo.x() + appGeo.x() + centerRect.x()); // x=三个x相加
    copyGeo.setY(geo.y() + appGeo.y() + centerRect.y());
    copyGeo.setWidth(geo.width());
    copyGeo.setHeight(geo.height());
    qDebug()<<"VW1 x: "<<copyGeo.x()<<" y: "<<copyGeo.y()<<" width: "<<copyGeo.width()<<" height: "<<copyGeo.height()<<endl;

    QPixmap pixmapCopy = pixmap.copy(copyGeo); // copy图片
    filePathName.prepend("Copy+");
    if(!pixmapCopy.save(filePathName,"png"))
    {
        qDebug()<<"copy cut save png failed"<<endl;
    }
        m_pplayerOne->play();
}


void MainWindow::on_openBtnTwo_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("open file"),tr(""),tr("video (*.mp4)"));

    m_pWgtTwo->resize(1104, 622);
    m_pplayerTwo->setMedia(QUrl::fromLocalFile(QFileInfo(fileName).absoluteFilePath()));
    m_pplayerTwo->setVideoOutput(m_pWgtTwo);
    m_pplayerTwo->play();
}


void MainWindow::on_playBtnTwo_clicked()
{
    m_pplayerTwo->play();
}


void MainWindow::on_stopBtnTwo_clicked()
{
    m_pplayerTwo->pause();
}


void MainWindow::on_snapBtnTwo_clicked()
{
    m_pplayerTwo->pause();
    // 保存整个屏幕为QPixmap
    QScreen *screen = QGuiApplication::primaryScreen();
    QString filePathName = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
    filePathName += ".png";

    QPixmap pixmap = screen->grabWindow(0);

    // 计算视频的位置和大小
    qDebug()<<"Full pixmap width: "<<pixmap.width()<<" height: "<<pixmap.height()<<endl;
    QRect geo = ui->videoWgtTwo->geometry(); // 播放视频在图片中的位置。
    qDebug()<<"VW x: "<<geo.x()<<" y: "<<geo.y()<<" width: "<<geo.width()<<" height: "<<geo.height()<<endl;

    QPoint leftop = ui->videoWgtTwo->mapToGlobal(QPoint(0,0));
    qDebug()<<"leftop x:"<<leftop.x()<<"lefttop y"<<leftop.y();

    QRect copyGeo;
//    copyGeo.setX(geo.x() + appGeo.x() + centerRect.x()+geo.width()*1.2); // x=三个x相加
//    copyGeo.setY(geo.y() + appGeo.y() + centerRect.y()*1.05);
    copyGeo.setX(leftop.x()); // x=三个x相加
    copyGeo.setY(leftop.y());
    copyGeo.setWidth(geo.width());
    copyGeo.setHeight(geo.height());
    qDebug()<<"VW1 x: "<<copyGeo.x()<<" y: "<<copyGeo.y()<<" width: "<<copyGeo.width()<<" height: "<<copyGeo.height()<<endl;

    QPixmap pixmapCopy = pixmap.copy(copyGeo); // copy图片
    filePathName.prepend("Copy+");
    if(!pixmapCopy.save(filePathName,"png"))
    {
        qDebug()<<"copy cut save png failed"<<endl;
    }
    m_pplayerTwo->play();
}

