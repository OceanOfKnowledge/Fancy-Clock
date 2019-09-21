#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPoint m_mousePos;
    void setColour();

private slots:
    void updateTime();
    void showContextMenu(const QPoint &pos);
    void closeEvent(QCloseEvent *);
    void showPreference();

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
