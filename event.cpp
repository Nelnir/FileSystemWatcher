#include "event.h"
#include <QDateTime>
Event::Event(const EventType& type, const QString& path, const FileType& file_type) : m_type(type),
    m_path(path),
    m_file_type(file_type)
{
    m_timestamp = QDateTime::currentMSecsSinceEpoch();
}

QString Event::event_type()
{
    switch(m_type){
    case EventType::Created: return "Created";
    case EventType::Deleted: return "Deleted";
    case EventType::Edited: return "Edited";
    case EventType::Renamed: return "Renamed";
    }
}

QString Event::path()
{
    return m_path;
}

QString Event::file_type()
{
    return m_file_type == FileType::Directory ? "Yes" : "No";
}

QString Event::timestamp()
{
    return QDateTime::fromMSecsSinceEpoch(m_timestamp).toString();
}
