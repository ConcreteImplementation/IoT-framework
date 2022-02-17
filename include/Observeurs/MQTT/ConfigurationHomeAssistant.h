#pragma once

class ConfigurationHomeAssistant {
private:
	char m_sujet  [ 75];
	char m_charge [200];

public:
	ConfigurationHomeAssistant(
		const char* p_guid,
		const char* p_type,
		const char* p_unite,
		const char* p_variable
	);
	const char* getSujet() const;
	const char* getCharge() const;
};