#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QSettings>
#include <vector>

struct HighScoreEntry
{
    QString name;
    int score;
    QDateTime date;
    
    HighScoreEntry(const QString &n = "", int s = 0, const QDateTime &d = QDateTime::currentDateTime())
        : name(n), score(s), date(d) {}
};

class HighScoreManager : public QObject
{
    Q_OBJECT

public:
    explicit HighScoreManager(QObject *parent = nullptr);
    
    bool isHighScore(int score) const;
    void addHighScore(const QString &name, int score);
    std::vector<HighScoreEntry> getHighScores() const;
    void clearHighScores();
    
    static constexpr int MAX_HIGH_SCORES = 10;

private:
    void loadHighScores();
    void saveHighScores();
    
    std::vector<HighScoreEntry> m_highScores;
    QSettings m_settings;
};

#endif
