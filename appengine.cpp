#include "appengine.h"

#include <QDebug>

#include <QFile>
#include <QDir>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QJsonDocument loadJson(QString fileName){
    QFile jsonFile(fileName);
    if(!jsonFile.exists()){
        if(jsonFile.open(QIODevice::WriteOnly)){
            jsonFile.write("");
        }
        jsonFile.close();
    }
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void saveJson(QJsonDocument document,QString fileName){
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

AppEngine::AppEngine(QObject *parent) : QObject(parent)
{

}

QStringList AppEngine::getFilesInFolder(QString path){
    QStringList images;
    QDir workingDir(path);
    workingDir.setFilter(QDir::Files);
    QFileInfoList folderitems = workingDir.entryInfoList();
    qDebug()<<folderitems;
    foreach(QFileInfo i,folderitems){
        //png *.jpg *.jpeg *.raw *.tiff *.jp2 *.gif
        if(i.suffix() == "png" || i.suffix() == "jpg" || i.suffix() == "jpeg" ||
                i.suffix() == "tiff" || i.suffix() == "jp2" || i.suffix() == "gif"){
            images.append(i.absoluteFilePath());
        }
    }

    return images;
}

void AppEngine::showPathToImage(QString path){
    setPathToImage("file:///"+path);

    //TODO: add function getFilesInFolder
}

void AppEngine::setFolderPath(QString pathToFolder,QString pathToFile){
    pathToFolder.remove(0,7);//delete file://
    folderPathToImage = pathToFolder;
    images = getFilesInFolder(pathToFolder);
    nowImage = pathToFile;

    pathToFile.remove(0,7);
    for(int i = 0;i < images.length();i++){
        if(images[i] == nowImage){
            nowImageIndex = i;
            break;
        }
    }
}



void AppEngine::saveSizeWindowWhenOpened(QString x,QString y){
    QJsonDocument json;
    json = loadJson(QDir::homePath()+"/config.json");
    qDebug()<<"Вот тут лежит конфиг : "<<QDir::homePath()+"/config.json";
    qDebug()<<json;
    QJsonObject LoJsonObj;
    LoJsonObj = json.object();

    QJsonObject jsonSizeWindow;
    jsonSizeWindow.insert("x",x);
    jsonSizeWindow.insert("y",y);

    LoJsonObj["Sizewindow"] = jsonSizeWindow;

    json.setObject(LoJsonObj);
    saveJson(json,QDir::homePath()+"/config.json");
}


QString AppEngine::XSizeWindow(){
    QJsonDocument json = loadJson(QDir::homePath()+"/config.json");

    QJsonObject LoJsonObj;
    LoJsonObj = json.object();
    QJsonValue val = LoJsonObj["Sizewindow"];
    return val["x"].toString() != "" && val["x"].toString() != "0"?val["x"].toString() : "640";
}
QString AppEngine::YSizeWindow(){
    QJsonDocument json = loadJson(QDir::homePath()+"/config.json");

    QJsonObject LoJsonObj;
    LoJsonObj = json.object();
    QJsonValue val = LoJsonObj["Sizewindow"];

    return val["y"].toString() != "" && val["y"].toString() != "0"?val["y"].toString() : "480";
}

void AppEngine::deleteConfig(){
    QFile _config(QDir::homePath()+"/config.json");
    if(_config.exists())
        _config.remove();
}

void AppEngine::nextImage(){
    if(nowImageIndex + 1 >= images.length())
        nowImageIndex = -1;
    nowImage = images[nowImageIndex+1];
    nowImageIndex++;
    showPathToImage(nowImage);

}
void AppEngine::previousImage(){
    if(nowImageIndex - 1 < 0)
        nowImageIndex = images.length();
    nowImage = images[nowImageIndex-1];
    nowImageIndex--;
    showPathToImage(nowImage);

}



