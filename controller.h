#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mywatcher.h"
#include "eventtablemodel.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList model MEMBER m_model NOTIFY model_changed);
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    Q_INVOKABLE void add_folder(const QString& folder);
    Q_INVOKABLE void remove_path(const int& index);
    Q_INVOKABLE void set_event_model(EventTableModel* model);
    Q_INVOKABLE void start_watching();
    Q_INVOKABLE void stop_watching();
signals:
    void model_changed();
private:
    void add_event(const EventType& type, const QString& path, const FileType& ftype);
    void start_download(const QString& file);
private:
    QStringList m_model;
    MyWatcher m_watcher;
    EventTableModel* m_event_model;
};

#endif // CONTROLLER_H
