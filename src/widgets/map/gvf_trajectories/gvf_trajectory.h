#ifndef GVF_TRAJECTORY_H
#define GVF_TRAJECTORY_H

#include "coordinatestransform.h"
#include "AircraftManager.h"
#include "quiver_item.h"
#include "path_item.h"

constexpr int QUIVERS_NUMBER = 20;
constexpr float DEFAULT_AREA = 1000;

class GVF_trajectory : public QObject
{
    Q_OBJECT
public:
    explicit GVF_trajectory(QString id, Point2DLatLon origin, QList<float> gvf_settings);

    QuiverItem* getVField();
    PathItem* getTraj();

    void setVFiledVis(bool vis);

    void purge_trajectory();
    void update_trajectory();

    virtual void set_param(QList<float> param, int8_t _s, float _ke) = 0;

protected:
    QString ac_id;
    Point2DLatLon ltp_origin;
    QPointF xy_off;
    QPointF traj_grad;

    QList<QPointF> xy_mesh;
    QList<QPointF> vxy_mesh;

    void createTrajItem(QList<QPointF> points);
    void createVFieldItem(QList<QPointF> points, QList<QPointF> vpoints, float bound_area, float ref_area = 150);
    QList<QPointF> meshGrid(float area = DEFAULT_AREA, int xpoints_num = QUIVERS_NUMBER, int ypoints_num = QUIVERS_NUMBER);

    virtual void param_points() = 0;
    virtual void vector_field() = 0;

private:
    QObject* child;

    QuiverItem* field_item;
    PathItem* traj_item;
    QList<WaypointItem*> traj_waypoints;

    bool field_item_vis;
    bool traj_item_vis;
};

#endif // GVF_TRAJECTORY_H