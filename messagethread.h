#ifndef MESSAGETHREAD_H
#define MESSAGETHREAD_H

#include <QObject>
#include <QThread>
#include <iostream>

class messageThread : public QThread
{
     Q_OBJECT
public:
    messageThread();
private:
    void run();
signals:
 void enterMassage();
};

#endif // MESSAGETHREAD_H
