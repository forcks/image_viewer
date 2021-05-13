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

public slots:
    void showPathToImage(QString path);

    void saveSizeWindowWhenOpened(QString x,QString y);
    void deleteConfig();
signals:
    void setPathToImage(QString pathToImage);
    void loadWindowsSize(QString x,QString y);

private:
    QJsonObject config;


};

#endif // APPENGINE_H
