#include "mangapanda.h"

MangaPanda::MangaPanda(NetworkManager *dm) : AbstractMangaSource(dm)
{
    name = "MangaPanda";
    baseurl = "http://www.mangapanda.com";
    dictionaryUrl = baseurl + "/popular/";
}

bool MangaPanda::uptareMangaList(UpdateProgressToken *token)
{
    QRegularExpression mangarx(R"lit(<a href="(/[^"]+)">([^<]+)<)lit");

    QRegularExpression numpagesrx(R"lit(href="/popular/(\d+)">Last)lit");

    auto job = networkManager->downloadAsString(dictionaryUrl);

    if (!job->await(10000))
    {
        token->sendError(job->errorString);
        return false;
    }

    token->sendProgress(10);

    QElapsedTimer timer;
    timer.start();

    auto numpagesrxmatch = numpagesrx.match(job->buffer);

    MangaList mangas;
    mangas.absoluteUrls = false;
    int pages = 1;

    if (numpagesrxmatch.hasMatch())
        pages = numpagesrxmatch.captured(1).toInt() / 30 + 1;
    qDebug() << "pages:" << pages;

    const int matchesPerPage = 30;
    auto lambda = [&](QSharedPointer<DownloadStringJob> job) {
        int spos = job->buffer.indexOf(R"(id="mangaresults")");
        int epos = job->buffer.indexOf(R"(id="navigator")");

        int matches = 0;
        for (auto &match : getAllRxMatches(mangarx, job->buffer, spos, epos))
        {
            auto title = htmlToPlainText(match.captured(2));
            auto url = match.captured(1);
            mangas.append(title, url);
            matches++;
        }

        token->sendProgress(10 + 90 * (mangas.size / matchesPerPage) / pages);
        qDebug() << "matches:" << matches;
        if (matches < matchesPerPage)
            qDebug() << "          Incomplete match in page:" << job->url;
    };

    lambda(job);

    QList<QString> urls;
    for (int i = 1; i < pages; i++)
        urls.append(dictionaryUrl + QString::number(i * 30));

    DownloadQueue queue(networkManager, urls, CONF.parallelDownloadsHigh, lambda, true);
    queue.setCancellationToken(&token->canceled);
    queue.start();
    if (!queue.awaitCompletion())
    {
        token->sendError(queue.lastErrorMessage);
        return false;
    }
    this->mangaList = mangas;

    qDebug() << "mangas:" << mangas.size << "time:" << timer.elapsed();

    token->sendProgress(100);

    return true;
}

void MangaPanda::updateMangaInfoFinishedLoading(QSharedPointer<DownloadStringJob> job,
                                                QSharedPointer<MangaInfo> info)
{
    //    QRegularExpression titlerx(R"(<h2 class="aname">([^<]*))");
    QRegularExpression authorrx("Author:</td>[^>]*>([^<]*)");
    QRegularExpression artistrx("Artist:</td>[^>]*>([^<]*)");
    QRegularExpression statusrx("Status:</td>[^>]*>([^<]*)");
    QRegularExpression yearrx("Year of Release:</td>[^>]*>([^<]*)");
    QRegularExpression genresrx("Genre:</td>(.*?)</td>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpression summaryrx(R"(<div id="readmangasum">.*?<p>(.*?)</p>)",
                                 QRegularExpression::DotMatchesEverythingOption);
    QRegularExpression coverrx(R"(<div id="mangaimg"><img src="([^"]*))");

    QRegularExpression chapterrx(R"lit(<a href="([^"]*)"[^>]*>([^<]*)</a>([^<]*))lit");

    fillMangaInfo(info, job->buffer, authorrx, artistrx, statusrx, yearrx, genresrx, summaryrx, coverrx);

    int spos = job->buffer.indexOf(R"(<div id="chapterlist">)");
    int epos = job->buffer.indexOf(R"(<div id="adfooter">)", spos);

    MangaChapterCollection newchapters;
    for (auto &chapterrxmatch : getAllRxMatches(chapterrx, job->buffer, spos, epos))
    {
        auto ctitle = chapterrxmatch.captured(2);
        if (chapterrxmatch.captured(3) != " : ")
            ctitle += chapterrxmatch.captured(3);
        auto curl = baseurl + chapterrxmatch.captured(1);
        newchapters.append(MangaChapter(ctitle, curl));
    }
    info->chapters.mergeChapters(newchapters);
}

Result<QStringList, QString> MangaPanda::getPageList(const QString &chapterUrl)
{
    QRegularExpression pagerx(R"lit(<option value="([^"]*)")lit");

    auto job = networkManager->downloadAsString(chapterUrl);

    if (!job->await(7000))
        return Err(job->errorString);

    int spos = job->buffer.indexOf(R"(<select id="pageMenu")");
    int epos = job->buffer.indexOf("</select>", spos);

    QStringList pageUrls;
    for (auto &match : getAllRxMatches(pagerx, job->buffer, spos, epos))
    {
        pageUrls.append(baseurl + match.captured(1));
    }

    return Ok(pageUrls);
}

Result<QString, QString> MangaPanda::getImageUrl(const QString &pageUrl)
{
    QRegularExpression imagerx(R"lit(<img id="img"[^>]*src="([^"]*)")lit");

    auto job = networkManager->downloadAsString(pageUrl);

    if (!job->await(7000))
        return Err(job->errorString);

    auto match = imagerx.match(job->buffer);

    if (!match.hasMatch())
        return Err(QString("Couldn't process pages/images."));

    auto imageUrl = match.captured(1);

    return Ok(imageUrl);
}
