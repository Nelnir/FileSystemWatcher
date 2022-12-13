#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mywatcher.h"
#include "event.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList model MEMBER m_model NOTIFY model_changed);
    Q_PROPERTY(QStringList event_model MEMBER m_event_model NOTIFY event_model_changed);
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    Q_INVOKABLE void add_folder(const QString& folder);
    Q_INVOKABLE void remove_last_folder();
signals:
    void model_changed();
    void event_model_changed();
private:
    void add_event();
private:
    QStringList m_model;
    MyWatcher m_watcher;
    QStringList m_event_model;
};

#endif // CONTROLLER_H
