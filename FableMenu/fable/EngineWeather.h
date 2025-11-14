#pragma once

class CEngineWeatherSettings {
public:
	void SetRain(float power);
};

extern CEngineWeatherSettings* WeatherSettings;

CEngineWeatherSettings* __fastcall HookEngineWeatherConstructor(CEngineWeatherSettings* ptr);
