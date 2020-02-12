#ifndef MAP2D_H
#define MAP2D_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsTextItem>
#include "tileprovider.h"
#include "tileproviderconfig.h"
#include <QMap>
#include <math.h>
#include <QResizeEvent>

class Map2D : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Map2D(QString configFile, QWidget *parent = nullptr);
    void centerLatLon(Point2DLatLon latLon);
    void toggleTileProvider(QString providerName, bool enable, int zValue = 0, qreal opacity = 1);
    std::map<QString, TileProviderConfig*>* tileProviders() {return &sourceConfigs;}
    QList<QString> tileProvidersNames();
    void updateTiles();
    double zoom() {return _zoom;}
    int zoomLevel() {return static_cast<int>(ceil(_zoom));}
    void setZoom(double z);

signals:

public slots:


protected:
    virtual void wheelEvent(QWheelEvent* event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    Point2DTile tilePoint(QPointF scenePos, int zoom);
    QPointF scenePoint(Point2DTile tilePoint);
    QPointF scenePoint(Point2DLatLon latlon, int zoomLvl);
    Point2DLatLon latlonPoint(QPointF scenePos, int zoom);
    Point2DLatLon latlonFromView(QPoint viewPos, int zoom);
    double scaleFactor() {return pow(2, _zoom - zoomLevel());}

    QGraphicsScene* _scene;

private slots:
    void handleTile(TileItem*, TileItem*);


private:
    void loadConfig(QString filename);

    double numericZoom;
    double _zoom;
    int tileSize;
    double minZoom;
    double maxZoom;

    std::map<QString, TileProviderConfig*> sourceConfigs;
    std::map<QString, TileProvider*> tile_providers;

};

#endif // MAP2D_H
