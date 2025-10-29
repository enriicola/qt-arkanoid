#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <vector>
#include <memory>
#include "Level.h"

class LevelManager : public QObject
{
    Q_OBJECT

public:
    explicit LevelManager(QObject *parent = nullptr);
    
    bool loadLevels();
    void createDefaultLevels();
    
    int currentLevelNumber() const { return m_currentLevel; }
    int totalLevels() const { return static_cast<int>(m_levels.size()); }
    bool hasNextLevel() const { return m_currentLevel < static_cast<int>(m_levels.size()); }
    
    const Level* getCurrentLevel() const;
    bool nextLevel();
    void resetToLevel(int levelNumber);
    
    // Progress tracking
    void saveProgress();
    void loadProgress();
    int getHighestUnlockedLevel() const { return m_highestUnlockedLevel; }
    void unlockLevel(int levelNumber);

private:
    std::vector<std::unique_ptr<Level>> m_levels;
    int m_currentLevel;
    int m_highestUnlockedLevel;
    QSettings m_settings;
    
    void createLevel1();
    void createLevel2();
    void createLevel3();
    void createLevel4();
    void createLevel5();
};

#endif
