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
Q_SIGNALS:
    void file_renamed(const QString& new_filename, const QString& old_filename);
    void file_edited(const QString& file);
    void file_deleted(const QString& file);
    void file_added(const QString& file);
private:
    void analyze(const QString& path);
    void init(const QString& path);
private:
    std::unordered_map<QString, FilesData> m_data;
};

#endif // MYWATCHER_H
