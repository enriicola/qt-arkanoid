#include "HighScoreManager.h"
#include <algorithm>

HighScoreManager::HighScoreManager(QObject *parent)
    : QObject(parent), m_settings("QtArkanoid", "Arkanoid")
{
    loadHighScores();
}

void HighScoreManager::loadHighScores()
{
    m_highScores.clear();
    
    int size = m_settings.beginReadArray("highscores");
    for (int i = 0; i < size; ++i) {
        m_settings.setArrayIndex(i);
        QString name = m_settings.value("name").toString();
        int score = m_settings.value("score").toInt();
        QDateTime date = m_settings.value("date").toDateTime();
        
        m_highScores.emplace_back(name, score, date);
    }
    m_settings.endArray();
    
    // Sort by score descending
    std::sort(m_highScores.begin(), m_highScores.end(),
              [](const HighScoreEntry &a, const HighScoreEntry &b) {
                  return a.score > b.score;
              });
}

void HighScoreManager::saveHighScores()
{
    m_settings.beginWriteArray("highscores");
    for (size_t i = 0; i < m_highScores.size(); ++i) {
        m_settings.setArrayIndex(static_cast<int>(i));
        m_settings.setValue("name", m_highScores[i].name);
        m_settings.setValue("score", m_highScores[i].score);
        m_settings.setValue("date", m_highScores[i].date);
    }
    m_settings.endArray();
    m_settings.sync();
}

bool HighScoreManager::isHighScore(int score) const
{
    if (m_highScores.size() < MAX_HIGH_SCORES) {
        return true;
    }
    return score > m_highScores.back().score;
}

void HighScoreManager::addHighScore(const QString &name, int score)
{
    m_highScores.emplace_back(name, score, QDateTime::currentDateTime());
    
    // Sort by score descending
    std::sort(m_highScores.begin(), m_highScores.end(),
              [](const HighScoreEntry &a, const HighScoreEntry &b) {
                  return a.score > b.score;
              });
    
    // Keep only top MAX_HIGH_SCORES
    if (m_highScores.size() > MAX_HIGH_SCORES) {
        m_highScores.resize(MAX_HIGH_SCORES);
    }
    
    saveHighScores();
}

std::vector<HighScoreEntry> HighScoreManager::getHighScores() const
{
    return m_highScores;
}

void HighScoreManager::clearHighScores()
{
    m_highScores.clear();
    saveHighScores();
}
