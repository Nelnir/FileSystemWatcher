#ifndef EVENT_H
#define EVENT_H

#include <QtGlobal>

enum class EventType{
    Created,
    Deleted,
    Edited
};

enum class FileType{
    Directory,
    File
};

class Event
{
public:
    Event(const EventType& type, const FileType& file_type, const quint64& timestamp);
private:
    EventType m_type;
    FileType m_file_type;
    quint64 m_timestamp;
};

#endif // EVENT_H
