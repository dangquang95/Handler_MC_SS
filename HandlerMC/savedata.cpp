#include "stdafx.h"
#include "savedata.h"

saveDatatsystem::saveDatatsystem()
{
}

saveDatatsystem::~saveDatatsystem()
{
}

BOOL saveDatatsystem::saveParameter(CString strPath, DataSystem & data_system)
{
	CFileFind ffind;
	if (ffind.FindFile((LPCTSTR)strPath) == FALSE)
	{
		AfxMessageBox(_T("Not find"));
		return FALSE;
	}
	else
	{
		
		CStdioFile fn;
		fn.Open(strPath, CFile::modeReadWrite);
		fn.WriteString(_T("[Data]\n\n"));
		CString cstr;

		//Point and angle tool 1
		cstr.Format(_T("d_Point_Tool_1_X			 = %f \n"), data_system.d_Point_Tool_1_X);
		fn.WriteString(cstr);
		cstr.Format(_T("d_Point_Tool_1_Y			 = %f \n"), data_system.d_Point_Tool_1_Y);
		fn.WriteString(cstr);
		cstr.Format(_T("d_dAgnle_Tool_1				= %f \n"), data_system.d_dAgnle_Tool_1);
		fn.WriteString(cstr);
		//Point and angle tool 2
		cstr.Format(_T("d_Point_Tool_2_X			 = %f \n"), data_system.d_Point_Tool_2_X);
		fn.WriteString(cstr);
		cstr.Format(_T("d_Point_Tool_2_Y			 = %f \n"), data_system.d_Point_Tool_2_Y);
		fn.WriteString(cstr);
		cstr.Format(_T("d_dAgnle_Tool_2			 = %f \n"), data_system.d_dAgnle_Tool_2);
		fn.WriteString(cstr);
		//blur
		cstr.Format(_T("check_blur			 = %d \n"), data_system.d_check_blur);
		fn.WriteString(cstr);
		cstr.Format(_T("kSize_Tool_1		 = %d \n"), data_system.d_kSize_Tool_1);
		fn.WriteString(cstr);
		cstr.Format(_T("kSize_Tool_2		 = %d \n"), data_system.d_kSize_Tool_2);
		fn.WriteString(cstr);

		//threshold
		cstr.Format(_T("d_check_thresh		 = %d \n"), data_system.d_check_thresh);
		fn.WriteString(cstr);
		cstr.Format(_T("d_threshold_tool_1	 = %lf \n"), data_system.d_threshold_tool_1);
		fn.WriteString(cstr);
		cstr.Format(_T("d_threshold_tool_2	 = %lf \n"), data_system.d_threshold_tool_2);
		fn.WriteString(cstr);

		//areaContour sample
		cstr.Format(_T("areaContours		 = %d \n"), data_system.d_areaContours);
		fn.WriteString(cstr);
		cstr.Format(_T("areaContours_2		 = %d \n"), data_system.d_areaContours_2);
		fn.WriteString(cstr);

		//Morphology
		cstr.Format(_T("d_morSize_tool_1			= %d \n"), data_system.d_morSize_tool_1);
		fn.WriteString(cstr);
		cstr.Format(_T("d_morSize_tool_2			= %d \n"), data_system.d_morSize_tool_2);
		fn.WriteString(cstr);
		cstr.Format(_T("erode						= %d \n"), data_system.d_erode);
		fn.WriteString(cstr);
		cstr.Format(_T("dilate						= %d \n"), data_system.d_dilate);
		fn.WriteString(cstr);
		cstr.Format(_T("erode_dilate				= %d \n"), data_system.d_e_dilate);
		fn.WriteString(cstr);
		cstr.Format(_T("dilate_erode				= %d \n"), data_system.d_d_erode);
		fn.WriteString(cstr);
		cstr.Format(_T("d_Check_Apply_Morphology	= %d \n"), data_system.d_Check_Apply_Morphology);
		fn.WriteString(cstr);

	
		//Remove noise
		cstr.Format(_T("minArea					 = %d \n"), data_system.d_minArea);
		fn.WriteString(cstr);
		cstr.Format(_T("maxArea					 = %d \n"), data_system.d_maxArea);
		fn.WriteString(cstr);
		cstr.Format(_T("minWidth				 = %d \n"), data_system.d_minWidth);
		fn.WriteString(cstr);
		cstr.Format(_T("maxWidth				 = %d \n"), data_system.d_maxWidth);
		fn.WriteString(cstr);
		cstr.Format(_T("minHeight				 = %d \n"), data_system.d_minHeight);
		fn.WriteString(cstr);
		cstr.Format(_T("maxHeight				 = %d \n"), data_system.d_maxHeight);
		fn.WriteString(cstr);
		cstr.Format(_T("d_check_remove_noise	 = %d \n"), data_system.d_check_remove_noise);
		fn.WriteString(cstr);


		cstr.Format(_T("check_process			 = %d \n"), data_system.d_check_process);
		fn.WriteString(cstr);

		cstr.Format(_T("offset_x				 = %f \n"), data_system.d_offset_x);
		fn.WriteString(cstr);
		cstr.Format(_T("offset_y				 = %f \n"), data_system.d_offset_y);
		fn.WriteString(cstr);
		cstr.Format(_T("offset_angle			 = %f \n"), data_system.d_offset_angle);
		fn.WriteString(cstr);
		cstr.Format(_T("d_rad_tool_1			 = %d \n"), data_system.d_rad_tool_1);
		fn.WriteString(cstr);
		cstr.Format(_T("d_rad_tool_2			 = %d \n"), data_system.d_rad_tool_2);
		fn.WriteString(cstr);

		cstr.Format(_T("offset_x2				 = %f \n"), data_system.d_offset_x2);
		fn.WriteString(cstr);
		cstr.Format(_T("offset_y2				 = %f \n"), data_system.d_offset_y2);
		fn.WriteString(cstr);
		cstr.Format(_T("offset_angle2			 = %f \n"), data_system.d_offset_angle2);
		fn.WriteString(cstr);
		cstr.Format(_T("d_rad_tool_2			 = %d \n"), data_system.d_rad_tool_2);
		fn.WriteString(cstr);

		fn.Close();
	}
	return TRUE;
}

BOOL saveDatatsystem::loadParameter(CString strPath, DataSystem & data_system)
{

	CIniFile ini_Setting;
	ini_Setting.SetPath(strPath);

	//Area contour find
	data_system.d_areaContours		= ini_Setting.ReadInt(_T("Data"), _T("areaContours"), 0);
	data_system.d_areaContours_2	= ini_Setting.ReadInt(_T("Data"), _T("areaContours_2"), 0);
	//Point and Angle tool 1
	data_system.d_Point_Tool_1_X	= ini_Setting.ReadDouble(_T("Data"), _T("d_Point_Tool_1_X"), 0);
	data_system.d_Point_Tool_1_Y	= ini_Setting.ReadDouble(_T("Data"), _T("d_Point_Tool_1_Y"), 0);
	data_system.d_dAgnle_Tool_1		= ini_Setting.ReadDouble(_T("Data"), _T("d_dAgnle_Tool_1"), 0);
	//Point and angle tool 2
	data_system.d_Point_Tool_2_X	= ini_Setting.ReadDouble(_T("Data"), _T("d_Point_Tool_2_X"), 0);
	data_system.d_Point_Tool_2_Y	= ini_Setting.ReadDouble(_T("Data"), _T("d_Point_Tool_2_Y"), 0);
	data_system.d_dAgnle_Tool_2		= ini_Setting.ReadDouble(_T("Data"), _T("d_dAgnle_Tool_2"), 0);

	//Offset point
	data_system.d_offset_x		= ini_Setting.ReadDouble(_T("Data"), _T("offset_x"), 0);
	data_system.d_offset_y		= ini_Setting.ReadDouble(_T("Data"), _T("offset_y"), 0);
	data_system.d_offset_angle	= ini_Setting.ReadDouble(_T("Data"), _T("offset_angle"), 0);
	data_system.d_rad_tool_1	= ini_Setting.ReadInt(_T("Data"), _T("d_rad_tool_1"), 0);

	data_system.d_offset_x2		= ini_Setting.ReadDouble(_T("Data"), _T("offset_x2"), 0);
	data_system.d_offset_y2		= ini_Setting.ReadDouble(_T("Data"), _T("offset_y2"), 0);
	data_system.d_offset_angle2	= ini_Setting.ReadDouble(_T("Data"), _T("offset_angle2"), 0);
	data_system.d_rad_tool_2	= ini_Setting.ReadInt(_T("Data"), _T("d_rad_tool_2"), 0);

	//blur
	data_system.d_check_blur	= ini_Setting.ReadInt(_T("Data"), _T("check_blur"), 0);
	data_system.d_kSize_Tool_1	= ini_Setting.ReadInt(_T("Data"), _T("kSize_Tool_1"), 0);
	data_system.d_kSize_Tool_2	= ini_Setting.ReadInt(_T("Data"), _T("kSize_Tool_2"), 0);
	
	//Threshold
	data_system.d_check_thresh		= ini_Setting.ReadInt(_T("Data"), _T("d_check_thresh"), 0);
	data_system.d_threshold_tool_1	= ini_Setting.ReadDouble(_T("Data"), _T("d_threshold_tool_1"), 0);
	data_system.d_threshold_tool_2	= ini_Setting.ReadDouble(_T("Data"), _T("d_threshold_tool_2"), 0);
	
	//Morphology
	data_system.d_erode						= ini_Setting.ReadInt(_T("Data"), _T("erode"), 0);
	data_system.d_dilate					= ini_Setting.ReadInt(_T("Data"), _T("dilate"), 0);
	data_system.d_e_dilate					= ini_Setting.ReadInt(_T("Data"), _T("erode_dilate"), 0);
	data_system.d_d_erode					= ini_Setting.ReadInt(_T("Data"), _T("dilate_erod"), 0);
	data_system.d_morSize_tool_1			= ini_Setting.ReadInt(_T("Data"), _T("d_morSize_tool_1"), 0);
	data_system.d_morSize_tool_2			= ini_Setting.ReadInt(_T("Data"), _T("d_morSize_tool_2"), 0);
	data_system.d_Check_Apply_Morphology	= ini_Setting.ReadInt(_T("Data"), _T("d_Check_Apply_Morphology"), 0);

	//Remove noise
	data_system.d_minArea				= ini_Setting.ReadInt(_T("Data"), _T("minArea"), 0);
	data_system.d_maxArea				= ini_Setting.ReadInt(_T("Data"), _T("maxArea"), 0);
	data_system.d_minWidth				= ini_Setting.ReadInt(_T("Data"), _T("minWidth"), 0);
	data_system.d_maxWidth				= ini_Setting.ReadInt(_T("Data"), _T("maxWidth"), 0);
	data_system.d_minHeight				= ini_Setting.ReadInt(_T("Data"), _T("minHeight"), 0);
	data_system.d_maxHeight				= ini_Setting.ReadInt(_T("Data"), _T("maxHeight"), 0);
	data_system.d_check_remove_noise	= ini_Setting.ReadDouble(_T("Data"), _T("d_check_remove_noise"), 0);

	data_system.d_check_process		= ini_Setting.ReadInt(_T("Data"), _T("check_process"), 0);

	return TRUE;
}
