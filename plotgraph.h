/*! \file plotgraph.h
*/

#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QPair>
#include <QVector>
#include <algorithm>
#include <QGraphicsScene>
/*! \class plotGraph
 * \brief The plotGraph class.
 *
 * This class graphs the values read from the multimeter versus the time.
 */
class plotGraph : public QGraphicsItem
{
    Q_GADGET
    Q_ENUMS(Units)
public:
    plotGraph();
    plotGraph(QGraphicsScene *scene);
    //Abstract paint.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //Abstract boundingRect
    QRectF boundingRect() const;
    void setXaxis(qint64 minVal,qint64 maxVal);
    void setYaxis(qreal minVal,qreal maxVal);
    void setXsticks(int nSticks);
    void setYsticks(int nSticks);
    void linkData(const QVector<QPair<qint64, qreal> > *dat);
    void setUnit(int U);
    void setScene(QGraphicsScene *scene);


private:
    void paintAxis(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void plotData(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void labelXaxis(QPainter *painter, QPoint &p1, QPoint &p2);
    void labelYaxis(QPainter *painter, QPoint &p1, QPoint &p2);
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
    const QVector<QPair<qint64,qreal> > *data=NULL;

    QString unit;
    QGraphicsScene *scene;
};

#endif // PLOTGRAPH_H
