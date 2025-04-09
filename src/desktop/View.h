#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QDebug>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QPainter>
#include <QProcess>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../api/ControllerApi.h"
#include "Controller.h"
#include "InitOpenGL.h"
#include "OpenGL.h"
#include "OpenGLFasad.h"
#include "Singleton.h"

#define DELAY 100

namespace s21 {

class Widget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT

 private:
  OpenGLFasad openGL;
  InitOpenGL &gl;
  std::vector<unsigned int> indices;
  int timer;

 protected:
  void timerEvent(QTimerEvent *event) override;
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 public:
  explicit Widget(QWidget *parent = nullptr);
  bool isFile;
  bool saveScreenshot(const QString &filename);
  bool gifCapture;
  ~Widget() override;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Controller *contr, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Controller *controller;
  RawMatrixData data;
  Widget *openGLWidget;
  OpenGL &openGL;
  char projection;
  int GifId;
  QTimer *GifTimer;
  QElapsedTimer TimeCounter;
  QSlider *sliderTX;
  QSlider *sliderTY;
  QSlider *sliderTZ;
  QSlider *sliderRotX;
  QSlider *sliderRotY;
  QSlider *sliderRotZ;
  QSlider *sliderScale;
  QSlider *sliderThikness;
  QSlider *sliderVertices;
  QLabel *LRotation;
  QLabel *LTranslation;
  QLabel *LScale;
  QLabel *LThikness;
  QLabel *LPointSize;
  QLabel *LModelName;
  QLabel *LValueModelName;
  QLabel *LVertices;
  QLabel *LValueVertices;
  QLabel *LEdges;
  QLabel *LValueEdges;
  QPushButton *buttonLoad;
  QPushButton *buttonEdgeColor;
  QPushButton *buttonBackColor;
  QPushButton *buttonPointColor;
  QPushButton *buttonSave;
  QPushButton *buttonGif;
  QCheckBox *toggleStipple;
  QCheckBox *toggleRoundV;
  QLineEdit *lineEditTX;
  QLineEdit *lineEditTY;
  QLineEdit *lineEditTZ;
  QLineEdit *lineEditRX;
  QLineEdit *lineEditRY;
  QLineEdit *lineEditRZ;
  QLineEdit *lineEditS;
  QComboBox *projectionType;
  QString *filePath;
  QSettings *settings;
  void createWidgets();
  QSlider *createSliderWithLineEdit(int const min, int const max,
                                    int const average, QLineEdit **lineEditPtr);
  void createRightPanel();
  void setupConnections();
  void setupSliderSync(QSlider *slider, QLineEdit *lineEdit, int min, int max);
  QLineEdit *createLineEdit(int charWidth);
  void setNameAndValues(ObjData tempData);
  void setupSliderConnects(QSlider *slider, Signal signal, char type);
  void loadObj();
  void saveSettings();
  void loadSettings();
  void startGifCapture();
  void stopGifCapture();
  void setProjection(const QString &text);
  void setButtonSave();
  void setColor(QPushButton &button, const QString &text);
  static void updateButtonColor(QPushButton *button, const QColor &color);

 private slots:
  void makeGifLoop();
};

class QtView {
 private:
  Controller *controller;
  int argc;
  char *argv;

 public:
  explicit QtView(Controller *controller, int argc, char *argv);
  int startView();
};
}  // namespace s21

#endif  // WIDGET_H
