#include "removablegoo.h"
#include "tools.h"

//The constructor is not different at the Dynamic goo constructor
RemovableGoo::RemovableGoo(b2World *world, QPoint point, int radius, QObject *parent) :
    DynamicGoo(world,point,radius,parent)
{
    type=REMOVIBLE;
    color=QColor(188,211,95);
    secondaryColor=color;
}

//The only difference with dynamic goo is that the joint status is ignored.
bool RemovableGoo::isDragable(){
   return !isSleeping();
}


