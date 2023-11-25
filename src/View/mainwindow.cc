#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget* parent, s21::Controller* c)
    : QMainWindow(parent), control_(c), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  for (auto btn : ui_->numbers_group->buttons()) {
    connect(btn, &QPushButton::clicked, this, &MainWindow::DigitNumbers);
  }
  for (auto btn : ui_->function_group->buttons()) {
    connect(btn, &QPushButton::clicked, this, &MainWindow::FunctionButtons);
  }
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::on_calculate_button_clicked() {
  ui_->expression_line->setText(QString::fromUtf8(
      control_->CalculateResult(ui_->expression_line->text().toStdString(),
                                ui_->x_value_line->text().toDouble())));
}

void MainWindow::DigitNumbers() {
  QPushButton* button = (QPushButton*)sender();
  QString new_label = ui_->expression_line->text() + button->text();
  ui_->expression_line->setText(new_label);
}

void MainWindow::FunctionButtons() {
  QPushButton* button = (QPushButton*)sender();
  QString new_label = ui_->expression_line->text() + button->text() + '(';
  ui_->expression_line->setText(new_label);
}

void MainWindow::on_clear_button_clicked() { ui_->expression_line->clear(); }

void MainWindow::on_backspace_button_clicked() {
  ui_->expression_line->backspace();
}

void MainWindow::GraphPlay() {
  std::string expression = ui_->graph_line->text().toStdString();
  double x_min = ui_->x_min_spin->value();
  double x_max = ui_->x_max_spin->value();
  double y_min = ui_->y_min_spin->value();
  double y_max = ui_->y_max_spin->value();
  if (x_min >= x_max || y_min >= y_max) {
    return;
  }
  QVector<double> x, y;
  GeneratePlotData(expression, x_min, x_max, y_min, y_max, x, y);
  UpdateGraph(x, y, x_min, x_max, y_min, y_max);
}

void MainWindow::GeneratePlotData(const std::string& expression, double x_min,
                                  double x_max, double y_min, double y_max,
                                  QVector<double>& x, QVector<double>& y) {
  double h = (x_max - x_min) / 1000;
  double Y = 0;
  x.clear();
  y.clear();
  for (double X = x_min; X <= x_max; X += h) {
    std::string result = control_->CalculateResult(expression, X);
    if (result != "Error validation" && result != "Error calculation") {
      Y = std::stod(result);
      if (Y <= y_max && Y >= y_min) {
        x.push_back(X);
        y.push_back(Y);
      }
    }
  }
}

void MainWindow::UpdateGraph(const QVector<double>& x, const QVector<double>& y,
                             double x_min, double x_max, double y_min,
                             double y_max) {
  ui_->plot_widget->clearGraphs();
  ui_->plot_widget->addGraph();
  ui_->plot_widget->graph(0)->setData(x, y);
  ui_->plot_widget->graph(0)->setPen(QPen(Qt::green));
  ui_->plot_widget->graph(0)->setBrush(QBrush(QColor(0, 255, 0, 20)));
  ui_->plot_widget->graph(0)->setLineStyle(QCPGraph::lsLine);
  ui_->plot_widget->xAxis->setLabel("X");
  ui_->plot_widget->yAxis->setLabel("Y");
  ui_->plot_widget->xAxis->setRange(x_min, x_max);
  ui_->plot_widget->yAxis->setRange(y_min, y_max);
  ui_->plot_widget->replot();
}

void MainWindow::on_calculate_graph_button_clicked() { GraphPlay(); }
}  // namespace s21
