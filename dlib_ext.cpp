#include "dlib_ext.h"
#include <iostream>
#include <cmath>
#include "dlib/dlib/dnn.h"
#include "dlib/dlib/data_io.h"
#include "dlib/dlib/gui_widgets.h"
#include "dlib/dlib/image_processing.h"

#include "json/json.h"
#include <string.h>

using namespace std;
using namespace dlib;

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



class DlibAlignerEncoder{
    public:
        char alignerModelPath[1000] = {'\0'};
        char encoderModelPath[1000] = {'\0'};
        dlib::shape_predictor * pAligner = NULL;
        anet_type * pEncoder = NULL;
          
};

DlibAlignerEncoder Instance;

char * charpizeJsonValue(Json::Value& V){
    const string& result = V.toStyledString();
    // shared_ptr<char> ret = make_shared<char>(new char[result.size()]);
    strcpy(Buffer, result.data());
    return Buffer;
}

char * setParameters(char* jsonstrParams){
    Json::Value ret;
    Json::Reader reader;
    Json::Value parameters;
    
    if (!reader.parse(jsonParameters, parameters, false))
    {
        result["code"] = 4;
        result["message"] = "Cannot parse json!";
        return charpizeJsonValue(result);
    }
    
    string alignerModelPath;
    string encoderModelPath;
    try{
        alignerModelPath = parameters["alignerModelPath"].asString();
        strcpy(Instance.alignerModelPath, alignerModelPath.c_str());
    }catch(...){
        result["code"] = 4;
        result["message"] = "Missing parameter [alignerModelPath]";
        return charpizeJsonValue(result);
    }

    try{
        encoderModelPath = parameters["encoderModelPath"].asString();
        strcpy(Instance.encoderModelPath, encoderModelPath.c_str());
    }catch(...){
        result["code"] = 4;
        result["message"] = "Missing parameter [encoderModelPath]";
        return charpizeJsonValue(result);
    }

    result["code"] = 0;
    result["message"] = "Ok";
    return charpizeJsonValue(result);
}

char * load(){
    Json::Value ret;
    try{
        Instance.pAligner = new dlib::shape_predictor();
    }catch(...){
        result["code"] = 4;
        result["message"] = "Cannot load aligner";
        return charpizeJsonValue(result);
    }
    
    try{
        Instance.pEncoder = new anet_type();
    }catch(...){
        result["code"] = 4;
        result["message"] = "Cannot load encoder";
        return charpizeJsonValue(result);
    }

    result["code"] = 0;
    result["message"] = "Ok";
    return charpizeJsonValue(result);
}

char * load(){
    Json::Value ret;
    try{
        Instance.pAligner = new dlib::shape_predictor();
        deserialize(Instance.alignerModelPath) >> *Instance.pAligner;
    }catch(...){
        result["code"] = 4;
        result["message"] = "Cannot load aligner";
        return charpizeJsonValue(result);
    }
    
    try{
        Instance.pEncoder = new anet_type();
        deserialize(Instance.encoderModelPath) >> *Instance.pEncoder;        
    }catch(...){
        result["code"] = 4;
        result["message"] = "Cannot load encoder";
        return charpizeJsonValue(result);
    }

    result["code"] = 0;
    result["message"] = "Ok";
    return charpizeJsonValue(result);
}

char * load(){
    Json::Value ret;
    try{
        delete Instance.pAligner;
        Instance.pAligner = new dlib::shape_predictor();
        deserialize(Instance.alignerModelPath) >> *Instance.pAligner;
    }catch(...){
        result["code"] = 4;
        result["message"] = "Cannot load aligner";
        return charpizeJsonValue(result);
    }
    
    try{
        delete Instance.pEncoder;
        Instance.pEncoder = new anet_type();
        deserialize(Instance.encoderModelPath) >> *Instance.pEncoder;        
    }catch(...){
        result["code"] = 4;
        result["message"] = "Cannot load encoder";
        return charpizeJsonValue(result);
    }

    result["code"] = 0;
    result["message"] = "Ok";
    return charpizeJsonValue(result);
}

char *
alignAndEncode(char * data, int x, int y){
    matrix<rgb_pixel> img(y, x);
    _convert_img_from_ctypes_(img, data, x, y);
    Json::Value result;

    // 获取landmarks
    Json::Value landmarks;

    rectangle face_window(x, y);
    auto shape = (*Instance.pAligner)(img, face_window);
    
    // push landmark coordinate into vector
    for(int i = 0; i < shape.num_parts(); i++){
        Json::Value point;
        point[(int)0] = (int)shape.part(i).x();
        point[(int)1] = (int)shape.part(i).y();
        landmarks.append(point);
    }
    result["landmarks"] = landmarks;

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
    result["facevector"] = facevector;
    
    std::string result = result.toStyledString();
    return charpizeJsonValue(result);
}