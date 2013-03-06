#ifndef WOG_LEVEL_H
#define WOG_LEVEL_H

#include <QPointF>
#include <QString>
#include <QList>
#include <QColor>

struct WOGPoi
{
    QPointF position;
    float traveltime;
    float pause;
    float zoom;
};

struct WOGCamera
{
    QString aspect;
    QPointF endpos;
    float endzoom;
    QList<WOGPoi*> poi;

    ~WOGCamera();
};

struct WOGMusic { QString id; };

typedef WOGMusic WOGLoopSound;

struct WOGBallInstance
{
    QString type;
    QString id;
    float x;
    float y;
    float angle;
    bool discovered;
};

struct WOGLevelExit
{
    QString id;
    QPointF pos;
    float radius;
    QString filter;
};

struct WOGPipe
{
    QString id;
    float depth;
    QList<QPointF> vertex;
};

struct WOGStrand
{
    QString gb1;
    QString gb2;
};


struct WOGLevel
{
    int ballsrequired;
    bool letterboxed;
    bool visualdebug;
    bool autobounds;
    QColor textcolor;
    bool texteffects;
    float timebugprobability;
    bool strandgeom;
    bool allowskip;
    QList<WOGCamera*> camera;
    WOGMusic music;
    QList<WOGBallInstance*> ball;
    WOGLevelExit* levelexit;
    QList<WOGStrand*> strand;
    WOGPipe pipe;

    WOGLevel() : levelexit(0) { }
    ~WOGLevel();
};

#endif // WOG_LEVEL_H
