#include "aircraft.h"
#include "pprz_dispatcher.h"
#include "dispatcher_ui.h"
#include <QDebug>
#include "AircraftManager.h"

Aircraft::Aircraft(ConfigData* config, QObject* parent): QObject(parent),
    ac_id(config->getId()), color(config->getColor()), _name(config->getName()), position(Point2DLatLon(0,0))
{
    QSettings app_settings(qApp->property("SETTINGS_PATH").toString(), QSettings::IniFormat);
    flight_plan = new FlightPlan(config->getFlightPlan(), this);
    setting_menu = make_shared<SettingMenu>(config->getSettings());
    airframe = Airframe(config->getAirframe());
    icon = app_settings.value("path/aircraft_icon").toString() + "/" + QString(airframe.getIconName()) + ".svg";
    status = new AircraftStatus(ac_id, this);
}

void Aircraft::setSetting(shared_ptr<Setting> setting, float value) {
    auto coef = setting->getAltUnitCoef();
    if(value < setting->getMin() / coef || value > setting->getMax() / coef) {
        qDebug() << "Warning: send setting value " << value << ", out of bounds for setting " << setting->getName();
    }

    pprzlink::Message dlSetting(PprzDispatcher::get()->getDict()->getDefinition("DL_SETTING"));
    dlSetting.addField("ac_id", ac_id);
    dlSetting.addField("index", setting->getNo());
    dlSetting.addField("value", value);
    PprzDispatcher::get()->sendMessage(dlSetting);
}

void Aircraft::setSetting(uint8_t setting_no, float value) {
    for(auto set: setting_menu->getAllSettings()) {
        if(set->getNo() == setting_no) {
            setSetting(set, value);
            break;
        }
    }
}
