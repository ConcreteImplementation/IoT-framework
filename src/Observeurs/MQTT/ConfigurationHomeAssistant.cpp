#include <ArduinoJson.h>

#include "Observeurs/MQTT/ConfigurationHomeAssistant.h"

#define SUJET "homeassistant/sensor/%s%s/config"


ConfigurationHomeAssistant::ConfigurationHomeAssistant(const char* p_guid, const char* p_type, const char* p_unite, const char* p_variable) {
	snprintf(m_sujet, 75, SUJET, p_guid, p_type);

	DynamicJsonDocument document(200);
	document["device_class"]        = p_type;
	document["name"]                = String(p_guid) + "-" + String(p_type);
	document["state_topic"]  				= p_guid;
	document["unit_of_measurement"] = p_unite;
	document["value_template"]      = "{{ value_json." + String(p_variable) + "|round(2, 'common') }}";
	
	serializeJson(document, m_charge);

	Serial.println(m_charge);
}


const char* ConfigurationHomeAssistant::getSujet()  const { return m_sujet; }
const char* ConfigurationHomeAssistant::getCharge() const { return m_charge; }