#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <QColor>
#include <vector>

struct BrickData
{
    int row;
    int col;
    QColor color;
    int hitPoints;
    
    BrickData(int r = 0, int c = 0, const QColor &clr = Qt::white, int hp = 1)
        : row(r), col(c), color(clr), hitPoints(hp) {}
};

class Level
{
public:
    Level();
    
    bool loadFromJson(const QString &filePath);
    
    int levelNumber() const { return m_levelNumber; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    qreal ballSpeed() const { return m_ballSpeed; }
    const std::vector<BrickData>& bricks() const { return m_bricks; }
    int totalBricks() const { return static_cast<int>(m_bricks.size()); }

private:
    int m_levelNumber;
    QString m_name;
    QString m_description;
    qreal m_ballSpeed;
    std::vector<BrickData> m_bricks;
    
    QColor parseColor(const QString &colorStr) const;
};

#endif
