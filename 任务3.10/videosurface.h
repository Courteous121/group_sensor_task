#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H
#include <QAbstractVideoSurface>
#include <QObject>
class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideoSurface(QObject *parent=0);

signals:
    void showImage(QVideoFrame frame);

protected:
    bool present(const QVideoFrame &frame);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType =
            QAbstractVideoBuffer::NoHandle) const;
};

#endif // VIDEOSURFACE_H
