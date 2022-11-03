#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/types_c.h>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;

double stringTodouble(string a)
{
stringstream s(a);
  double b;
  s >> b;
  return b;
}
vector<vector<string>> strArray;
vector<vector<double>> objpoint;

vector<vector<string>> GetArray()
{

 
  string lineStr00, lineStr01, lineStr02, lineStr03, lineStr04, lineStr10, lineStr11, lineStr12, lineStr13, lineStr14;
  string lineStr20, lineStr21, lineStr22, lineStr23, lineStr24, lineStr30, lineStr31, lineStr32, lineStr33, lineStr34;
 
 
 
// ifstream m00("激光雷达数据/one/cloud_0.csv");
//  while (getline(m00, lineStr00))
//    {
  
//      stringstream ss00(lineStr00);
//      string str00;
//      vector<string> lineArray00;
//      while (getline(ss00, str00, ','))
//      {
//        lineArray00.push_back(str00);
//      }
//      strArray.push_back(lineArray00);
//   }



    // ifstream m01("激光雷达数据/one/cloud_1.csv");

    // while (getline(m01, lineStr01)) {
       //cout << lineStr << endl;
    //   stringstream ss01(lineStr01);
    //   string str01;
    //   vector<string> lineArray01;
    //   while (getline(ss01, str01, ',')){
  	// 	lineArray01.push_back(str01);
  	// }
    //   strArray.push_back(lineArray01);
    // }

    // ifstream m02("激光雷达数据/one/cloud_2.csv");
    //   while (getline(m02, lineStr02)) {
      
    //   stringstream ss02(lineStr02);
    //   string str02;
    //   vector<string> lineArray02;
    //   while (getline(ss02, str02, ',')){
  	// 	lineArray02.push_back(str02);
  	// }
    //   strArray.push_back(lineArray02);
    // }

  // ifstream m03("激光雷达数据/one/cloud_3.csv");
  //   while (getline(m03, lineStr03)) {
  //     //cout << lineStr << endl;
  //     stringstream ss03(lineStr03);
  //     string str03;
  //     vector<string> lineArray03;
  //     while (getline(ss03, str03, ',')){
  // 		lineArray03.push_back(str03);
  // 	}
  //     strArray.push_back(lineArray03);
  //   }

    // ifstream m04("激光雷达数据/one/cloud_4.csv");
    //  while (getline(m04, lineStr04)) {
      
    //   stringstream ss04(lineStr04);
    //   string str04;
    //   vector<string> lineArray04;
    //   while (getline(ss04, str04, ',')){
  	// 	lineArray04.push_back(str04);
  	// }
    //   strArray.push_back(lineArray04);
    // }

    // ifstream m10("激光雷达数据/two/cloud_0.csv");
    // while (getline(m10, lineStr10)) {
    //   //cout << lineStr << endl;
    //   stringstream ss10(lineStr10);
    //   string str10;
    //   vector<string> lineArray10;
    //   while (getline(ss10, str10, ',')){
  	// 	lineArray10.push_back(str10);
  	// }
    //   strArray.push_back(lineArray10);
    // }

    // ifstream m11("激光雷达数据/two/cloud_1.csv");
    //   while (getline(m11, lineStr11)) {
    //   //cout << lineStr << endl;
    //   stringstream ss11(lineStr11);
    //   string str11;
    //   vector<string> lineArray11;
    //   while (getline(ss11, str11, ',')){
  	// 	lineArray11.push_back(str11);
  	// }
    //   strArray.push_back(lineArray11);
    // }

    // ifstream m12("激光雷达数据/two/cloud_2.csv");
    
    // while (getline(m12, lineStr12)) {
   
    //   stringstream ss12(lineStr12);
    //   string str12;
    //   vector<string> lineArray12;
    //   while (getline(ss12, str12, ',')){
  	// 	lineArray12.push_back(str12);
  	// }
    //   strArray.push_back(lineArray12);
    // }

  //   ifstream m13("激光雷达数据/two/cloud_3.csv");
  //  while (getline(m13, lineStr13)) {
  //     //cout << lineStr << endl;
  //     stringstream ss13(lineStr13);
  //     string str13;
  //     vector<string> lineArray13;
  //     while (getline(ss13, str13, ',')){
  // 		lineArray13.push_back(str13);
  // 	}
  //     strArray.push_back(lineArray13);
  //   }

    // ifstream m14("激光雷达数据/two/cloud_4.csv");
    //  while (getline(m14, lineStr14)) {
    //   //cout << lineStr << endl;
    //   stringstream ss14(lineStr14);
    //   string str14;
    //   vector<string> lineArray14;
    //   while (getline(ss14, str14, ',')){
  	// 	lineArray14.push_back(str14);
  	// }
    //   strArray.push_back(lineArray14);
    // }

    // ifstream m20("激光雷达数据/three/cloud_0.csv");
    //  while (getline(m20, lineStr20)) {
    //   //cout << lineStr << endl;
    //   stringstream ss20(lineStr20);
    //   string str20;
    //   vector<string> lineArray20;
    //   while (getline(ss20, str20, ',')){
  	// 	lineArray20.push_back(str20);
  	// }
    //   strArray.push_back(lineArray20);
    // }

    // ifstream m21("激光雷达数据/three/cloud_1.csv");
    //  while (getline(m21, lineStr21)) {
    //   //cout << lineStr << endl;
    //   stringstream ss21(lineStr21);
    //   string str21;
    //   vector<string> lineArray21;
    //   while (getline(ss21, str21, ',')){
  	// 	lineArray21.push_back(str21);
  	// }
    //   strArray.push_back(lineArray21);
    // }

    // ifstream m22("激光雷达数据/three/cloud_2.csv");
    //  while (getline(m22, lineStr22)) {
    //   //cout << lineStr << endl;
    //   stringstream ss22(lineStr22);
    //   string str22;
    //   vector<string> lineArray22;
    //   while (getline(ss22, str22, ',')){
  	// 	lineArray22.push_back(str22);
  	// }
    //   strArray.push_back(lineArray22);
    // }

    // ifstream m23("激光雷达数据/three/cloud_3.csv");
    // while (getline(m23, lineStr23)) {
    //   //cout << lineStr << endl;
    //   stringstream ss23(lineStr23);
    //   string str23;
    //   vector<string> lineArray23;
    //   while (getline(ss23, str23, ',')){
  	// 	lineArray23.push_back(str23);
  	// }
    //   strArray.push_back(lineArray23);
    // }

    // ifstream m24("激光雷达数据/three/cloud_4.csv");
    // while (getline(m24, lineStr24)) {
    //   //cout << lineStr << endl;
    //   stringstream ss24(lineStr24);
    //   string str24;
    //   vector<string> lineArray24;
    //   while (getline(ss24, str24, ',')){
  	// 	lineArray24.push_back(str24);
  	// }
    //   strArray.push_back(lineArray24);
    // }

    // ifstream m30("激光雷达数据/forth/cloud_0.csv");
    // while (getline(m30, lineStr30)) {
    //   //cout << lineStr << endl;
    //   stringstream ss30(lineStr30);
    //   string str30;
    //   vector<string> lineArray30;
    //   while (getline(ss30, str30, ',')){
  	// 	lineArray30.push_back(str30);
  	// }
    //   strArray.push_back(lineArray30);
    // }

  //   ifstream m31("激光雷达数据/forth/cloud_1.csv");
  //  while (getline(m31, lineStr31)) {
  //     //cout << lineStr << endl;
  //     stringstream ss31(lineStr31);
  //     string str31;
  //     vector<string> lineArray31;
  //     while (getline(ss31, str31, ',')){
  // 		lineArray31.push_back(str31);
  // 	}
  //     strArray.push_back(lineArray31);
  //   }

    // ifstream m32("激光雷达数据/forth/cloud_2.csv");
    //  while (getline(m32, lineStr32)) {
    //   //cout << lineStr << endl;
    //   stringstream ss32(lineStr32);
    //   string str32;
    //   vector<string> lineArray32;
    //   while (getline(ss32, str32, ',')){
  	// 	lineArray32.push_back(str32);
  	// }
    //   strArray.push_back(lineArray32);
    //  }

    // ifstream m33("激光雷达数据/forth/cloud_3.csv");
    // while (getline(m33, lineStr33)) {
    //   //cout << lineStr << endl;
    //   stringstream ss33(lineStr33);
    //   string str33;
    //   vector<string> lineArray33;
    //   while (getline(ss33, str33, ',')){
  	// 	lineArray33.push_back(str33);
  	// }
    //   strArray.push_back(lineArray33);
    // }

    ifstream m34("激光雷达数据/forth/cloud_4.csv");
    while (getline(m34, lineStr34)) {
      
      stringstream ss34(lineStr34);
      string str34;
      vector<string> lineArray34;
      while (getline(ss34, str34, ',')){
  		lineArray34.push_back(str34);
  	}
      strArray.push_back(lineArray34);
 }

  return strArray;
}

int main()
{

  strArray = GetArray();
  cout<<strArray.size()<<endl;
  cout<<strArray[0][0]<<endl;
  std::vector<cv::Point2d> imagePoints;

  Mat extrisicMat(4, 4, cv::DataType<double>::type); // Intrisic matrix
  extrisicMat.at<double>(0, 0) = -7.1907391850483116e-03;
  extrisicMat.at<double>(1, 0) = -9.9997142335005851e-01;
  extrisicMat.at<double>(2, 0) = -2.3336137706425064e-03;
  extrisicMat.at<double>(3, 0) = 0;
  extrisicMat.at<double>(0, 1) = 1.0494953004635377e-02;
  extrisicMat.at<double>(1, 1) = 2.2580773589691017e-03;
  extrisicMat.at<double>(2, 1) = -9.9994237686382270e-01;
  extrisicMat.at<double>(3, 1) = 0;
  extrisicMat.at<double>(0, 2) = 9.9991907134097757e-01;
  extrisicMat.at<double>(1, 2) = -7.2148159989590677e-03;
  extrisicMat.at<double>(2, 2) = 1.0478415848689249e-02;
  extrisicMat.at<double>(3, 2) = 0;
  extrisicMat.at<double>(0, 3) = 1.0984281510814174e-01;
  extrisicMat.at<double>(1, 3) = -1.8261670813403203e-02;
  extrisicMat.at<double>(2, 3) = 1.7323651488230618e-01;
  extrisicMat.at<double>(3, 3) = 1;

Mat ConextrisicMat(4, 4, cv::DataType<double>::type); // Intrisic matrix
   ConextrisicMat.at<double>(0, 0) = -0.00719074;
   ConextrisicMat.at<double>(1, 0) = 0.01049495 ;
   ConextrisicMat.at<double>(2, 0) = 0.99991907;
   ConextrisicMat.at<double>(3, 0) = 0;
   ConextrisicMat.at<double>(0, 1) = -0.99997142;
   ConextrisicMat.at<double>(1, 1) = 0.00225808;
   ConextrisicMat.at<double>(2, 1) = -0.00721482;
   ConextrisicMat.at<double>(3, 1) = 0;
   ConextrisicMat.at<double>(0, 2) = -0.00233361;
   ConextrisicMat.at<double>(1, 2) = -0.99994238;
   ConextrisicMat.at<double>(2, 2) = 0.01047842;
   ConextrisicMat.at<double>(3, 2) = 0;
   ConextrisicMat.at<double>(0, 3) = -0.01706703;
   ConextrisicMat.at<double>(1, 3) =  0.17211497;
   ConextrisicMat.at<double>(2, 3) = -0.11178092;
   ConextrisicMat.at<double>(3, 3) = 1;



  Mat intrisicMat(3, 4, cv::DataType<double>::type); // Intrisic matrix
  intrisicMat.at<double>(0, 0) = 1.3859739625395162e+03;
  intrisicMat.at<double>(1, 0) = 0;
  intrisicMat.at<double>(2, 0) = 0;
  intrisicMat.at<double>(0, 1) = 0;
  intrisicMat.at<double>(1, 1) = 1.3815353250336800e+03;
  intrisicMat.at<double>(2, 1) = 0;
  intrisicMat.at<double>(0, 2) = 9.3622464596653492e+02;
  intrisicMat.at<double>(1, 2) = 4.9459467170828475e+02;
  intrisicMat.at<double>(2, 2) = 1;
  intrisicMat.at<double>(0, 3) = 1;
  intrisicMat.at<double>(1, 3) = 1;
  intrisicMat.at<double>(2, 3) = 1;

  cv::Mat distCoeffs(5, 1, cv::DataType<double>::type); // Distortion vector
  distCoeffs.at<double>(0) = 7.0444095385902794e-02;
  distCoeffs.at<double>(1) = -1.8010798300183417e-01;
  distCoeffs.at<double>(2) = -7.7001990711544465e-03;
  distCoeffs.at<double>(3) = -2.2524968464184810e-03;
  distCoeffs.at<double>(4) = 1.4838608095798808e-01;

  objpoint.resize(930000);
  vector<Point2i> imgpoint(930000);
  vector<Point2d> drawpoint;

  Mat img = Mat(1024, 1280, CV_8UC3, Scalar(0, 0, 0));


  for (int i = 0; i < strArray.size(); i++)
  {
    objpoint[i].resize(4);

    objpoint[i][0] = stod(strArray[i][0]);
    objpoint[i][1] = stod(strArray[i][1]);
    objpoint[i][2] = stod(strArray[i][2]);
    objpoint[i][3] = 1;



    Mat m(4, 1, cv::DataType<double>::type);
    m.at<double>(0) = objpoint[i][0];
    m.at<double>(1) = objpoint[i][1];
    m.at<double>(2) = objpoint[i][2];
    m.at<double>(3) = objpoint[i][3];
    Mat cam=ConextrisicMat*m;
    double zc=cam.at<double>(2);
    Mat imgp = intrisicMat*cam;
    imgpoint[i].x = static_cast<int>(imgp.at<double>(0)/zc);
    imgpoint[i].y = static_cast<int>(imgp.at<double>(1)/zc);

    if (imgpoint[i].x > 0 && imgpoint[i].x < 1280 && imgpoint[i].y > 0 && imgpoint[i].y < 1024)
    {
      drawpoint.push_back(imgpoint[i]);
    }
  }

  for (int i = 0; i < drawpoint.size(); i++)
  {
    circle(img, Point2i(drawpoint[i].x, drawpoint[i].y), 1, Scalar(255, 255, 255), -1);
  }
  cout << "总共的点：" << strArray.size() << endl;
  cout << "需要画的点个数：" << drawpoint.size() << endl;
  imshow("1", img);
  imwrite("/home/alyssa/pic/45.jpg", img);
  waitKey(0);
}
