#ifndef AIRCRAFT_ITEM_H
#define AIRCRAFT_ITEM_H

#include "map_item.h"
#include "graphics_aircraft.h"
#include "graphics_text.h"
#include "QGraphicsTextItem"
#include "graphics_track.h"
#include "graphics_icon.h"
#include "aircraft_watcher.h"

class AircraftItem : public MapItem
{
    Q_OBJECT
public:
    explicit AircraftItem(Point2DLatLon pt, QString ac_id, double neutral_scale_zoom = 15, QObject *parent = nullptr);

    virtual void setHighlighted(bool h);
    virtual void updateZValue();
    virtual void setForbidHighlight(bool fh);
    virtual void setEditable(bool ed){(void)ed;}
    virtual void removeFromScene(MapWidget* map);
    virtual void addToMap(MapWidget* mw);

    void setPosition(Point2DLatLon pt);
    void setHeading(double h);
    void clearTrack();

signals:

public slots:

protected:
    virtual void updateGraphics(MapWidget* map, uint32_t update_event);
    void handle_bat_alarm(AircraftWatcher::BatStatus bs);

private:
    GraphicsAircraft* graphics_aircraft;
    GraphicsText* graphics_text;
    QGraphicsItemGroup* alarms;
    GraphicsIcon* bat_alarm;

    Point2DLatLon latlon;
    double heading;
    QList<GraphicsTrack*> graphics_tracks;

    QColor color_idle;
    QColor color_unfocused;

    QList<QList<Point2DLatLon>> track_chuncks;

    int last_chunk_index;
};

#endif // AIRCRAFT_ITEM_H
