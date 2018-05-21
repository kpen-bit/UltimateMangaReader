#ifndef MANGAPANDA_H
#define MANGAPANDA_H

#include "abstractmangasource.h"
#include "mangachapter.h"
#include "mangainfo.h"

class MangaPanda : public AbstractMangaSource
{
public:

    MangaPanda(QObject *parent, DownloadManager *dm);

    bool updateMangaList();
    MangaInfo *getMangaInfo(QString mangalink);
    QStringList *getPageList(QString chapterlink);
    QString getImageLink(QString pagelink);

protected:


};

#endif // MANGAPANDA_H