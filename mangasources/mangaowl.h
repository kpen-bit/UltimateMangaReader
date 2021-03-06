#ifndef MANGAOWL_H
#define MANGAOWL_H

#include "abstractmangasource.h"
#include "mangainfo.h"

class MangaOwl : public AbstractMangaSource
{
public:
    explicit MangaOwl(NetworkManager *dm);

    bool uptareMangaList(UpdateProgressToken *token) override;
    void updateMangaInfoFinishedLoading(QSharedPointer<DownloadStringJob> job,
                                        QSharedPointer<MangaInfo> info) override;
    Result<QStringList, QString> getPageList(const QString &chapterUrl) override;

private:
    QString mangalistUrl;
};

#endif  // MANGAOWL_H
