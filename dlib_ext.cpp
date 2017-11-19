#include "dlib_ext.h"
#include <iostream>
#include <cmath>
#include "../dlib/dlib/dnn.h"
#include "../dlib/dlib/data_io.h"
#include "../dlib/dlib/gui_widgets.h"
#include "../dlib/dlib/image_processing.h"

#include "json/json.h"

using namespace std;
using namespace dlib;

dlib::shape_predictor * pLandmarkPredictor = NULL;
anet_type * pFaceEncoder = NULL;

int 
LoadLandmarkPredictor(const char * modelpath){
    pLandmarkPredictor = new dlib::shape_predictor();
    deserialize(modelpath) >> *pLandmarkPredictor;
    return 0;
}

int 
LoadFaceEncoder(const char * modelpath){
    pFaceEncoder = new anet_type(); // 这里可以用作加载器
    deserialize(modelpath) >> *pFaceEncoder; // 不知道内部构造就不知道出错咋办
    return 0;
}

// 自定义转换函数
void
_convert_img_from_ctypes_(matrix<rgb_pixel> &dst, char * data, int x, int y){
    rgb_pixel * rgbdata = (rgb_pixel*)((void*)data);
    for(int r=0; r < y; r++){
        for(int c=0; c < x; c++){
            dst(r,c) = rgbdata[r*x+c];
        }
    }
    return;
}

char *
LandmarkAndEncode(char * data, int x, int y){
    if(!pFaceEncoder || !pLandmarkPredictor){
        return NULL;
    }
    matrix<rgb_pixel> img(y, x);
    _convert_img_from_ctypes_(img, data, x, y);

    Json::Value root;

    // 获取landmarks
    Json::Value landmarks;

    rectangle face_window(x, y);
    auto shape = (*pLandmarkPredictor)(img, face_window);
    
    // push landmark coordinate into vector
    for(int i = 0; i < shape.num_parts(); i++){
        Json::Value point;
        point[(int)0] = (int)shape.part(i).x();
        point[(int)1] = (int)shape.part(i).y();
        landmarks.append(point);
    }
    root["landmarks"] = landmarks;

    // 获取人脸vector
    Json::Value facevector;

    std::vector<matrix<rgb_pixel>> faces;
    matrix<rgb_pixel> face_chip;

    extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
    faces.push_back(move(face_chip));
    
    //extract face features via resNet
    std::vector<matrix<float,0,1>> facecodes = (*pFaceEncoder)(faces);
    int cvi = 0;
    for(float vi : facecodes[0]){
        facevector[cvi++] = vi;
    }
    root["facevector"] = facevector;
    
    std::string result = root.toStyledString();
    cout << result;

    return const_cast<char*>(result.c_str());
}

char *
TestFunc(char * data, int x, int y){
    matrix<rgb_pixel> img(y, x);
    _convert_img_from_ctypes_(img, data, x, y);


    string a("dadasdsadas");
    return a.c_str();
}