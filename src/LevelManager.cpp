#include "LevelManager.h"
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

LevelManager::LevelManager(QObject *parent)
    : QObject(parent), m_currentLevel(1), m_highestUnlockedLevel(1),
      m_settings("QtArkanoid", "Arkanoid")
{
    loadProgress();
    createDefaultLevels();
}

bool LevelManager::loadLevels()
{
    // Try to load levels from JSON files in a levels directory
    QString levelsDir = QCoreApplication::applicationDirPath() + "/levels";
    QDir dir(levelsDir);
    
    if (!dir.exists()) {
        qDebug() << "Levels directory not found, using default levels";
        createDefaultLevels();
        return true;
    }
    
    m_levels.clear();
    
    // Load level files (level1.json, level2.json, etc.)
    QStringList filters;
    filters << "level*.json";
    QStringList levelFiles = dir.entryList(filters, QDir::Files, QDir::Name);
    
    for (const QString &filename : levelFiles) {
        QString filePath = dir.filePath(filename);
        auto level = std::make_unique<Level>();
        
        if (level->loadFromJson(filePath)) {
            m_levels.push_back(std::move(level));
        }
    }
    
    if (m_levels.empty()) {
        qDebug() << "No valid levels found, creating defaults";
        createDefaultLevels();
    }
    
    return !m_levels.empty();
}

void LevelManager::createDefaultLevels()
{
    m_levels.clear();
    createLevel1();
    createLevel2();
    createLevel3();
    createLevel4();
    createLevel5();
}

void LevelManager::createLevel1()
{
    auto level = std::make_unique<Level>();
    // Simple level with 5 rows of bricks
    // For now, create levels programmatically
    m_levels.push_back(std::move(level));
}

void LevelManager::createLevel2()
{
    auto level = std::make_unique<Level>();
    m_levels.push_back(std::move(level));
}

void LevelManager::createLevel3()
{
    auto level = std::make_unique<Level>();
    m_levels.push_back(std::move(level));
}

void LevelManager::createLevel4()
{
    auto level = std::make_unique<Level>();
    m_levels.push_back(std::move(level));
}

void LevelManager::createLevel5()
{
    auto level = std::make_unique<Level>();
    m_levels.push_back(std::move(level));
}

const Level* LevelManager::getCurrentLevel() const
{
    if (m_currentLevel > 0 && m_currentLevel <= static_cast<int>(m_levels.size())) {
        return m_levels[m_currentLevel - 1].get();
    }
    return nullptr;
}

bool LevelManager::nextLevel()
{
    if (m_currentLevel < static_cast<int>(m_levels.size())) {
        m_currentLevel++;
        if (m_currentLevel > m_highestUnlockedLevel) {
            m_highestUnlockedLevel = m_currentLevel;
            saveProgress();
        }
        return true;
    }
    return false;
}

void LevelManager::resetToLevel(int levelNumber)
{
    if (levelNumber > 0 && levelNumber <= static_cast<int>(m_levels.size())) {
        m_currentLevel = levelNumber;
    }
}

void LevelManager::saveProgress()
{
    m_settings.setValue("progress/currentLevel", m_currentLevel);
    m_settings.setValue("progress/highestUnlockedLevel", m_highestUnlockedLevel);
    m_settings.sync();
}

void LevelManager::loadProgress()
{
    m_currentLevel = m_settings.value("progress/currentLevel", 1).toInt();
    m_highestUnlockedLevel = m_settings.value("progress/highestUnlockedLevel", 1).toInt();
}

void LevelManager::unlockLevel(int levelNumber)
{
    if (levelNumber > m_highestUnlockedLevel) {
        m_highestUnlockedLevel = levelNumber;
        saveProgress();
    }
}
