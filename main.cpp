#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "ui_mainwindow.h"
#include <QString>
#include <QtCore>
#include <QCoreApplication.h>
#include <iostream>

using namespace std;
using namespace cv;

int detectAndDraw(Mat& img, CascadeClassifier& cascade,
    CascadeClassifier& nestedCascade,
    double scale, bool tryflip, MainWindow& mainwindow);

string cascadeName;
string nestedCascadeName;

int main(int argc, char* argv[])
{
    // QT
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    

    // OPENCV
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    bool tryflip;

    CascadeClassifier cascade, nestedCascade;
    double scale;

    // import detecte face and smile from opencv
    cv::CommandLineParser parser(argc, argv,
        "{scale|1|}"
        "{cascade|data/haarcascades/haarcascade_frontalface_alt.xml|}"
        "{smile-cascade|data/haarcascades/haarcascade_smile.xml|}"
        "{try-flip||}{@input||}");

    cascadeName = samples::findFile(parser.get<string>("cascade"));
    nestedCascadeName = samples::findFile(parser.get<string>("smile-cascade"));
    tryflip = parser.has("try-flip");
    inputName = parser.get<string>("@input");
    scale = parser.get<int>("scale");

    if (scale < 1)
        scale = 1;

    if (!cascade.load(cascadeName))
    {
        return -1;
    }
    if (!nestedCascade.load(nestedCascadeName))
    {
        return -1;
    }
    if (inputName.empty() || (isdigit(inputName[0]) && inputName.size() == 1))
    {
        int c = inputName.empty() ? 0 : inputName[0] - '0';
        if (!capture.open(c))
            cout << "Capture from camera #" << c << " didn't work" << endl;
    }
    else if (inputName.size())
    {
        inputName = samples::findFileOrKeep(inputName);

    }

    if (capture.isOpened())
    {


        for (;;)
        {
            capture >> frame;
            if (frame.empty())
                break;

            Mat frame1 = frame.clone();

            int resultFace = detectAndDraw(frame1, cascade, nestedCascade, scale, tryflip, mainWindow);

            // application is closed
            if (resultFace == -1) {
                return -1;
            }
            // smile detected && currentRound is a number from 0 to 10 
            else if (resultFace == 1 && mainWindow.nextRoundIndex != 0 && mainWindow.nextRoundIndex != 10) {
                mainWindow.hasPlayerSmiled = true;
                mainWindow.setTitle("VOUS AVEZ PERDU !");
            }
            // player do not smiled && cuurrentround == 10
            else if (mainWindow.hasPlayerSmiled == false && mainWindow.nextRoundIndex == 10) {
                mainWindow.setTitle("VOUS AVEZ GAGNE !");
            }

            char c = (char)waitKey(10);
            if (c == 27 || c == 'q' || c == 'Q')
                break;
        }
    }
    else
    {
        return -1;
    }
    // FIN OPENCV

    // QT
    return a.exec();
}
int detectAndDraw(Mat& img, CascadeClassifier& cascade,
    CascadeClassifier& nestedCascade,
    double scale, bool tryflip, MainWindow& mainWindow)
{
    cout << "CloseGame " << mainWindow.CloseGame << endl;
    if (mainWindow.CloseGame == true) {
        return -1;
    }
    vector<Rect> faces, faces2;
    const static Scalar colors[] =
    {
        Scalar(255,0,0),
        Scalar(255,128,0),
        Scalar(255,255,0),
        Scalar(0,255,0),
        Scalar(0,128,255),
        Scalar(0,255,255),
        Scalar(0,0,255),
        Scalar(255,0,255)
    };
    Mat gray, smallImg;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    // non mais la d�claration de la fenetre c'est l�
    double fx = 1 / scale;
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT);
    equalizeHist(smallImg, smallImg);

    cascade.detectMultiScale(smallImg, faces,
        1.1, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        | CASCADE_SCALE_IMAGE,
        Size(30, 30));
    if (tryflip)
    {
        flip(smallImg, smallImg, 1);
        cascade.detectMultiScale(smallImg, faces2,
            1.1, 2, 0
            //|CASCADE_FIND_BIGGEST_OBJECT
            //|CASCADE_DO_ROUGH_SEARCH
            | CASCADE_SCALE_IMAGE,
            Size(30, 30));
        for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r)
        {
            faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }
    }

    for (size_t i = 0; i < faces.size(); i++)
    {
        
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i % 8];
        int radius;

        double aspect_ratio = (double)r.width / r.height;
        if (0.75 < aspect_ratio && aspect_ratio < 1.3)
        {
            center.x = cvRound((r.x + r.width * 0.5) * scale);
            center.y = cvRound((r.y + r.height * 0.5) * scale);
            radius = cvRound((r.width + r.height) * 0.25 * scale);
            circle(img, center, radius, color, 3, 8, 0);
        }
        else
            rectangle(img, Point(cvRound(r.x * scale), cvRound(r.y * scale)),
                Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
                color, 3, 8, 0);

        const int half_height = cvRound((float)r.height / 2);
        r.y = r.y + half_height;
        r.height = half_height - 1;
        smallImgROI = smallImg(r);
        nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
            1.1, 0, 0
            //|CASCADE_FIND_BIGGEST_OBJECT
            //|CASCADE_DO_ROUGH_SEARCH
            //|CASCADE_DO_CANNY_PRUNING
            | CASCADE_SCALE_IMAGE,
            Size(30, 30));

        // The number of detected neighbors depends on image size (and also illumination, etc.). The
        // following steps use a floating minimum and maximum of neighbors. Intensity thus estimated will be
        //accurate only after a first smile has been displayed by the user.
        const int smile_neighbors = (int)nestedObjects.size();
        static int max_neighbors = -1;
        static int min_neighbors = -1;
        if (min_neighbors == -1) min_neighbors = smile_neighbors;
        max_neighbors = MAX(max_neighbors, smile_neighbors);

        // Draw rectangle on the left side of the image reflecting smile intensity
        float intensityZeroOne = ((float)smile_neighbors - min_neighbors) / (max_neighbors - min_neighbors + 1);
        int rect_height = cvRound((float)img.rows * intensityZeroOne);
        Scalar col = Scalar((float)255 * intensityZeroOne, 0, 0);

        cout << intensityZeroOne << endl;

        //if (intensityZeroOne < 1) {
        //    mainwindow.setHasPlayerSmiled(true);
        //}

        rectangle(img, Point(0, img.rows), Point(img.cols / 10, img.rows - rect_height), col, -1);
        if (intensityZeroOne > 0.8) {
            return 1;
        }
    }
    imshow("Webcam", img);
}