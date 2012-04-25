#include "collisionlistener.h"
#include "target.h"
#include "thorn.h"

#include "tools.h"

#include <qmath.h>
#include <QDebug>

CollisionListener::CollisionListener(QObject *parent) :
    QObject(parent)
{
    //Nothing to do here (for now)
}

void CollisionListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold){
    //if (oldManifold->points==contact->GetManifold()->points) contact->SetEnabled(false); //To skip continuos contact
    Thorn *tha=static_cast<Thorn*>(contact->GetFixtureA()->GetUserData());
    Goo*a,*b; //for get the goo involved in the contact
    a=static_cast<Goo*>(contact->GetFixtureA()->GetUserData()); //Dynamic cast is for retrive (if any) the goo object of the first body involved
    b=static_cast<Goo*>(contact->GetFixtureB()->GetUserData()); //Dynamic cast is for retrive (if any) the goo object of the second body involved
    if (a&&b) { //If both bodies are goo
        if (a->isSleeping() && b->isSleeping()) {
            contact->SetEnabled(true);
            return;
        }
        if (!a->getPrevious()){  //if the first goo is falling down and the other is jointed with other one stop the falling
            if (b->hasJoint() && a->getTarget()!=b){
                a->setTarget(b);
            }
//            else if (b->getTarget()!=NULL && b->getTarget()!=a->getTarget()) {
//                a->setTarget(b->getTarget());
//            }
            contact->SetEnabled(false);
        }
        else if (!b->getPrevious()){ //if the second goo is falling down and the other is jointed with other one stop the falling
            if (a->hasJoint() && b->getTarget()!=a ){
                b->setTarget(a);
            }
//            else if (a->getTarget()!=NULL &&  a->getTarget()!=b->getTarget()){
//                b->setTarget(a->getTarget());
//            }
            contact->SetEnabled(false);
        }
        else if (b->isFalling() && a->isFalling() ) contact->SetEnabled(true);
        else contact->SetEnabled(false); //if the contact is between two Goo is ignored


    }
    else { //cas if the contact is not between two goo
        Target * t=NULL; //target
        Thorn* th=NULL; //thorn
        if (!b){ //if the second object isn't a goo
            t=static_cast<Target*>(contact->GetFixtureB()->GetBody()->GetUserData()); //check if is the target
            if (t==NULL){
                th=static_cast<Thorn*>(contact->GetFixtureB()->GetBody()->GetUserData());
                if (th!=NULL) a->destroyThis();
            }
        }
        else if (!a){ //if the first isn't a goo is the same of before!
            t=static_cast<Target*>(contact->GetFixtureA()->GetBody()->GetUserData()); //Check if is target
            //check if is a thorn
            if (t==NULL)  {
                th=static_cast<Thorn*>(contact->GetFixtureA()->GetBody()->GetUserData());
                if (tha!=NULL ) qWarning()<<"HERE";
            }

        }
        contact->SetEnabled(true); //contact is enabled here
    }

}

void CollisionListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){
    Goo*a,*b; //for get the goo involved in the contact
    a=static_cast<Goo*>(contact->GetFixtureA()->GetUserData()); //Dynamic cast is for retrive (if any) the goo object of the first body involved
    b=static_cast<Goo*>(contact->GetFixtureB()->GetUserData()); //Dynamic cast is for retrive (if any) the goo object of the second body involved
    if (!a){
        Target * t=NULL; //target
        Thorn* th=NULL; //thorn
        t=static_cast<Target*>(contact->GetFixtureA()->GetBody()->GetUserData()); //Check if is target
        //check if is a thorn
        if (t==NULL)  {
            th=static_cast<Thorn*>(contact->GetFixtureA()->GetBody()->GetUserData());
            if (!th&&contact->GetFixtureA()->GetBody()->GetType()==b2_staticBody) { //ELSE IS GROUND
                if (b){

                    b2Vec2 p;

                    //SOSTITUITION OF THE COLLISION POINT WITH MY BODY POINT
                    p=b->getVPosition();
                    //RETRIVE THE NORMAL OF THE COLLISION
                    b2Vec2 n=contact->GetManifold()->localNormal;
                    //NORMALY THE NORMAL IS CORRECT
                    //BUT I EXPERIMENTED SOME ERROR ALSO WITH THE NORMAL
                    //Compute the angle
                    float angle=atan2(n.y,n.x);
                    //Compute x,y of the vector
                    float px=20.0*cos(angle);
                    float py=20.0*sin(angle);
                    p.x-=px;
                    p.y-=py;

                    //END WORKAOROUND

                    if (b->hasJoint()) b->contactGround(toPoint(p));
                    else if (!b->isDragging()) b->contactGround();
                    else if (b->isDragging()) emit stopGOO(b->getPPosition()); //Advice to stop the goo
                }
            }
        }
    }
}
