#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    QObject::connect(&m_watcher, &MyWatcher::file_added, this, [](const QString& file){qDebug()<<"ADDED: " << file;});
    QObject::connect(&m_watcher, &MyWatcher::file_deleted, this, [](const QString& file){qDebug()<<"DELETED: " << file;});
    QObject::connect(&m_watcher, &MyWatcher::file_renamed, this, [](const QString& file, const QString& old){qDebug()<<"RENAMED: " << file << " " << old;});
    QObject::connect(&m_watcher, &MyWatcher::file_edited, this, [](const QString& file){qDebug()<<"EDITED: " << file;});
}

Controller::~Controller()
{

}

void Controller::add_folder(const QString& folder)
{
    QString file = folder.sliced(8);
    m_watcher.addPath(file);
    m_model.append(file);
    emit model_changed();
}

void Controller::remove_last_folder()
{
    if(m_model.isEmpty()) return;
    m_watcher.removePath(m_model.back());
    m_model.pop_back();
    emit model_changed();
}

void Controller::add_event()
{

}
