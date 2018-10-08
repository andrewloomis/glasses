#ifndef SWIPEMANAGER_H
#define SWIPEMANAGER_H

#include <QObject>

class SwipeManager : public QObject
{
    Q_OBJECT
//public:
//    SwipeManager(QObject* parent = nullptr);
//    ~SwipeManager();
//    void swipeLeft() { moveToLeft(); }
//    void swipeRight() { moveToRight(); }
//    using QObject::QObject;
//    explicit SwipeManager(QObject *parent = nullptr);
//private:

signals:
    void toRight();
    void toLeft();
public slots:
    void moveToRight(){
        emit toRight();
    }
    void moveToLeft(){
        emit toLeft();
    }
};

#endif // SWIPEMANAGER_H
