#include "EngineWeather.h"
#include "..\core.h"

CEngineWeatherSettings* WeatherSettings;

CEngineWeatherSettings::CEngineWeatherSettings()
{

}

void CEngineWeatherSettings::SetRain(float power)
{
	CallMethod<0xB51EA0, CEngineWeatherSettings*, float>(this, power);
}

CEngineWeatherSettings* __fastcall HookEngineWeatherConstructor(CEngineWeatherSettings* ptr)
{
	CEngineWeatherSettings* ret = CallMethodAndReturn<CEngineWeatherSettings*, 0xB50FB0, CEngineWeatherSettings*>(ptr);
	WeatherSettings = ret;
	return ret;
}
