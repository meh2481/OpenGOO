#include "mainwidget.h"
#include <QDebug>



MainWidget::MainWidget(QRect geometry,bool debug,QWidget *parent)
    : QMainWindow(parent)
{
    this->showFullScreen();//To have the game full screen
    this->setGeometry(geometry);
    this->geometry=geometry;
    this->debug=debug;
    levelS=new levelSelector(geometry,this);//Create the level selector
    levelS->show();//Show the level selector

    connect(levelS,SIGNAL(closing()),this,SLOT(close())); //Connect the closing of the levelSelector with the closing of the game
    connect(levelS,SIGNAL(eventLevelSelected()),this,SLOT(levelSelected()));//Connect the choose of the the level to the creation of the level

}

MainWidget::~MainWidget()
{
    delete levelS;
    delete level;
}

void MainWidget::levelSelected()//Create the level selected
{
    if(debug)qWarning()<<"Level Selected "<<levelS->getLevelSelected().toAscii();
    if(levelS->getLevelSelected().isEmpty())
        this->close();
    else
    {
        level=new Level(geometry,levelS->getLevelSelected(),STANDARD,this);//Create the level
        if (!debug)
                level=new Level(geometry,levelS->getLevelSelected(),STANDARD,this); //Create the level
            else{
                level=new Level(geometry,levelS->getLevelSelected(),DEBUG,this); //Create the level
                qWarning()<<"Level object created";
            }
        level->show();//Show the Level
        connect(level,SIGNAL(closing()),this,SLOT(close()));//Connect the closing of the level with the closing of the game
        if (debug) qWarning()<<"level showed an signal connected.";
    }
}
