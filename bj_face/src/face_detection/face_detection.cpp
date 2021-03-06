#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

//void detectAndRecognise(Mat frame, vector<Mat> images, vector<int> labels);
Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();


CascadeClassifier face_cascade;

// read csv for input files
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';'){
    std::ifstream file(filename.c_str(), ifstream::in);
    if(!file) {
        string error_message = "No Valid input file was given, check the file name";
        CV_Error(Error::StsBadArg, error_message);
    }

    string line, path, classlabel;
    while (getline(file, line)){
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path,0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

// The following lines simply get the last images from
    // your dataset and remove it from the vector. This is
    // done, so  that the training data (which we learn the
    // cv::LBPHFaceRecognizer on) and the test data we test
    // the model with, do not overlap.
void detectAndRecognise(Mat frame, vector<Mat> images, vector<int> labels){
    Mat frame_gray;
    cvtColor(frame, frame_gray,COLOR_BGR2GRAY);
    equalizeHist( frame_gray, frame_gray);


    // The following line predicts the label of a given
    // test image:
    int predictedLabel = -1;
    double confidence = 0.0;
    
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);
    
    for(size_t i = 0; i <faces.size(); i++){
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
        Mat faceROI = frame_gray(faces[i]);
        model->predict(faceROI, predictedLabel, confidence);
        putText( frame, to_string(predictedLabel), center, FONT_HERSHEY_COMPLEX, 10, cv::Scalar(255.0,0.0,0.0,255.0));
        string result_message = format("Predicted class = %d / Confidence = %d", predictedLabel, confidence);
        cout << result_message << endl;
    }

    imshow("Capture - Face detection", frame);
    /*
    Mat testSample = images[images.size() - 1];
    int testLabel = labels[labels.size() - 1];
    images.pop_back();
    labels.pop_back();
    // The following lines create an LBPH model for
    // face recognition and train it with the images and
    // labels read from the given CSV file.
    //
    // The LBPHFaceRecognizer uses Extended Local Binary Patterns
    // (it's probably configurable with other operators at a later
    // point), and has the following default values
    //
    //      radius = 1
    //      neighbors = 8
    //      grid_x = 8
    //      grid_y = 8
    //
    // So if you want a LBPH FaceRecognizer using a radius of
    // 2 and 16 neighbors, call the factory method with:
    //
    //      cv::face::LBPHFaceRecognizer::create(2, 16);
    //
    // And if you want a threshold (e.g. 123.0) call it with its default values:
    //
    //      cv::face::LBPHFaceRecognizer::create(1,8,8,8,123.0)
    //

    model->predict(testSample, predictedLabel, confidence);

    //
    // To get the confidence of a prediction call the model with:
    //
    //      int predictedLabel = -1;
    //      double confidence = 0.0;
    //      model->predict(testSample, predictedLabel, confidence);
    //
    string result_message = format("Predicted class = %d / Actual class = %d./ Confidence = %d", predictedLabel, testLabel, confidence);
    cout << result_message << endl;
    // First we'll use it to set the threshold of the LBPHFaceRecognizer
    // to 0.0 without retraining the model. This can be useful if
    // you are evaluating the model:
    //
    
    // Now the threshold of this model is set to 0.0. A prediction
    // now returns -1, as it's impossible to have a distance below
    // it
    predictedLabel = model->predict(testSample);
    cout << "Predicted class = " << predictedLabel << endl;
    // Show some informations about the model, as there's no cool
    // Model data to display as in Eigenfaces/Fisherfaces.
    // Due to efficiency reasons the LBP images are not stored
    // within the model:
    cout << "Model Information:" << endl;
    string model_info = format("\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
            model->getRadius(),
            model->getNeighbors(),
            model->getGridX(),
            model->getGridY(),
            model->getThreshold());
    cout << model_info << endl;
    // We could get the histograms for example:
    vector<Mat> histograms = model->getHistograms();
    // But should I really visualize it? Probably the length is interesting:
    cout << "Size of the histograms: " << histograms[0].total() << endl;
    */
}


int main(int argc, const char* argv[]){
    //check for valid argument
    if (argc != 4) {
        cout << "usage:" << argv[0] << " csv.ext CameraID Classifier XML file" << endl;
        exit(1);
    }

    
    string fn_csv = string(argv[1]);
    int CameraID = atoi(argv[2]);
    string face_cascade_name = argv[3];
    vector<Mat> images;
    vector<int> labels;

    

    try{
        read_csv(fn_csv, images, labels);
    }catch ( const cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }
    model->train(images, labels);

    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };

    int camera_device = atoi(argv[1]);
    VideoCapture capture;
    //-- 2. Read the video stream
    capture.open( camera_device );
    if ( ! capture.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }
    Mat frame;
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndRecognise( frame , images, labels);
        if( waitKey(10) == 27 )
        {
            break; // escape
        }
    }
    return 0;


    if(images.size() <= 1){
        string error_message = "this demo needs more than 1 image to work";
        CV_Error(Error::StsError, error_message);
    }
}
    