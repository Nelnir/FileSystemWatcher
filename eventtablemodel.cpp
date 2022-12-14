#include "eventtablemodel.h"

EventTableModel::EventTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant EventTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(section){
        case 0: return "Even Type";
        case 1: return "Path";
        case 2: return "Is folder";
        case 3: return "Timestamp";
    }
}

bool EventTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int EventTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int EventTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant EventTableModel::data(const QModelIndex &index, int role) const
{
    auto event = m_data[index.row()];
    switch(index.column()){
    case 0: return event.event_type();
    case 1: return event.path();
    case 2: return event.file_type();
    case 3: return event.timestamp();
    }
}

bool EventTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags EventTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool EventTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

bool EventTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    endInsertColumns();
    return true;
}

bool EventTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}

bool EventTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    endRemoveColumns();
    return true;
}

void EventTableModel::add_event(const Event &event)
{
    m_data.push_back(event);
    insertRows(0, 1);
}
