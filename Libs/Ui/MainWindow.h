#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>

#include <deque>

#include "../Controller/SongController.h"

class MainWindow : public QMainWindow

{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::deque<Song> m_allSongs;
    std::deque<Song> m_playlistSongs;
    void setupUI();

    QWidget* m_centralWidget;
    QHBoxLayout* m_baseLayout;
    struct LeftLayout
    {
        explicit LeftLayout(QHBoxLayout* parent);

        QVBoxLayout* m_mainLayout;

        QLabel* m_listSongsLabel;
        QListWidget* m_listSongs;

        QFormLayout* m_lineEditsForm;

        QLabel* m_titleLabel;
        QLineEdit* m_titleText;

        QLabel* m_artistLabel;
        QLineEdit* m_artistText;

        QLabel* m_durationLabel;
        QLineEdit* m_durationText;

        QLabel* m_linkLabel;
        QLineEdit* m_linkText;

        QVBoxLayout* m_buttonLayout;
        QHBoxLayout* m_firstRow;
        QPushButton *m_add, *m_delete, *m_update;
        QPushButton *m_filter;

    };
    LeftLayout* m_leftLayout;

    struct MiddleLayout
    {
        MiddleLayout(QHBoxLayout* parent);

        QVBoxLayout* m_mainLayout;
        QPushButton* m_insertButton;
    };
    MiddleLayout* m_middleLayout;

    struct RightLayout
    {
        RightLayout(QHBoxLayout* parent);
        QVBoxLayout* m_mainLayout;

        QLabel* m_listPlaylistLabel;
        QListWidget* m_listPlaylist;
        QHBoxLayout* m_buttonLayout;
        QPushButton* m_playButton;
        QPushButton* m_nextButton;
    };
    RightLayout* m_rightLayout;

    void m_addButtonAction();
    void m_deleteButtonAction();
    void m_updateButtonAction();
    void m_filterButtonAction();

    void m_insertButtonAction();
};