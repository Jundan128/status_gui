#ifndef status_gui_status_H
#define status_gui_status_H

#include <rqt_gui_cpp/plugin.h>
#include <status_gui/ui_status.h>

#include "status_gui/BatteryState.h"
//#include "status_gui/Battery.h"
#include "status_gui/Pose.h"
//#include <sensor_msgs.h>

#include <ros/ros.h>
#include <ros/package.h>



#include <QStringList>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QString>

namespace status_gui {
  //using namespace std;

class status
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT

public:
  status();

  virtual void initPlugin(qt_gui_cpp::PluginContext& context);

  virtual bool eventFilter(QObject* watched, QEvent* event);

  virtual void shutdownPlugin();

private slots:
  void on_status_1_clicked();
  void on_data_baterai_clicked();
  void on_status_2_clicked();
  void on_data_Suhu_clicked();
  void msgCallback(const status_gui::BatteryState::ConstPtr& msg);
  //void msgCallback(const status_gui::Battery::ConstPtr& msg);
  //void msgCallback(const sensor_msgs::BatteryState::ConstPtr& msg);
  void msgCallback2(const status_gui::Pose::ConstPtr& msg);

private:
  Ui::status ui_;
  QWidget* widget_;

  // for subscribe -------------------------
  ros::Subscriber sub;
  ros::Subscriber sub2;
  ros::NodeHandle nh;
  // ---------------------------------------
  
};

} //namespace status_gui

#endif // status_gui_status_H
