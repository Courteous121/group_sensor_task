/**
 * @file OnnxRT.h
 * @author 赵曦 (535394140@qq.com)
 * @brief the deployment library header file of the ONNXruntime (Ort)
 * @version 1.0
 * @date 2022-02-04
 *
 * @copyright Copyright SCUT RobotLab(c) 2022
 *
 */



#include <numeric>
#include <cassert>
#include <iostream>
#include <algorithm>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <chrono>
#include <string>

// onnxruntime
#include <core/session/onnxruntime_cxx_api.h>
// #include <core/providers/cuda/cuda_provider_factory.h>
#include <core/session/onnxruntime_c_api.h>

#include <onnxruntime_cxx_api.h>

using namespace std;
using namespace cv;
using namespace Ort;


class OnnxRT
{
    using session_ptr = std::shared_ptr<Ort::Session>;

    Ort::Env __env; // environment
    Ort::SessionOptions __session_options;

    
    Ort::MemoryInfo __memory_info;
    Ort::AllocatorWithDefaultOptions __allocator;
    session_ptr __pSession;

    float __means[3]; // mean value
    float __std[3];   // standard deviation

    // memory
    std::vector<std::vector<float>> __input_arrays;
    std::vector<const char *> __input_names;
    std::vector<const char *> __output_names;

public:

    OnnxRT(const std::string & ,cv::Matx31f ,cv::Matx31f  );
    
    ~OnnxRT() = default;

    void printModelInfo();
    std::vector<size_t> inference(const std::vector<cv::Mat> &);

private:
    void setupEngine(const std::string &); // initialize the engine of the Ort
    void imageToVector(cv::Mat &, std::vector<float> &);
    std::vector<Ort::Value> pre_process(const std::vector<cv::Mat> &);
    std::vector<size_t> post_process(std::vector<Ort::Value> &);

    inline std::vector<Ort::Value> doInference(std::vector<Ort::Value> &input_tensors)
    {
        return __pSession->Run(Ort::RunOptions{nullptr}, __input_names.data(), input_tensors.data(),
                               input_tensors.size(), __output_names.data(), __output_names.size());
    }
};



OnnxRT::OnnxRT(const string &model_path,cv::Matx31f means,cv::Matx31f std)
    : __env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "OnnxDeployment"),
      __memory_info(MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator,
                                          OrtMemType::OrtMemTypeDefault))
{
    assert(!model_path.empty());//判断
    setupEngine(model_path);
    for (int i = 0; i < 3; i++)
    {
        __means[i] = means(i);
        __std[i] = std(i);
         //       cout<<__means[i]<<"  "<<__std[i]<<endl;
    }
}



void OnnxRT::setupEngine(const string &model_path)
{

    __session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
    __pSession = make_shared<Session>(__env, model_path.c_str(), __session_options);

    // define the names of the I/O nodes
    //cout<<"输入的个数"<<__pSession->GetInputCount()<<endl;
    for (size_t i = 0; i < __pSession->GetInputCount(); i++)
        __input_names.emplace_back(__pSession->GetInputName(i, __allocator));
    for (size_t i = 0; i < __pSession->GetOutputCount(); i++)
        __output_names.emplace_back(__pSession->GetOutputName(i, __allocator));
    // setup input array
    __input_arrays.resize(__pSession->GetInputCount());
    for (size_t i = 0; i < __pSession->GetInputCount(); i++)
    {
        auto shape = __pSession->GetInputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();
        //cout<<"shape的个数："<<shape.size()<<endl;
        __input_arrays[i].resize(shape[1] * shape[2] * shape[3]);
        
    }
}


vector<size_t> OnnxRT::inference(const vector<Mat> &images)
{
    vector<Value> input_tensors = pre_process(images);//由输入的图片得到输入张量
    vector<Value> output_tensors = doInference(input_tensors);//得到输出张量
    return post_process(output_tensors);//获得输出的索引
}


vector<Value> OnnxRT::pre_process(const vector<Mat> &images)
{
    size_t input_count = __pSession->GetInputCount();
    assert(input_count == images.size());
    // get the correct data of each input layer
    vector<Value> input_tensors;
    for (size_t i = 0; i < input_count; i++)
    {
        auto input_shape = __pSession->GetInputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();
        // [2], [3] are the correct size of the image
        assert(input_shape.size() == 4 &&
               (input_shape[2] == input_shape[3]));
        input_shape[0] = 1;
        // update the size of each input layer
        Mat input_image;
        resize(images[i], input_image, Size(input_shape[2], input_shape[3]));
        // allocate memory and normalization
        imageToVector(input_image, __input_arrays[i]);
        input_tensors.emplace_back(Value::CreateTensor<float>(__memory_info,
                                                              __input_arrays[i].data(), __input_arrays[i].size(),
                                                              input_shape.data(), input_shape.size()));
    }
    return input_tensors;
}


vector<size_t> OnnxRT::post_process(vector<Value> &output_tensors)
{
    // the index with the highest confidence corresponding to all outputs
    vector<size_t> output_indexs;
    for (auto &output_tensor : output_tensors)
    {
        // Obtain the index with the highest confidence
        const float *output = output_tensor.GetTensorData<float>();
        vector<size_t> indexs(output_tensor.GetTensorTypeAndShapeInfo().GetElementCount());
        iota(indexs.begin(), indexs.end(), 0);
        sort(indexs.begin(), indexs.end(),
             [&output](size_t l, size_t r)
             {
                 return output[l] > output[r];
             });
        output_indexs.emplace_back(indexs[0]);//得到最大索引值
    }
    return output_indexs;
}


void OnnxRT::imageToVector(Mat &input_image, vector<float> &input_array)
{
    // CHW
    int C = input_image.channels();
    int H = input_image.rows;
    int W = input_image.cols;
    // to tensor, NHWC format and normalization
    float *p_input_array = input_array.data();

    for (int c = 0; c < C; c++)
    {
        for (int h = 0; h < H; h++)
        {
            for (int w = 0; w < W; w++)
            {
                p_input_array[c * H * W + h * W + w] = input_image.ptr<uchar>(h)[w * C + 2 - c] / 255.f;
                p_input_array[c * H * W + h * W + w] = (p_input_array[c * H * W + h * W + w] -
                                                      __means[c]) /
                                                       __std[c];
            }
        }
    }
}



int main()
{
    Mat img=imread("2.jpg");
    vector<Mat> img0;
    Mat Mean,stddev;
   
        
     OnnxRT ort0("FCNet.onnx",{0,0,0},{1,1,1});
     
    img0.push_back(img);
 
     vector<size_t> output_index=ort0.inference(img0);
         cout<<"检测类型为："<<output_index[0]<<endl;
    
}
