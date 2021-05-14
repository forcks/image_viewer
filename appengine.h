#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <QJsonObject>

class AppEngine : public QObject
{
    Q_OBJECT
public:
    explicit AppEngine(QObject *parent = nullptr);

    QString XSizeWindow();
    QString YSizeWindow();

    QString folderPathToImage;
    QStringList images;
    QString nowImage;

public slots:
    void showPathToImage(QString path);
    void setFolderPath(QString pathToFolder,QString pathToFile);
    QStringList getFilesInFolder(QString path);

    void getPathToImage(QString path);

    void saveSizeWindowWhenOpened(QString x,QString y);
    void deleteConfig();

    void nextImage();
    void previousImage();

signals:
    void setPathToImage(QString pathToImage);
    void loadWindowsSize(QString x,QString y);

private:
    QJsonObject config;
    int nowImageIndex;


};

#endif // APPENGINE_H
