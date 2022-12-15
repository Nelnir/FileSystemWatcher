#include "controller.h"
#include <thread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QEventLoop>

Controller::Controller(QObject *parent) : QObject(parent)
{
    QObject::connect(&m_watcher, &MyWatcher::file_added, this, [&](const QString& file, const FileType& file_type){
        add_event(EventType::Created, file, file_type);
    });
    QObject::connect(&m_watcher, &MyWatcher::file_deleted, this, [&](const QString& file, const FileType& file_type){
        add_event(EventType::Deleted, file, file_type);
        start_download(file);
    });
    QObject::connect(&m_watcher, &MyWatcher::file_renamed, this, [&](const QString& file, const FileType& file_type){
        add_event(EventType::Renamed, file, file_type);
    });
    QObject::connect(&m_watcher, &MyWatcher::file_edited, this, [&](const QString& file, const FileType& file_type){
        add_event(EventType::Edited, file, file_type);
    });
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

void Controller::remove_path(const int& index)
{
    if(m_model.isEmpty()) return;
    m_watcher.removePath(m_model.at(index));
    m_model.remove(index);
    emit model_changed();
}

void Controller::set_event_model(EventTableModel *model)
{
    m_event_model = model;
}

void Controller::start_watching()
{
    m_watcher.start_watching();
}

void Controller::stop_watching()
{
    m_watcher.stop_watching();
}

void Controller::add_event(const EventType& type, const QString& path, const FileType& ftype)
{
    m_event_model->add_event(Event(type, path, ftype));
}

void Controller::start_download(const QString& namee)
{
    std::thread([&](){
        QString name = namee;
        QNetworkAccessManager net;
        auto reply = net.get(QNetworkRequest(QUrl("https://cataas.com/cat/says/hello%20world!")));
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        QFile file(name.sliced(0, name.indexOf(".")) + ".gif");
        file.open(QIODevice::WriteOnly);
        file.write(reply->readAll());
        file.close();
    }).detach();
}
