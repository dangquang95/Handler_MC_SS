
#include "afxwin.h"
#include "IniFile.h"
#include "opencv2\opencv.hpp"
#pragma comment(lib, "opencv_world330d.lib")
typedef struct tagDataSystem
{
	//Filter 
	int d_check_blur;
	int d_kSize_Tool_1;
	int d_kSize_Tool_2;
	
	//Threshold
	int d_check_thresh;
	double d_threshold_tool_1;
	double d_threshold_tool_2;

	//Morphology
	int d_morSize_tool_1;
	int d_morSize_tool_2;
	int d_erode;
	int d_dilate;
	int d_e_dilate;
	int d_d_erode;
	int d_Check_Apply_Morphology;

	//Point sample
	float d_dAgnle_Tool_1;
	float d_dAgnle_Tool_2;
	double	d_Point_Tool_1_X;
	double	d_Point_Tool_1_Y;
	double	d_Point_Tool_2_X;
	double	d_Point_Tool_2_Y;

	//Remove Noise
	int d_minArea;
	int d_maxArea;
	int d_minWidth;
	int d_maxWidth;
	int d_minHeight;
	int d_maxHeight;
	int d_check_remove_noise;
	//check process
	int d_check_process;

	//offset tool 1
	double	d_offset_x;
	double	d_offset_y;
	double	d_offset_angle;
	int		d_rad_tool_1;

	//offset tool 2
	double	d_offset_x2;
	double	d_offset_y2;
	double	d_offset_angle2;
	int		d_rad_tool_2;

	//area contours
	int d_areaContours;
	int d_areaContours_2;

	double d_rate;



}DataSystem;

class saveDatatsystem
{
public:
	saveDatatsystem();
	~saveDatatsystem();

	BOOL		saveParameter(CString strPath, DataSystem &data_system);
	BOOL		loadParameter(CString strPath, DataSystem &data_system);
	
};

#pragma once
