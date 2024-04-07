#ifndef DAO_H
#define DAO_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlTableModel>

class DAO : public QObject
{
    Q_OBJECT
public:
    DAO(); //Data Access Object
signals:

    void update_status(bool);

public slots:

    void test_query(QString);
};

#endif // DAO_H
