#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <QTimer>
#include <pprzlink/IvyLink.h>
#include <pprzlink/Message.h>
#include <memory>
#include "PprzToolbox.h"
#include "PprzApplication.h"

class PprzDispatcher : public PprzTool
{
    Q_OBJECT
public:
    explicit PprzDispatcher(PprzApplication* app, PprzToolbox* toolbox);

    static PprzDispatcher* get() {
        return pprzApp()->toolbox()->pprzDispatcher();
    }

    virtual void setToolbox(PprzToolbox* toolbox) override;

    void start();

    void sendMessage(pprzlink::Message);
    std::shared_ptr<pprzlink::MessageDictionary> getDict() {return dict;}

    /**
     * @brief bind message to callback. Use it only for messages not handled by default by the application
     * @param msg_name
     * @param cb
     * @return
     */
    long bind(std::string msg_name, pprzlink::messageCallback_t cb);

    bool isSilent() {return silent_mode;}
    void setSilent(bool silent) {
        silent_mode = silent;
    }

signals:
    void aircraft_die(pprzlink::Message);
    void flight_param(pprzlink::Message);
    void ap_status(pprzlink::Message);
    void nav_status(pprzlink::Message);
    void circle_status(pprzlink::Message);
    void segment_status(pprzlink::Message);
    void engine_status(pprzlink::Message);
    void waypoint_moved(pprzlink::Message);
    void dl_values(pprzlink::Message);
    void telemetry_status(pprzlink::Message);
    void fly_by_wire(pprzlink::Message);
    void svsinfo(pprzlink::Message);


public slots:
    void requestAircrafts();

private:
    void updateSettings(pprzlink::Message msg);
    using sig_ptr_t = decltype(&PprzDispatcher::flight_param);

    void requestConfig(std::string ac_id);
    void bindDeftoSignal(std::string const &name, sig_ptr_t sig);

    std::shared_ptr<pprzlink::MessageDictionary> dict;
    std::unique_ptr<pprzlink::IvyLink> link;

    std::string pprzlink_id;

    bool first_msg;
    bool started;
    bool silent_mode;

    qint64 time_msg_server;
    QTimer server_check_timer;
};




#endif // DISPATCHER_H
