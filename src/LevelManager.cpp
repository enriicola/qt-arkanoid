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
    m_levels.clear();
    
    // Try to load levels from Qt resources first
    QStringList resourceLevels = {
        ":/levels/resources/levels/level1.json",
        ":/levels/resources/levels/level2.json",
        ":/levels/resources/levels/level3.json"
    };
    
    bool anyLoaded = false;
    for (const QString &resourcePath : resourceLevels) {
        QFile file(resourcePath);
        if (!file.exists()) {
            qWarning() << "Resource level file not found:" << resourcePath;
            continue;
        }
        
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open resource level:" << resourcePath << file.errorString();
            continue;
        }
        
        auto level = std::make_unique<Level>();
        if (level->loadFromJson(resourcePath)) {
            m_levels.push_back(std::move(level));
            anyLoaded = true;
            qDebug() << "Loaded level from resource:" << resourcePath;
        } else {
            qWarning() << "Failed to parse level from resource:" << resourcePath;
        }
    }
    
    // Fallback: Try to load from external directory
    if (!anyLoaded) {
        QString levelsDir = QCoreApplication::applicationDirPath() + "/levels";
        QDir dir(levelsDir);
        
        if (dir.exists()) {
            QStringList filters;
            filters << "level*.json";
            QStringList levelFiles = dir.entryList(filters, QDir::Files, QDir::Name);
            
            for (const QString &filename : levelFiles) {
                QString filePath = dir.filePath(filename);
                QFile file(filePath);
                
                if (!file.open(QIODevice::ReadOnly)) {
                    qWarning() << "Failed to open level file:" << filePath << file.errorString();
                    continue;
                }
                
                auto level = std::make_unique<Level>();
                if (level->loadFromJson(filePath)) {
                    m_levels.push_back(std::move(level));
                    anyLoaded = true;
                    qDebug() << "Loaded level from file:" << filePath;
                } else {
                    qWarning() << "Failed to parse level file:" << filePath;
                }
            }
        }
    }
    
    // Last resort: Create default levels programmatically
    if (!anyLoaded) {
        qWarning() << "No levels found in resources or files, creating default levels";
        createDefaultLevels();
        return !m_levels.empty();
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
