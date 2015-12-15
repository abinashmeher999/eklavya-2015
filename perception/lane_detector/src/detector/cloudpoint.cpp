#include <opencv2/highgui/highgui.hpp>
#include <ros/package.h>
#include <laneDetector.hpp>
#include <math.h>

#define ANGLE_SPREAD 180
#define BOT_REFERENCE_X 100
#define BOT_REFERENCE_Y 20   //100 pixels with respect to cartesian coordinates
#define LARGE_VAL 10000

pcl::PointCloud<pcl::PointXYZ>::Ptr LaneDetector::generatecloud(cv::Mat& img)
{
	typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
	PointCloud::Ptr cloud_msg(new PointCloud);
    cloud_msg->header.frame_id="base_link";
	cloud_msg->height=1;
	for(int i=1;i<=img.rows;i++)
	{
		for(int j=0;j<img.cols;j++)
		{
			if(img.at<uchar>(img.rows-i,j)>200)
			cloud_msg->points.push_back(pcl::PointXYZ(((i-img.rows)+6*BOT_REFERENCE_Y)*0.002,(BOT_REFERENCE_X-j)*0.002,0));
		}
	}
	cloud_msg->width=cloud_msg->points.size();

	return cloud_msg;
}