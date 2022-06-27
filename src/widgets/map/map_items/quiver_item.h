#ifndef QUIVERITEM_H
#define QUIVERITEM_H

#include "map_item.h"
#include "graphics_quiver.h"

class QuiverItem : public MapItem
{
    Q_OBJECT
public:
    QuiverItem(Point2DLatLon pos, Point2DLatLon vpos, QString id, double neutral_scale_zoom = 15, QObject *parent = nullptr);
    QuiverItem(QList<Point2DLatLon> pos, QList<Point2DLatLon> vpos, QString id, double neutral_scale_zoom = 15, QObject *parent = nullptr);
    virtual void addToMap(MapWidget* map) override;
    virtual void updateGraphics(MapWidget* map, uint32_t update_event) override;
    virtual void removeFromScene(MapWidget* map) override;
    virtual void setForbidHighlight(bool fh) override;
    virtual void setEditable(bool ed) override;
    virtual void updateZValue() override;

private:
    QList<GraphicsQuiver*> graphics_quiver_l;

    QList<Point2DLatLon> latlon_l;
    QList<Point2DLatLon> vlatlon_l;
    QList<double> distance_l;
    QList<double> azimut_l;
};

#endif // QUIVERITEM_H