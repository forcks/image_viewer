#include "appengine.h"
#include <QDir>
#include <QFileDialog>

AppEngine::AppEngine(QObject *parent) : QObject(parent)
{

}
void AppEngine::showPathToImage(QString path){
    setPathToImage("file:///"+path);
}
void AppEngine::searchPicture(){
    //QString pathToImage =  QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.png *.jpg *.jpeg *.raw *.tiff *.jp2 *.gif");
    //setPathToImage(pathToImage);
}
