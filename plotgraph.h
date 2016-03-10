#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QPair>
#include <QVector>

class plotGraph : public QGraphicsItem
{
public:
    plotGraph();
    //Abstract paint.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //Abstract boundingRect
    QRectF boundingRect() const;
    void setXaxis(qreal minVal,qreal maxVal);
    void setYaxis(qreal minVal,qreal maxVal);
    void setXsticks(int nSticks);
    void setYsticks(int nSticks);
    void linkData(const QVector<QPair<qreal,qreal> > *dat);

private:
    void paintAxis(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void plotData(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint real2Coord(const QPair<qreal,qreal> dpoint);
    QRect bRect=QRect(0,0,0,0);
    QPoint origin, rightX,upperY;

    const int axisMargin=40;
    qreal xmin=0;
    qreal xmax=1;
    qreal ymin=0;
    qreal ymax=1;
    int nx=2;
    int ny=2;
    const QVector<QPair<qreal,qreal> > *data=NULL;
};

#endif // PLOTGRAPH_H
