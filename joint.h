#ifndef JOINT_H
#define JOINT_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QPainter>

#include "goo.h"

class Joint : public QObject
{
    Q_OBJECT
public:
    explicit Joint(Goo* a,Goo* b, b2World * world,QObject *parent = 0); //cunstractor: the two goo to link and the phisical world
    void paint(QPainter &p); //Paint function
    //DEBUG PAINTER
    void paintDebug(QPainter &p);
    b2Joint* getJoint(); //To have acces at the material b2joint
    bool has(Goo*a,Goo*b); //To check if this joint link this two GOO
protected:
    b2DistanceJoint* joint; //The phisical joint
    Goo *a,*b; //the two linked goo
    virtual void status(); // function to check the status of the joint
signals:
    void destroyJoint(Joint *j); //SIGNAL FOR DESTROY THIS JOINT
public slots:

};

#endif // JOINT_H
