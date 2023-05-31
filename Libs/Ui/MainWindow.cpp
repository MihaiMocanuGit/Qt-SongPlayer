#include <QMessageBox>
#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), m_allSongsController{m_allSongs}, m_playlistController{m_playlist}
{
    this->setupUI();
}

MainWindow::~MainWindow()
{
    //delete m_centralWidget;

    delete m_leftLayout;
    delete m_middleLayout;
    delete m_rightLayout;
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_baseLayout = new QHBoxLayout(m_centralWidget);

    m_leftLayout = new LeftLayout(m_baseLayout);
    m_middleLayout = new MiddleLayout(m_baseLayout);
    m_rightLayout = new RightLayout(m_baseLayout);
    this->setCentralWidget(m_centralWidget);

    connect(m_leftLayout->m_update, &QPushButton::clicked, this, &MainWindow::m_updateButtonAction);
    connect(m_leftLayout->m_delete, &QPushButton::clicked, this, &MainWindow::m_deleteButtonAction);
    connect(m_leftLayout->m_add, &QPushButton::clicked, this, &MainWindow::m_addButtonAction);
    connect(m_leftLayout->m_filter, &QPushButton::clicked, this, &MainWindow::m_filterButtonAction);

    connect(m_middleLayout->m_insertButton, &QPushButton::clicked, this, &MainWindow::m_insertButtonAction);

}

void MainWindow::m_updateButtonAction()
{
    QMessageBox msgBox;
    msgBox.setText("Not implemented yet\n(Very fancy box)");
    msgBox.exec();
}
void MainWindow::m_filterButtonAction()
{
    QMessageBox msgBox;
    msgBox.setText("Not implemented yet\n(Very fancy box)");
    msgBox.exec();
}

void MainWindow::m_addButtonAction()
{

    m_refreshQListWidget(m_leftLayout->m_listSongs);
}

void MainWindow::m_deleteButtonAction()
{
}

void MainWindow::m_insertButtonAction()
{

    m_refreshQListWidget(m_rightLayout->m_listPlaylist);
}


MainWindow::LeftLayout::LeftLayout(QHBoxLayout* parent)
{
    m_mainLayout = new QVBoxLayout();

    m_listSongsLabel = new QLabel("All songs");
    m_listSongs = new QListWidget();
    m_mainLayout->addWidget(m_listSongsLabel);
    m_mainLayout->addWidget(m_listSongs);


    m_lineEditsForm = new QFormLayout();
    m_lineEditsForm->setLabelAlignment(Qt::AlignLeft);

    m_titleLabel = new QLabel("Title:");
    m_titleText = new QLineEdit();
    m_lineEditsForm->addRow(m_titleLabel, m_titleText);



    m_artistLabel = new QLabel("Artist:");
    m_artistText = new QLineEdit();
    m_lineEditsForm->addRow(m_artistLabel, m_artistText);


    m_durationLabel = new QLabel("Duration:");
    m_durationText = new QLineEdit();
    m_lineEditsForm->addRow(m_durationLabel, m_durationText);

    m_linkLabel = new QLabel("Link:");
    m_linkText = new QLineEdit();
    m_lineEditsForm->addRow(m_linkLabel, m_linkText);

    m_mainLayout->addLayout(m_lineEditsForm);



    m_buttonLayout = new QVBoxLayout;
    m_firstRow = new QHBoxLayout;

    m_add = new QPushButton("Add");
    m_firstRow->addWidget(m_add);

    m_delete = new QPushButton("Delete");
    m_firstRow->addWidget(m_delete);

    m_update = new QPushButton("Update");
    m_firstRow->addWidget(m_update);

    m_buttonLayout->addLayout(m_firstRow);

    m_filter = new QPushButton("Filter");
    m_buttonLayout->addWidget(m_filter, 0, Qt::AlignCenter);

    m_mainLayout->addLayout(m_buttonLayout);

    parent->addLayout(m_mainLayout);
    //parent->setLayout(m_mainLayout);
}

MainWindow::MiddleLayout::MiddleLayout(QHBoxLayout *parent)
{
    m_mainLayout = new QVBoxLayout();
    m_insertButton = new QPushButton(">");
    m_mainLayout->addWidget(m_insertButton);

    parent->addLayout(m_mainLayout);

}

MainWindow::RightLayout::RightLayout(QHBoxLayout *parent)
{

    m_mainLayout = new QVBoxLayout();

    m_listPlaylistLabel = new QLabel("Playlist");
    m_listPlaylist = new QListWidget();
    m_mainLayout->addWidget(m_listPlaylistLabel);
    m_mainLayout->addWidget(m_listPlaylist);

    m_buttonLayout = new QHBoxLayout();

    m_playButton = new QPushButton("Play");
    m_nextButton = new QPushButton("Next");

    m_buttonLayout->addWidget(m_playButton);
    m_buttonLayout->addWidget(m_nextButton);

    m_mainLayout->addLayout(m_buttonLayout);

    parent->addLayout(m_mainLayout);
}