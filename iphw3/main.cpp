#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Mat img = imread("/Users/sovietreborn/Desktop/lena_color.jpg"),imggray;
    if(img.empty())
    {
        fprintf(stderr, "Can not load image \n");
        return -1;
    }
    Mat resultlap;
    Mat graytmp,graytmp7;
    resultlap.create(img.size(),img.type());
    imggray.create(img.size(),img.type());
    cvtColor(img,imggray,CV_RGB2GRAY);
    imwrite("/Users/sovietreborn/Desktop/gray.jpg", imggray);
    Mat imggrayN;
    imggrayN.create(img.size(),img.type());
    imggrayN=imggray;
    int i, j,k,number,wb;
    number=img.cols*img.rows*0.25;
    for(k=0;k<number;k++)
    {
        int m=1;
        while(m){
        i=rand()%img.cols;
        j=rand()%img.rows;
            if (imggrayN.at<uchar>(j,i)!=255||imggrayN.at<uchar>(j,i)!=0)
            {
                m=0;
                wb=rand()%2;
                imggrayN.at<uchar>(j,i)=255*wb;
            }
        }
    }
    Mat blur7;
    cv::medianBlur(imggrayN, blur7, 7);
    
    imwrite("/Users/sovietreborn/Desktop/graynoise.jpg", imggrayN);
    imwrite("/Users/sovietreborn/Desktop/blur7.jpg", blur7);

    Mat graysmooth;
    graysmooth.create(img.size(),img.type());
    graysmooth=imggrayN.clone();
    Mat_<uchar> gray777=cv::Mat::zeros(50, 1, CV_32F);
    for(int j= 3; j<img.rows-3; ++j)
        
    {
        
        const uchar *prepreprevious = graysmooth.ptr<const uchar>(j-3);
        const uchar *preprevious = graysmooth.ptr<const uchar>(j-2);
        
        const uchar *previous = graysmooth.ptr<const uchar>(j-1);
        
        const uchar *current = graysmooth.ptr<const uchar>(j);
        
        const uchar *next = graysmooth.ptr<const uchar>(j+1);
        
        const uchar *nextnext = graysmooth.ptr<const uchar>(j+2);
        const uchar *nextnextnext = graysmooth.ptr<const uchar>(j+3);
        
        uchar *output = graysmooth.ptr<uchar>(j);
        
        for(int k= 3; k<img.cols-3; ++k)
            {   int cnt=0;
                for(int gi=0;gi<49;gi+=7)
            {
                gray777.at<uchar>(gi,0)=prepreprevious[k-3+cnt];
                gray777.at<uchar>(gi+1,0)=preprevious[k-3+cnt];
                gray777.at<uchar>(gi+2,0)=previous[k-3+cnt];
                gray777.at<uchar>(gi+3,0)=current[k-3+cnt];
                gray777.at<uchar>(gi+4,0)=next[k-3+cnt];
                gray777.at<uchar>(gi+5,0)=nextnext[k-3+cnt];
                gray777.at<uchar>(gi+6,0)=nextnextnext[k-3+cnt];
                cnt++;
            }
  
                graytmp.release();
            cv::sort(gray777, graytmp,CV_SORT_DESCENDING+CV_SORT_EVERY_COLUMN);
                int cnti=0;
            for (int i=50-1; i>=0; i--) {
                if (graytmp.at<uchar>(i,0)==0) {
                    cnti++;
                }
             }

           output[k]=graytmp.at<uchar>((48+cnti)/2,0);
        }
    }
        imwrite("/Users/sovietreborn/Desktop/graynoisesmooth.jpg", graysmooth);
    Mat grayadaptive;
    grayadaptive.create(img.size(),img.type());
    grayadaptive=imggrayN.clone();
    for(int j= 3; j<img.rows; ++j)
        
    {
        const uchar *prepreprevious = grayadaptive.ptr<const uchar>(j-3);
        const uchar *preprevious = grayadaptive.ptr<const uchar>(j-2);

        const uchar *previous = grayadaptive.ptr<const uchar>(j-1);
        
        const uchar *current = grayadaptive.ptr<const uchar>(j);
        
        const uchar *next = grayadaptive.ptr<const uchar>(j+1);
        
        const uchar *nextnext = grayadaptive.ptr<const uchar>(j+2);
        const uchar *nextnextnext = grayadaptive.ptr<const uchar>(j+3);
        
        uchar *output = grayadaptive.ptr<uchar>(j);
        
        for(int k= 3; k<img.cols; k++)
            
        {
            Mat_<uchar> gray33=cv::Mat::zeros(10, 1, CV_32S);
            int Zmax,Zmin,Zmed;
            int Zxy,gi;
            int i=k;
            int cnt=0;
            graytmp.release();
            for(gi=0;gi<9;gi+=3)
            {
                cnt++;
                gray33.at<uchar>(gi,0)=previous[k-1+cnt];
                gray33.at<uchar>(gi+1,0)=current[k-1+cnt];
                gray33.at<uchar>(gi+2,0)=next[k-1+cnt];
                
            }
            cv:sort(gray33, graytmp,CV_SORT_ASCENDING+CV_SORT_EVERY_COLUMN);
            cnt=0;
            for (int i=9-1; i>=0; i--) {
                if (graytmp.at<uchar>(i,0)==0) {
                    cnt++;
                }
            }
            Zmax=graytmp.at<uchar>(8,0);
            Zmin=graytmp.at<uchar>(0,0);
            Zmed=graytmp.at<uchar>((9+cnt)/2,0);
            Zxy=current[i];
            if (Zmed-Zmin>0&&Zmed-Zmax<0) {
                if (Zxy-Zmin>0&&Zxy-Zmax<0) {
                    output[i] =current[i];
                }
                else
                    output[i] =graytmp.at<uchar>((9+cnt)/2,0);
            }
                else
                {
              
                Mat_<uchar> gray55=cv::Mat::zeros(26, 1, CV_32S);
                    graytmp.release();
                    cnt=0;
                for(gi=0;gi<25;gi+=5)
                    {
                        cnt++;
                        gray55.at<uchar>(gi+0,0)=preprevious[k-2+cnt];
                        gray55.at<uchar>(gi+1,0)=previous[k-2+cnt];
                        gray55.at<uchar>(gi+2,0)=current[k-2+cnt];
                        gray55.at<uchar>(gi+3,0)=next[k-2+cnt];
                        gray55.at<uchar>(gi+4,0)=nextnext[k-2+cnt];
                        
                    }
                    cv::sort(gray55, graytmp,CV_SORT_ASCENDING+CV_SORT_EVERY_COLUMN);
                    cnt=0;
                    for (int i=25-1; i>=0; i--) {
                        if (graytmp.at<uchar>(i,0)==0) {
                            cnt++;
                        }
                    }
                    Zmax=graytmp.at<uchar>(24,0);
                    Zmin=graytmp.at<uchar>(0,0);
                    Zmed=graytmp.at<uchar>((24+cnt)/2,0);
                if (Zmed-Zmin>0&&Zmed-Zmax<0) {
                    if (Zxy-Zmin>0&&Zxy-Zmax<0) {
                        output[i] =current[i];
                    }
                    else
                        output[i] =graytmp.at<uchar>((24+cnt)/2,0);
                }
                else{
                    Mat_<uchar> gray77=cv::Mat::zeros(50, 1, CV_32S);
                    
                graytmp.release();
                    int cnt=0;
                    for(int gi=0;gi<49;gi+=7)
                    {
                        cnt++;
                        gray777.at<uchar>(gi,0)=prepreprevious[k-3+cnt];
                        gray777.at<uchar>(gi+1,0)=preprevious[k-3+cnt];
                        gray777.at<uchar>(gi+2,0)=previous[k-3+cnt];
                        gray777.at<uchar>(gi+3,0)=current[k-3+cnt];
                        gray777.at<uchar>(gi+4,0)=next[k-3+cnt];
                        gray777.at<uchar>(gi+5,0)=nextnext[k-3+cnt];
                        gray777.at<uchar>(gi+6,0)=nextnextnext[k-3+cnt];
                        
                    }
                 cv::sort(gray77, graytmp,CV_SORT_ASCENDING+CV_SORT_EVERY_COLUMN);
                    cnt=0;
                    for (int i=49-1; i>=0; i--) {
                        if (graytmp.at<uchar>(i,0)==0) {
                            cnt++;
                        }
                    }
                    Zmax=graytmp.at<uchar>(48,0);
                    Zmin=graytmp.at<uchar>(0,0);
                    Zmed=graytmp.at<uchar>((48+cnt)/2,0);
                if (Zmed-Zmin>0&&Zmed-Zmax<0) {
                    if (Zxy-Zmin>0&&Zxy-Zmax<0) {
                        output[i] =current[i];
                    }
                    else
                        output[i]=graytmp.at<uchar>((48+cnt)/2,0);;
                }
                else
                    output[i] =current[i];
                }


            }
           
        }
    }
    imwrite("/Users/sovietreborn/Desktop/graynoiseactive.jpg", grayadaptive);

    return 0;
}
