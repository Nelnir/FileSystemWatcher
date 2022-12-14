#include "mywatcher.h"
#include <QDebug>
#include <QDirIterator>
#include <set>

MyWatcher::MyWatcher(QObject *parent)
    : QFileSystemWatcher{parent}
{

}


bool MyWatcher::addPath(const QString& file)
{
    init(file);
    return QFileSystemWatcher::addPath(file);
}

bool MyWatcher::removePath(const QString& file)
{
    if(QFileInfo(file).isDir()){
        for(auto& y : m_data.find(file)->second){
            QFileSystemWatcher::removePath(y.first);
        }
    }
    return QFileSystemWatcher::removePath(file);
}

void MyWatcher::start_watching()
{
    QObject::connect(this, &QFileSystemWatcher::directoryChanged, this, &MyWatcher::analyze);
}

void MyWatcher::stop_watching()
{
    QObject::disconnect(this, &QFileSystemWatcher::directoryChanged, this, &MyWatcher::analyze);
}

void MyWatcher::analyze(const QString &path)
{
    auto& data = m_data.find(path)->second;
    for(auto& x : data){
        x.second.m_to_delete = true;
    }
    QVector<std::pair<QString, quint64>> new_files;
    QDirIterator it(path);
    while (it.hasNext()){
        QString file = it.next();
        if(file.endsWith("..") || file.endsWith(".")) continue;
        QFileInfo info(file);
        auto itr = data.find(file);
        if(itr != data.end()){
            itr->second.m_to_delete = false;
            if(info.size() != itr->second.m_size){
                itr->second.m_size = info.size();
                emit file_edited(file, itr->second.m_type);
            }
        } else{
            new_files.append(std::make_pair(file, info.size()));
        }
    }
    QStringList to_delete;
    QList<std::pair<QString, QString>> renamed;
    for(auto& x : data){
        for(auto itr = new_files.begin(); itr != new_files.end();){
            // currently im using simple size eq, but crc here could be implemented
            if(x.second.m_to_delete && x.second.m_size == itr->second){
                x.second.m_to_delete = false;
                renamed.append(std::make_pair(itr->first, x.first));
                itr = new_files.erase(itr);
            } else{
                ++itr;
            }
        }
        if(x.second.m_to_delete){
            to_delete.append(x.first);
        }
    }

    for(auto& x : new_files){
        QFileSystemWatcher::addPath(x.first);
        QFileInfo info(x.first);
        FileData fdata;
        fdata.m_size = x.second;
        fdata.m_type = info.isDir() ? FileType::Directory : FileType::File;
        emit file_added(x.first, fdata.m_type);
        data.emplace(x.first, fdata);
        if(info.isDir()){
            m_data.emplace(x.first, FilesData());
        }
    }

    for(auto& x : renamed){
        if(QFileInfo(x.first).isDir()){
            auto itr = m_data.emplace(x.first, FilesData());
            for(auto& y : m_data.find(x.second)->second){
                QString new_file = x.first + y.first.sliced(y.first.lastIndexOf('/'));
                QFileSystemWatcher::addPath(new_file);
                itr.first->second.emplace(new_file, y.second);
            }
            m_data.erase(x.second);
        }
       // emit file_renamed(x.first, x.second);
        auto info = data.find(x.second)->second;
        emit file_renamed(x.first, info.m_type);
        data.emplace(x.first, info);
        data.erase(x.second);
        removePath(x.second);
        QFileSystemWatcher::addPath(x.first);
    }

    for(auto& x : to_delete){
        emit file_deleted(x, data.find(x)->second.m_type);
        data.erase(x);
        QFileSystemWatcher::removePath(x);
    }
}

void MyWatcher::init(const QString &path)
{
    m_data.emplace(path, FilesData());
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()){
        QString file = it.next();
        if(file.endsWith("..") || file.endsWith(".")) continue;
        QFileInfo info(file);
        FileData data;
        data.m_size = info.size();
        data.m_type = info.isDir() ? FileType::Directory : FileType::File;
        auto itr = m_data.emplace(file.sliced(0, file.lastIndexOf('/')), FilesData());
        if(info.isDir()){
            itr.first->second.emplace(file, data);
            m_data.emplace(file, FilesData());
        } else{
            itr.first->second.emplace(file, data);
        }
        QFileSystemWatcher::addPath(file);
    }
}
