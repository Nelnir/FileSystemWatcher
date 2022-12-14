#ifndef MYWATCHER_H
#define MYWATCHER_H

#include <QFileSystemWatcher>
#include <unordered_map>
#include "event.h"

struct FileData{
    quint64 m_size;
    FileType m_type;
    bool m_to_delete;
};

using FilesData = std::unordered_map<QString, FileData>;

class MyWatcher : public QFileSystemWatcher
{
    Q_OBJECT
public:
    explicit MyWatcher(QObject *parent = nullptr);
    bool addPath(const QString& file);
    bool removePath(const QString& file);
    void start_watching();
    void stop_watching();
Q_SIGNALS:
    void file_renamed(const QString& new_filename, const FileType& file_type);
    void file_edited(const QString& file, const FileType& file_type);
    void file_deleted(const QString& file, const FileType& file_type);
    void file_added(const QString& file, const FileType& file_type);
private:
    void analyze(const QString& path);
    void init(const QString& path);
private:
    std::unordered_map<QString, FilesData> m_data;
};

#endif // MYWATCHER_H
