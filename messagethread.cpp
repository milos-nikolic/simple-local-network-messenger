#include "messagethread.h"

messageThread::messageThread()
{

}
void messageThread::run()
{
    while(1)
	{
		QThread::msleep(500);
		emit enterMassage();
    }
}
