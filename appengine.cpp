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
void AppEngine::showPathToImage(QString path){
    setPathToImage("file:///"+path);
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
    return val["x"].toString() == "" || val["x"].toString() == "0"?val["x"].toString() : "640";
}
QString AppEngine::YSizeWindow(){
    QJsonDocument json = loadJson(QDir::homePath()+"/config.json");

    QJsonObject LoJsonObj;
    LoJsonObj = json.object();
    QJsonValue val = LoJsonObj["Sizewindow"];

    return val["y"].toString() == "" || val["y"].toString() == "0"?val["y"].toString() : "480";
}

void AppEngine::deleteConfig(){
    QFile _config(QDir::homePath()+"/config.json");
    if(_config.exists())
        _config.remove();
}



