#ifndef HIGHSCOREDIALOG_H
#define HIGHSCOREDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "HighScoreManager.h"

class HighScoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoreDialog(HighScoreManager *manager, QWidget *parent = nullptr);
    
private slots:
    void onClearScores();
    
private:
    void refreshTable();
    
    HighScoreManager *m_manager;
    QTableWidget *m_table;
};

#endif
