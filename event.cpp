#include "event.h"

Event::Event(const EventType& type, const FileType& file_type, const quint64& timestamp) : m_type(type),
    m_file_type(file_type),
    m_timestamp(timestamp)
{

}
