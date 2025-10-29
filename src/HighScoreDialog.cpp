#include "HighScoreDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>

HighScoreDialog::HighScoreDialog(HighScoreManager *manager, QWidget *parent)
    : QDialog(parent), m_manager(manager)
{
    setWindowTitle("High Scores");
    setMinimumSize(600, 400);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create table
    m_table = new QTableWidget(this);
    m_table->setColumnCount(3);
    m_table->setHorizontalHeaderLabels({"Rank", "Name", "Score", "Date"});
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setAlternatingRowColors(true);
    
    mainLayout->addWidget(m_table);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *clearButton = new QPushButton("Clear Scores", this);
    QPushButton *closeButton = new QPushButton("Close", this);
    
    buttonLayout->addWidget(clearButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    
    mainLayout->addLayout(buttonLayout);
    
    connect(clearButton, &QPushButton::clicked, this, &HighScoreDialog::onClearScores);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    
    refreshTable();
}

void HighScoreDialog::refreshTable()
{
    auto scores = m_manager->getHighScores();
    m_table->setRowCount(static_cast<int>(scores.size()));
    
    for (size_t i = 0; i < scores.size(); ++i) {
        // Rank
        QTableWidgetItem *rankItem = new QTableWidgetItem(QString::number(i + 1));
        rankItem->setTextAlignment(Qt::AlignCenter);
        m_table->setItem(static_cast<int>(i), 0, rankItem);
        
        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem(scores[i].name);
        m_table->setItem(static_cast<int>(i), 1, nameItem);
        
        // Score
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(scores[i].score));
        scoreItem->setTextAlignment(Qt::AlignCenter);
        m_table->setItem(static_cast<int>(i), 2, scoreItem);
        
        // Date
        QTableWidgetItem *dateItem = new QTableWidgetItem(
            scores[i].date.toString("yyyy-MM-dd hh:mm"));
        dateItem->setTextAlignment(Qt::AlignCenter);
        m_table->setItem(static_cast<int>(i), 3, dateItem);
    }
    
    // Resize columns to content
    m_table->resizeColumnsToContents();
}

void HighScoreDialog::onClearScores()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Clear High Scores",
        "Are you sure you want to clear all high scores?",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        m_manager->clearHighScores();
        refreshTable();
    }
}
