#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H_

#include <QMainWindow>

#include "../Controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, s21::Controller *c = nullptr);
  ~MainWindow();

  void DigitNumbers();
  void FunctionButtons();

 private slots:
  void on_calculate_button_clicked();
  void on_clear_button_clicked();
  void on_backspace_button_clicked();
  void on_calculate_graph_button_clicked();

 private:
  s21::Controller *control_;
  Ui::MainWindow *ui_;

  void GraphPlay();
  void GeneratePlotData(const std::string &expression, double x_min,
                        double x_max, double y_min, double y_max,
                        QVector<double> &x, QVector<double> &y);
  void UpdateGraph(const QVector<double> &x, const QVector<double> &y,
                   double x_min, double x_max, double y_min, double y_max);
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_MAINWINDOW_H_
