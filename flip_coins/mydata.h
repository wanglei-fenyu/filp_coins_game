#ifndef MYDATA_H
#define MYDATA_H

#include <QObject>
#include<QMap>
#include<QVector>
class mydata : public QObject
{
    Q_OBJECT
public:
    explicit mydata(QObject *parent = nullptr);
public:
    QMap<int,QVector<QVector<int>>> mData ;

signals:

public slots:
};

#endif // MYDATA_H
