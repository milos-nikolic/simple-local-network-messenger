#include "beaconservice.h"

beaconService::beaconService()
{

}
void beaconService::run()
{
    while(1)
	{
		QThread::msleep(500);
		emit timerInterupt();
    }
}
