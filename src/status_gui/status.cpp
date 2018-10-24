#include "status_gui/status.h"

#include <pluginlib/class_list_macros.h>


namespace status_gui {
  

status::status()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  setObjectName("status");
}

void status::initPlugin(qt_gui_cpp::PluginContext& context)
{
  QStringList argv = context.argv();

  widget_ = new QWidget();
  ui_.setupUi(widget_);

  //adds number if more than 1 of this plugin?
  if (context.serialNumber() > 1)
  {
    widget_->setWindowTitle(widget_->windowTitle() + " (" + QString::number(context.serialNumber()) + ")");
  }
  context.addWidget(widget_);


  //Input QWidget ---------------------------------------------------------------------
  ui_.status_1->setIcon(QIcon::fromTheme("battery"));
  ui_.status_1->setIconSize(QSize(40, 40));
  connect(ui_.status_1, SIGNAL(pressed()), this, SLOT(on_status_1_clicked()));
  
  connect(ui_.data_baterai, SIGNAL(pressed()), this, SLOT(on_data_baterai_clicked()));

  ui_.status_2->setIcon(QIcon::fromTheme("battery"));
  ui_.status_2->setIconSize(QSize(40, 40));
  connect(ui_.status_2, SIGNAL(pressed()), this, SLOT(on_status_2_clicked()));
  
  connect(ui_.data_Suhu, SIGNAL(pressed()), this, SLOT(on_data_Suhu_clicked()));
  
  // Subscribe Topic ----------------------------------------------------------------	 
  sub2 = nh.subscribe("turtle1/pose", 10, &status::msgCallback2, this);
  sub = nh.subscribe("battery_state", 10, &status::msgCallback, this);
  //---------------------------------------------------------------------------------
  
}

bool status::eventFilter (QObject* watched, QEvent* event)
{
  //return true;
}

void status::shutdownPlugin() 
{
  sub.shutdown();
}

void status::on_status_1_clicked()
{
  
}

void status::on_data_baterai_clicked()
{
  
}

void status::on_status_2_clicked()
{
  
}

void status::on_data_Suhu_clicked()
{
  
}

///*/ Subscriber ------------------------------------------------
void status::msgCallback(const status_gui::BatteryState::ConstPtr& msg)
//void status::msgCallback(const status_gui::Battery::ConstPtr& msg)
//void status::msgCallback(const status_gui::Pose::ConstPtr& msg)
//void msgCallback(const sensor_msgs::BatteryState::ConstPtr& msg);
{
	int persenBaterai = ((msg->voltage)-11.5)*100;
	// Mapping 11.5 - 12.5 Voltage to 0 - 100 %
        //int Sudut = (msg->theta)*57;      
	QString str = QString::number(persenBaterai);

	ui_.data_baterai->setText(str);
	///*-----------------------------------------------------------------------
	if (persenBaterai < 25)
	{
		ui_.status_1->setIcon(QIcon::fromTheme("battery-low"));
	} 
	else
	{
		if (persenBaterai < 40)
		{
			ui_.status_1->setIcon(QIcon::fromTheme("battery-caution"));
		}
		else
			ui_.status_1->setIcon(QIcon::fromTheme("battery"));
	}
	//----------------------------------------------------------------------*/
}

void status::msgCallback2(const status_gui::Pose::ConstPtr& msg)
{
	//int persenBaterai = ((msg->voltage)-11.5)*100;
	// Mapping 11.5 - 12.5 Voltage to 0 - 100 %
        int Sudut = (msg->theta)*57;      
	QString str = QString::number(Sudut);

	ui_.data_Suhu->setText(str);
	///*-----------------------------------------------------------------------
	if (Sudut < 90)
	{
		ui_.status_2->setIcon(QIcon::fromTheme("battery-low"));
	} 
	else
	{
		if (Sudut < 180)
		{
			ui_.status_2->setIcon(QIcon::fromTheme("battery-caution"));
		}
		else
			ui_.status_2->setIcon(QIcon::fromTheme("battery"));
	}
	//----------------------------------------------------------------------*/
}
//------------------------------------------------------------*/

} //namespace rqt_testing

PLUGINLIB_EXPORT_CLASS(status_gui::status, rqt_gui_cpp::Plugin)
