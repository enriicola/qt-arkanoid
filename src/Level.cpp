#include "Level.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Level::Level()
    : m_levelNumber(1), m_name("Untitled"), m_ballSpeed(200.0)
{
}

bool Level::loadFromJson(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open level file:" << filePath;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Invalid JSON in level file:" << filePath;
        return false;
    }
    
    QJsonObject obj = doc.object();
    
    m_levelNumber = obj.value("levelNumber").toInt(1);
    m_name = obj.value("name").toString("Untitled");
    m_description = obj.value("description").toString("");
    m_ballSpeed = obj.value("ballSpeed").toDouble(200.0);
    
    m_bricks.clear();
    
    QJsonArray bricksArray = obj.value("bricks").toArray();
    for (const QJsonValue &value : bricksArray) {
        QJsonObject brickObj = value.toObject();
        
        int row = brickObj.value("row").toInt(0);
        int col = brickObj.value("col").toInt(0);
        QString colorStr = brickObj.value("color").toString("#FFFFFF");
        int hitPoints = brickObj.value("hitPoints").toInt(1);
        
        QColor color = parseColor(colorStr);
        m_bricks.emplace_back(row, col, color, hitPoints);
    }
    
    return true;
}

QColor Level::parseColor(const QString &colorStr) const
{
    // Handle named colors
    if (colorStr == "red") return QColor(255, 100, 100);
    if (colorStr == "orange") return QColor(255, 180, 100);
    if (colorStr == "yellow") return QColor(255, 255, 100);
    if (colorStr == "green") return QColor(100, 255, 100);
    if (colorStr == "blue") return QColor(100, 100, 255);
    if (colorStr == "purple") return QColor(200, 100, 255);
    if (colorStr == "cyan") return QColor(100, 255, 255);
    if (colorStr == "magenta") return QColor(255, 100, 255);
    
    // Handle hex colors
    return QColor(colorStr);
}
