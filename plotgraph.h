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
    /*!
     * \brief plotGraph. Default constructor.
     */
    plotGraph() : scene(NULL) {}
    /*!
     * \brief plotGraph. Constructor.
     * \param _scene
     */
    plotGraph(QGraphicsScene *_scene) : scene(_scene) {}
    //Abstract paint.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //Abstract boundingRect
    QRectF boundingRect() const;
    void setXaxis(qint64 minVal,qint64 maxVal);
    void setYaxis(qreal minVal,qreal maxVal);
    /*!
     * \brief plotGraph::setXsticks.
     *
     * Sets the number of sticks in the x axis.
     * \param nSticks
     */
    void setXsticks(int nSticks) {nx=nSticks;}

    /*!
     * \brief plotGraph::setYsticks.
     *
     * Sets the number of sticks in the y axis.
     * \param nSticks
     */
    void setYsticks(int nSticks) {ny=nSticks;}

    /*!
     * \brief plotGraph::linkData.
     *
     * Links the data being plotted with the data vector that is being acquired from the port.
     * \param dat
     */
    void linkData(const QVector<QPair<qint64, qreal> > *dat) {data=dat;}
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
