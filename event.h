#ifndef EVENT_H
#define EVENT_H

#include <QtGlobal>
#include <QString>

enum class EventType{
    Created,
    Deleted,
    Edited,
    Renamed
};

enum class FileType{
    Directory,
    File
};

class Event
{
public:
    Event(const EventType& type, const QString& path, const FileType& file_type);
    QString event_type();
    QString path();
    QString file_type();
    QString timestamp();
private:
    EventType m_type;
    QString m_path;
    FileType m_file_type;
    quint64 m_timestamp;
};

#endif // EVENT_H
