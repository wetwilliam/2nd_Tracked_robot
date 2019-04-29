#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
#include <errno.h>
#include <cstdio>
//HOUGH TRANSFROM Header
#include <opencv2/opencv.hpp>
// STL Header
#include <iostream>
#include <math.h>
// OpenCV Header
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define member 100
#define member2 1000
#define thetarobot 25
#define Hrobot 30
// OpenNI Header
#include <OpenNI.h>
// namespace





//int masktype=(rand()%3)+1;
//int masktype=(rand()%2)+2;

using namespace std;
using namespace openni;
using namespace cv;




bool	g_bUseCoordinateConverter = true;
int xcenter,ycenter;
float vpixel,thetaL,thetaD,D;
int Selfdonw(int *x,float *mmvalue,int imagecount,int imagecount10);
float slope_detection(test start_point, test end_point);
void writemode(int nowmode,int nowdepth,int centerplzx,int centerplzy );
char window_name[12] ="dmage00.jpg";
char window_named[12]="ddpth00.txt";
char window_name2[12] ="dmagg00.jpg";
char window_name3[12] ="dmaga00.jpg";
int pDepth[640*480] = {0};
//int copymask(int * pDepth[640*480], int masktype);


int Selfdown(int *x,float *mmvalue,int imagecount,int imagecount10)
{

  unsigned seed;
  seed = (unsigned)time(NULL);
  srand(seed);
  float masktype=0.2;
 // float masktype=((rand()%5)+1)*0.2;//
  printf("masktype=%f",masktype);

*x=888;
*mmvalue=0.5;
FILE *fPtr;

//printf("in");
  // 1. Initial OpenNI
  if( OpenNI::initialize() != STATUS_OK )
  {
    cerr << "OpenNI Initial Error: "
         << OpenNI::getExtendedError() << endl;
    return -1;
  }

  // 2. Open Device
  Device mDevice;
  if( mDevice.open( ANY_DEVICE ) != STATUS_OK )
  {
    cerr << "Can't Open Device: "
         << OpenNI::getExtendedError() << endl;
    return -1;
  }

  // 3. Create depth stream
  VideoStream mDepthStream;
  if( mDevice.hasSensor( SENSOR_DEPTH ) )
  {
    if( mDepthStream.create( mDevice, SENSOR_DEPTH ) == STATUS_OK )
    {
      // 3a. set video mode
      VideoMode mMode;
      mMode.setResolution( 640, 480 );
      mMode.setFps( 30 );
      mMode.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );

      if( mDepthStream.setVideoMode( mMode) != STATUS_OK )
      {
        cout << "Can't apply VideoMode: "
             << OpenNI::getExtendedError() << endl;
      }
    }
    else
    {
      cerr << "Can't create depth stream on device: "
           << OpenNI::getExtendedError() << endl;
      return -1;
    }
  }
  else
  {
    cerr << "ERROR: This device does not have depth sensor" << endl;
    return -1;
  }

  // 4. Create color stream
  VideoStream mColorStream;
  if( mDevice.hasSensor( SENSOR_COLOR ) )
  {
    if( mColorStream.create( mDevice, SENSOR_COLOR ) == STATUS_OK )
    {
      // 4a. set video mode
      VideoMode mMode;
      mMode.setResolution( 640, 480 );
      mMode.setFps( 30 );
      mMode.setPixelFormat( PIXEL_FORMAT_RGB888 );

      if( mColorStream.setVideoMode( mMode) != STATUS_OK )
      {
        cout << "Can't apply VideoMode: "
             << OpenNI::getExtendedError() << endl;
      }

      // 4b. image registration

			if( !g_bUseCoordinateConverter )
			{
				// image registration
				if( mDevice.isImageRegistrationModeSupported( IMAGE_REGISTRATION_DEPTH_TO_COLOR ) )
					mDevice.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );


				else
					cerr << "This device doesn't support image registration" << endl;

			}
    }
    else
    {
      cerr << "Can't create color stream on device: "
           << OpenNI::getExtendedError() << endl;
      return -1;
    }
  }

  // 5. create OpenCV Window
  //cv::namedWindow( "Depth Image",  CV_WINDOW_AUTOSIZE );
 // cv::namedWindow( "Color Image",  CV_WINDOW_AUTOSIZE );
  //cv::namedWindow( "Clone Image",  CV_WINDOW_AUTOSIZE );
   //cv::namedWindow( "forhough Image",  CV_WINDOW_AUTOSIZE );
  // 6. start
  VideoFrameRef  mColorFrame;
  VideoFrameRef  mDepthFrame;
  mDepthStream.start();
  mColorStream.start();
  int iMaxDepth = mDepthStream.getMaxPixelValue();

//---------------------------------------------------------------------------------------------------------------------
  while( true )
  {
    // 7. check is color stream is available
    if( mColorStream.isValid() )
    {
        usleep(1000000);  //inoder to let xtion picture get enough light we need to wait 1 sec
      // 7a. get color frame
      if( mColorStream.readFrame( &mColorFrame ) == STATUS_OK )
      {
        // 7b. convert data to OpenCV format
        const cv::Mat mImageRGB( mColorFrame.getHeight(), mColorFrame.getWidth(),
			                    CV_8UC3, (void*)mColorFrame.getData() );
        // 7c. convert form RGB to BGR
        cv::Mat cImageBGR;
        cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );
        window_name3[5]= char(48+imagecount10);
        window_name3[6]= char(48+imagecount);
        window_named[5]= char(48+imagecount10);
        window_named[6]= char(48+imagecount);

         fPtr =fopen(window_named,"w");
          imwrite(window_name3,cImageBGR);
//
		cv::Mat imageforhough;
		imageforhough = cImageBGR.clone();
//        cv::Mat imageforhough;
//		imageforhough = cvLoadImage("10-150000.JPG",1);

        // 7d. show image
		cv::Mat imageClone;
		imageClone = cImageBGR.clone();
		//cv::imshow( "Color Image",cImageBGR);


		int rr=0 ;
		//------------------------------------------------------------11111111111111111111111111111111111111111111111111111111111111------------

			 //Sleep(1000);

		{  //while(true){
		 openni::Device devAnyDevice;
	  devAnyDevice.open( openni::ANY_DEVICE );// 4. create depth stream
				  openni::VideoStream streamDepth;
				  streamDepth.create( devAnyDevice, openni::SENSOR_DEPTH );
				  streamDepth.start();
				  // 5 main loop, continue read
				  openni::VideoFrameRef frameDepth;
					// 5.1 get frame
					streamDepth.readFrame( &frameDepth );
					// 5.2 get data array
					const openni::DepthPixel* pDepthori
						   = (const openni::DepthPixel*)frameDepth.getData();
					//printf("%d\t",pDepth[500]);
                   //copymask(pDepth, &formask );
                      for(int i=0;i<(307200-640);i++)
                        {
                           pDepth[i] =pDepthori[i];
                        }
					for(int iy=0;iy< frameDepth.getHeight() ;iy=iy+24)
					{// 5.3 output the depth value of center point
						for(int ix=0;ix<frameDepth.getWidth();ix=ix+64)
						{int idx = ix+iy*frameDepth.getWidth();
						 printf("%d\t",pDepth[idx]);
						 }
					}
					 printf("\n");
					//------------------
					int over[15000]={0};int iover=0;int px[15000]={0},py[15000]={0};CvPoint CircleCenter;int Radius;CvScalar Color;int Thickness;int Shift=0;int math=0;int max;
				   float mvalue[15000]={20};

					for(int i=0;i<(307200-640);i++)
					{if(pDepth[i]-pDepth[i+640]>member && pDepth[i]-pDepth[i+640] <member2)
						{if(pDepth[i+640]!=0)
							{over[iover]=i+640;py[iover]=((i+640)/640);px[iover]=((i+640)%640);
								CircleCenter=cvPoint(px[iover], py[iover]);
								Radius=1;Color=CV_RGB(255,0,0);Thickness=10;
							cv::circle(imageClone,CircleCenter,Radius, CV_RGB(255,0,0), -1, CV_AA);
							cv::circle(imageforhough,cvPoint(0,0),Radius, CV_RGB(255,0,0), -1, CV_AA);
							 iover++;

							}
						}
					}
					//------------------------------------------------------------
					//////int samevalue[15000]={0};
					//////for(int ik=0;ik<iover;ik++)
					//////{
					//////	for(int id=0;id<iover;id++)
					//////	{
					//////	double xvalue=abs(px[ik]-px[id]);
					//////	double yvalue=abs(py[ik]-py[id]);
					//////
					//////	//double totalvalue=sqrt( xvalue*xvalue+yvalue*yvalue);
					//////	double totalvalue=(0.2*xvalue+3*yvalue);
					//////	if(totalvalue<14)
				 //////       		{
					//////				 samevalue[ik]=samevalue[ik]+1;
					//////				// printf("samevalue[%d]=%d\t",ik,samevalue[ik]);
 	   //////       					}
					//////	}
					//////}
					//////max=samevalue[0];
					//////for(int ir=1;ir<iover;ir++)
					//////{
					//////	if(samevalue[ir]>max)
					//////	{
					//////		max=samevalue[ir];
					//////		math=ir;
					//////	}
					//////		//printf("math=%d\n",math);
     //////                       //printf("max=%d\n",max);
					//////
					//////}



		///////////*			cv::circle(imageClone,cvPoint(px[math],py[math]),5, CV_RGB(0,255,0), -1, CV_AA);
		//////////	printf("
		//////////	        cv::circle(imageClone,cvPoint(320,240),5, CV_RGB(0,0,255), -1, CV_AA);
		//////////			cv::circle(imageClone,cvPoint(320,300),5, CV_RGB(0,255,255), -1, CV_AA);
		//////////			cv::circle(imageClone,cvPoint(320,180),5, CV_RGB(122,255,255), -1, CV_AA);
		//////////			cv::circle(imageClone,cvPoint(320,120),1, CV_RGB(122,122,255), -1, CV_AA);*/


					//cv::imshow( "forhough Image",imageforhough);//<<--------------------------------------------------forhough
					   streamDepth.destroy();//system("pause");
					   //-----------------------------------hough-----------------------------------------------------------------------lines


					  ///////////////////// IplImage *srcImg = cvLoadImage("12-2000.jpg",1);

					//   IplImage srcImg = IplImage(imageforhough);
					//   cv* srcImg ;
					//  srcImg= cvLoadImage("ghyll.jpg",1);
					 //  IplImage* srcImg ;

					 //  srcImg = &IplImage(srcImg);

////
					   IplImage imgtemp = IplImage(imageforhough);
					   IplImage *pImg_0 = &imgtemp;
					   //pImg_skin = &IplImage(srcImg);
////							 IplImage *cannyErosionImgDilationfilterImg = NULL;
////
////                            IplImage *pImg_0 = IplImage*(imageforhough);//////////////




							 if(pImg_0 == NULL ){
								 return -1;
							 }
							 float kk[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };  //
							 CvMat km = cvMat( 3, 3, CV_32FC1, kk );
							// cvShowImage( "Source", srcImg );
							 int pos = 3;
							 IplConvKernel * pKernel = NULL;
							 pKernel = cvCreateStructuringElementEx(
								 pos*2+1,
								 pos*2+1,
								 pos,
								 pos,
								 CV_SHAPE_ELLIPSE,
								 NULL);


							 //cvShowImage("D",srcImg);
//============================================================================================================================
////////							 cvErode( pImg_skin,  pImg_skin, pKernel, 1);
////////						 	cvDilate( pImg_skin,  pImg_skin, pKernel, 1);
////////							// cvShowImage("DE",srcImg);
////////							 cvFilter2D(pImg_skin, pImg_skin, &km);
////////							 //cvShowImage("DEfilter",srcImg);
////////							 cvSmooth(pImg_skin,pImg_skin,CV_//IAN,3,3);
////////							// cvShowImage("defilterg",srcImg);
////////							// cvSmooth(srcImg,srcImg,CV_GAUSSIAN,3,3);
////////
////////
////////							// cvShowImage("canny_gause_ErosionImgDilationImg",srcImg);

//////             DE                cvDilate( pImg_skin,  pImg_skin, pKernel, 1);
//////                             cvErode( pImg_skin,  pImg_skin, pKernel, 1);
//////
                            Mat M(pImg_0,0);
                            Mat tt;

                            IplImage imgtempp = IplImage(M);
					        IplImage *img02 = &imgtempp;

//                            IplImage *img02;
//                            img02= &IplImage(M);

                            cv::bilateralFilter(M,tt,10,80,80);
                           // IplImage *pImg_skin;


                            IplImage imgtemppp = IplImage(tt);
					        IplImage *pImg_skin = &imgtemppp;

                          //  pImg_skin= &IplImage(tt);
                          // imwrite("haha",tt);
                         // cvSaveImage("haha",pImg_skin);
							 cvFilter2D(pImg_skin, pImg_skin, &km);
							 //
							 //cvSmooth(pImg_skin,pImg_skin,CV_GAUSSIAN,3,3);
                             //cvSmooth(pImg_skin,pImg_skin,CV_GAUSSIAN,3,3);
                             //
                            // cvSmooth(pImg_skin,pImg_skin,CV_GAUSSIAN,3,3);
                              cvSmooth(pImg_skin,pImg_skin,CV_GAUSSIAN,3,1);
//============================================================================================================================

							 IplImage* pSrcImg1 ;  //
							 pSrcImg1 = pImg_skin;
				   IplImage* pDstImg = cvCreateImage( cvGetSize(pSrcImg1), 8, 1 );// \dst
				   IplImage* pColorImg = cvCreateImage( cvGetSize(pSrcImg1), 8, 3 );//color
				   CvMemStorage* storage = cvCreateMemStorage(0); //
                   CvSeq* lines = 0;  //
				   IplImage* pSrcImg= cvCreateImage( cvGetSize(pSrcImg1), 8, 1 );  //
				   cvCvtColor( pSrcImg1, pSrcImg,CV_BGR2GRAY  );//
				   //cvCanny( pSrcImg, pDstImg, 100,100,3 );  /////////////////////////////////100 200 3
				    cvCanny( pSrcImg, pDstImg, 100,200,3 );
				  // cvShowImage("rr",pDstImg);
				   cvCvtColor( pDstImg, pColorImg,CV_GRAY2BGR  );//
				   //lines = cvHoughLines2( pDstImg, storage, CV_HOUGH_PROBABILISTIC,0.8, CV_PI/360,50,50,20);//0.2 50 150 20
                   lines = cvHoughLines2( pDstImg, storage, CV_HOUGH_PROBABILISTIC,0.5, CV_PI/360,80,50,40);//0.2 50 150 20  //0.8 150 150 20

				   //0.8   0.9  0.6
				 //  /*


				   int xvvs[15000],yvvs[15000];
				   int xvve[15000],yvve[15000];


				    for(int i = 0; i < lines->total; i++ )
					 {
						 int ctt=0;

					  CvPoint* line=0;

					 // line[0]=cvPoint(0,0);
					 // line[1]=cvPoint(0,0);
					 line=(CvPoint*)cvGetSeqElem(lines, i);
					//  printf("line[0]=%d %d,line[1]=%d %d ",line[0],line[1]);


					  CvPoint frompoint=cvPoint(line[0].x,line[0].y);
					  CvPoint topoint=cvPoint(line[1].x,line[1].y);
					  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                      test start_point;
                      test end_point;
					  float test_slope_value;
					  start_point.x = line[0].x;
					  start_point.y = line[0].y;
					  end_point.x = line[1].x;
					  end_point.y = line[1].y;
					  test_slope_value = slope_detection(start_point, end_point);
					  //printf("%f\n", test_slope_value);


					 // printf("i=%d  x=%d,%d,%d,%d\n",i,frompoint,topoint);
					  ctt+1;
					  int  mxvalue=(line[1].x-line[0].x);
					  int  myvalue=(line[1].y-line[0].y);
					  float a =(float)mvalue[i];
					  float b =(float)myvalue;
					  float c =(float)mxvalue;
					  xvvs[i]=line[0].x; xvve[i]=line[1].x;
					  yvvs[i]=line[0].y; yvve[i]=line[1].y;
					  if(mxvalue!=0)
					  {a=b/c;
					  mvalue[i]=a;}
					  else
					  {mvalue[i]=9999;}
					 // printf("mxvalue=%d ,myvalue=%d mva=%f\n",mxvalue,myvalue,mvalue[i]);
					  //printf("mxvalue[%d]=%d ,myvalue[%d]=%d mvalue[%d]=%d\n",i, mxvalue,i,myvalue,i,mvalue[i]);
					  	 if(abs(mvalue[i])>0.5)
                      {
                         //printf("xvvs[i]=%d xvve[i]=%d yvvs[i]=%d yvve[i]=%d",xvvs[i],xvvs[i],xvvs[i],xvvs[i]);
                          xvvs[i]=0;
                          xvve[i]=0;
                          yvvs[i]=0;
                          yvve[i]=0;
                        // printf("xvvs[i]=%d xvve[i]=%d yvvs[i]=%d yvve[i]=%d",xvvs[i],xvvs[i],xvvs[i],xvvs[i]);
                      }
                      cvLine(pColorImg,cvPoint(xvvs[i],yvvs[i]),cvPoint(xvve[i],yvve[i]),CV_RGB(0,155,0),1,CV_AA,0);
					 }




					int door=0;
					   float distance[5000];  //pherhaps here?
					float d;
					 float k= sqrt((mvalue[1]*mvalue[1])+1);
					 float tempx,tempy,tempm;// to add a new m
                         //to change point rank and i`ll  change m now
					  for(int  i1 = 0; i1 < lines->total; i1++) {
						for( int j1 = i1; j1 < lines->total; j1++) {
							if( yvvs[j1] >yvvs[i1] ) {
								// printf("%d==   %d==\n",yvvs[j1],yvvs[i1]);
								tempy = yvvs[j1];
								tempx=xvvs[j1];
								tempm=  mvalue[j1];
								yvvs[j1] = yvvs[i1];
								xvvs[j1] = xvvs[i1];
								mvalue[j1]=mvalue[i1];
								yvvs[i1] = tempy;
								xvvs[i1] = tempx;
								mvalue[i1]=tempm;

								tempy = yvve[j1];
								tempx=xvve[j1];
								yvve[j1] = yvve[i1];
								xvve[j1] = xvve[i1];
								yvve[i1] = tempy;
								xvve[i1] = tempx;
							// printf("%d=== %d=== %d==   %d==\n",j1,i1,yvvs[j1],yvvs[i1]);
							}
						}
					}
					   int maxX=xvve[(lines->total)-1];
					  int minX=xvvs[(lines->total)-1];
					   for(int  i1 = 0; i1 < lines->total; i1++) {
					  // printf(" xvvs[%d]=%d xvve[%d]=%d yvvs[%d]=%d yvve[%d]=%d ==\n",i1,xvvs[i1],i1,xvve[i1],i1,yvvs[i1],i1,yvve[i1]);
					   }
					  //

						  for( int i1 = 0; i1 < lines->total; i1++)
						  {
							  if( yvvs[(lines->total)-1]-yvvs[i1]<11 )
							  {
								  //printf("%d==   %d==",yvvs[0],yvvs[i1]);
								 // printf("%d getin",i1);
								  if (xvvs[i1]<minX)
								  {
									  minX=xvvs[i1];
									//  printf("min=%d\n",minX);
								  }
								  if (xvve[i1]>maxX)
								  {
									  maxX=xvve[i1];
									// printf("max=%d\n",maxX);
								  }
							  }
						  }
						 //  printf("min=%d max=%d \n",minX,maxX);
					   cvCircle(pColorImg,cvPoint((int)(maxX+minX)/2,(yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2),8,CV_RGB(255,255,0),-1,CV_AA,0);/////////////////////////////////////////////////////////////////////////
					   //centerx=(int)(maxX+minX)/2 centery=(yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2)

                       printf("now save\n");
					  // cvSaveImage("savetest.jpg",pSrcImg1);

					  window_name[5]= char(48+imagecount10);
					  window_name[6]= char(48+imagecount);
                       cvSaveImage(window_name,pColorImg);

					   int centerplzx,centerplzy;

					   centerplzx=(maxX+minX)/2;
					   centerplzy=(yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2;
					   // printf("centerplzx=%d,centerplzy=%d \n", centerplzx, centerplzy  );
						//----------------------------------------------------------------------------------

						//----------------------------------------------------------------------------------

						//----------------
					   for(int  i1 = (lines->total)-1 ; i1 >0; i1--)
					   {
						   //printf("i=%d  x=%d,%d \n",i1,xvvs[i1],yvvs[i1]  );
						  d=abs((mvalue[i1]*xvvs[i1-1])-yvvs[i1-1]+yvvs[i1]-(mvalue[i1]*xvvs[i1]))  /k;
						  	//printf("%f,%f,%d\n",d,k,lines->total);
							distance[i1]=d;

					   }


                        for(int  i1 = (lines->total)-1 ; i1 >0; i1--)
					   {
						   if (distance[i1]<10 || distance[i1]>10000 )
						   { distance[i1]=0;}

						   if (distance[i1]<50 && distance[i1]>12)
						   { door=door+1;
						   }

					   }
					    int countfloor=1;
						int isyou=0;
						int linedis=(lines->total)-1;
						//printf("linedis %d------distance[linedis]=%f-----\n",linedis,distance[20]);
						for(int  i1 = (lines->total)-1 ; i1 >0; i1--)
					   {

						  if (distance[i1]>0 && isyou==0)
							{  linedis=i1;
								//printf("%dstairs=%f\n",countfloor,distance[i1]);
						   countfloor=countfloor+1;
						   isyou=1;}
						   else
							  if (distance[i1]>0 && isyou==1)
						   {
							 //  printf("%dstairs=%f\n",countfloor,distance[i1]);
							  // printf("%d\n",i1);
							   countfloor=countfloor+1;
						   }

					   }
					   printf("mvalue of last line=%f",mvalue[linedis]); //the last line`s mvalue is here
                        *mmvalue=mvalue[linedis];
                        //*mmvalue=0.2;

						printf("linedis %d------distance[linedis]=%f-----",linedis,distance[linedis]);
					  if(door>=3)
					  {printf("find");}
					  else
					  {printf("not find");}

						xcenter=(xvvs[(lines->total)-1]+xvve[(lines->total)-1])/2;

						ycenter=(yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2;

						int interseptxx=xvvs[(lines->total)-1]-xvve[(lines->total)-1];
						int interseptyy=yvvs[(lines->total)-1]-yvve[(lines->total)-1];
						int summ=0; int rangex,rangey,totall=0,averagee;
						int g8=8;
						char str[256] ={'\0'};
						sprintf(str,"FPS = %d",g8);
						int counterforx=0;
						int sumforx=0;
						int kii=0;
						int averageforx=0;
						int key=0;
						int catchh[3]={0};
						int catchcounter=0;
						int hold=0;
						int catchx[3]={0},catchy[3]={0};
						int face[] = {cv::FONT_HERSHEY_SIMPLEX, cv::FONT_HERSHEY_PLAIN, cv::FONT_HERSHEY_DUPLEX, cv::FONT_HERSHEY_COMPLEX,
							cv::FONT_HERSHEY_TRIPLEX, cv::FONT_HERSHEY_COMPLEX_SMALL, cv::FONT_HERSHEY_SCRIPT_SIMPLEX,
							cv::FONT_HERSHEY_SCRIPT_COMPLEX, cv::FONT_ITALIC};
                        int a_crd,b_crd;
						//printf("%d/----------------",pDepth[centerplzx+(640*centerplzy)]);

						//----------------------
						//for mask use
                        //1.pDepth[centerplzx+(640*centerplzy)]=0;

                        //-----------------------------------------
                        //2.average x=0 and  randzero for depth
                        //
						//----------------------
                        //--------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////                        unsigned seed;
////////////////////////////////////////////////////////////////////////////////////////////////                        seed = (unsigned)time(NULL);
////////////////////////////////////////////////////////////////////////////////////////////////                        srand(seed);
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////                        if(masktype<1)
////////////////////////////////////////////////////////////////////////////////////////////////                        {
////////////////////////////////////////////////////////////////////////////////////////////////                            pDepth[centerplzx+(640*centerplzy)]={0};
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////                            if(masktype>1)//to mode3
////////////////////////////////////////////////////////////////////////////////////////////////                            {
////////////////////////////////////////////////////////////////////////////////////////////////                             for(int i=0;i<10;i++)
////////////////////////////////////////////////////////////////////////////////////////////////                             {
////////////////////////////////////////////////////////////////////////////////////////////////                                for(int j=0;j<200;j++)
////////////////////////////////////////////////////////////////////////////////////////////////                                {
////////////////////////////////////////////////////////////////////////////////////////////////                                    if(centerplzy>200)
////////////////////////////////////////////////////////////////////////////////////////////////                                       (pDepth[centerplzx+(640*(centerplzy-j))+i]={0});
////////////////////////////////////////////////////////////////////////////////////////////////                                }
////////////////////////////////////////////////////////////////////////////////////////////////                             }
////////////////////////////////////////////////////////////////////////////////////////////////                            }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////                            for(int i=0;i<640*480*masktype;i++)//mask 20%
////////////////////////////////////////////////////////////////////////////////////////////////                             {
////////////////////////////////////////////////////////////////////////////////////////////////                                    a_crd=(rand()%640);
////////////////////////////////////////////////////////////////////////////////////////////////                                    b_crd=(rand()%480);
////////////////////////////////////////////////////////////////////////////////////////////////                                    pDepth[b_crd*640+a_crd]=0;
////////////////////////////////////////////////////////////////////////////////////////////////                             }
////////////////////////////////////////////////////////////////////////////////////////////////                        } /*---mask-----*/

//////////////                        else if(masktype==3)
//////////////                        {
//////////////                            pDepth[centerplzx+(640*centerplzy)]={0};
//////////////                            for(int i=0;i<10;i++)
//////////////                            {
//////////////
//////////////                                for(int j=0;j<200;j++)
//////////////                                {
//////////////                                  pDepth[centerplzx+(640*(centerplzy-j))+i]={0};
//////////////                                }
//////////////                            }
//////////////                             for(int i=0;i<256;i++)//mask 40%
//////////////                             {
//////////////                                for(int j=0;j<480;j++)
//////////////                                {
//////////////                                    a_crd=(rand()%640);
//////////////                                    b_crd=(rand()%480);
//////////////
//////////////                                    pDepth[b_crd*640+a_crd]=0;
//////////////                                }
//////////////                             }
//////////////                        }
//////////////
//////////////                        else if(masktype==4)
//////////////                        {
//////////////                           pDepth[centerplzx+(640*centerplzy)]={0};
//////////////                            for(int i=0;i<384;i++)//mask 60%
//////////////                             {
//////////////                                for(int j=0;j<480;j++)
//////////////                                {
//////////////                                    a_crd=(rand()%640);
//////////////                                    b_crd=(rand()%480);
//////////////
//////////////                                    pDepth[b_crd*640+a_crd]=0;
//////////////                                }
//////////////                             }
//////////////                        }
//////////////
//////////////
//////////////                        else if(masktype==5)
//////////////                        {
//////////////                           pDepth[centerplzx+(640*centerplzy)]={0};
//////////////                            for(int i=0;i<512;i++)//mask80%
//////////////                             {
//////////////                                for(int j=0;j<480;j++)
//////////////                                {
//////////////                                    a_crd=(rand()%640);
//////////////                                    b_crd=(rand()%480);
//////////////
//////////////                                    pDepth[b_crd*640+a_crd]=0;
//////////////                                }
//////////////                             }
//////////////                        }


                        unsigned char tmp_value;

                        for (int i = 0; i < 480; i++)
                        {
                            for (int j = 0; j < 640; j++)
                            {
                                tmp_value = pDepth[i*640+j] * 256 / 9500;
                                fprintf(fPtr,"%d ", tmp_value);
                            }
                            fprintf(fPtr,"\n");
                        }

                        //--------------------------------------------------------------------------------------------------------


						if (pDepth[centerplzx+(640*centerplzy)]!=0)
						{
							printf("1mode,cennterdepth=%d-----------------------------------------",pDepth[centerplzx+(640*centerplzy)]);
                            *x=pDepth[centerplzx+(640*centerplzy)];
                             writemode(1,pDepth[centerplzx+(640*centerplzy)],centerplzx,centerplzy);

						}

						else if (pDepth[centerplzx+(640*centerplzy)]==0)
						{
							// printf("in-----------------------\n");
							//distance[(lines->total)-1];
							printf("distance=%f\n",distance[linedis]);
							int xaverage ;
							for (int i8=0;i8<(int)(distance[linedis]);i8++)
							{
								if(pDepth[centerplzx+(640*(centerplzy-i8))]!=0)
								{

									//printf("x=%d,y=%d depth=%d\n",centerplzx,centerplzy,pDepth[centerplzx+(640*(centerplzy-kii-1))]);
									//printf("x=%d,y=%d depth=%d\n",centerplzx,centerplzy,pDepth[centerplzx+(640*(centerplzy-kii-1))]);
									counterforx++;
									//printf("counterforx=%d",counterforx);
									//sumforx=sumforx+pDepth[centerplzx+(640*(centerplzy-i8))];
									sumforx=sumforx+pDepth[centerplzx+(640*(centerplzy-1))];
									//printf("sumforx=%d\n",sumforx);
								}
								//kii=kii+1;
							}
							if (sumforx==0)
							{
								sumforx=0;
								key=1;
								 //printf("0-----------------------\n");
								//-----------------------------------------------------------------------------------------------------------------------------------
							}
							else if (sumforx!=0)
							{
								averageforx=sumforx/counterforx;
								printf("2mode,centerdepth=%d-------------------------------\n",averageforx);
								*x=averageforx;
                                writemode(2,averageforx,centerplzx,centerplzy);
							}
						}



						for(int i=0;i<10;i++)
						{
							//
							rangex=xvvs[(lines->total)-1]+i*0.1*(interseptxx);
							rangey=yvve[(lines->total)-1]+i*0.1*(interseptyy);
							//ptx[i]=((A*pointx[i])+(B*pointy[i])+(C*pointx[i]*pointy[i])+D);
							//pty[i]=((E*pointx[i])+(F*pointy[i])+(G*pointx[i]*pointy[i])+H);
							sprintf(str," %d",(pDepth[rangex+(640*rangey)])/100);

							cv::putText(imageClone, str, cv::Point(rangex,rangey), face[0], 0.6, cv::Scalar(0,0,200), 1, CV_AA);
							summ=summ+pDepth[rangex+(640*rangey)];
							//printf("summ=%d",summ);
							//printf("a=%f %f %f",ptx[i],pty[i],i);
							//printf("a=%f %f",pointx[i],pointy[i]);

							if(pDepth[rangex+(640*rangey)]!=0)
							{
								totall=totall+1;
								// printf("depth=%d =\n totall=%d",pDepth[rangex+(640*rangey)],totall);
							}
						}

						if (totall==0)
						{
							totall=1;
						averagee=(summ/totall);
						}
						else
						{
							averagee=(summ/totall);
						}

						if (key==1)
						{ printf("here~~~\n");

							for(int i1=10;i1<20;i1++)
							//
							{
								for (int j1=0;j1<distance[linedis];j1++)
								//
								{
									if(pDepth[(centerplzx+i1)+(640*(centerplzy-j1))]!=0 && hold!=1)
									{
										if (j1==0 && catchcounter==0)
										{  // printf("j10=%d",j1);
											catchh[catchcounter]=(pDepth[(centerplzx+i1)+(640*(centerplzy-j1))]);
											catchx[catchcounter]=centerplzx+i1;
											catchy[catchcounter]=centerplzy-j1;
											printf("%d= %d=\n",catchy[j1],centerplzy-j1);
										}
										else if (j1!=0 && catchy[j1-1]!=centerplzy-j1)
										{
											//printf("j1!=0%d",j1);
										printf("catchcounter=%d\n",catchcounter);
										catchh[catchcounter]=(pDepth[(centerplzx+i1)+(640*(centerplzy-j1))]);
										catchx[catchcounter]=centerplzx+i1;
										catchy[catchcounter]=centerplzy-j1;
										printf("%d= %d=\n",catchy[j1-1],centerplzy-j1);
										printf("catchcounter=%d\n",catchcounter);
										printf("catchh[%d]=%d,catchx[catchcounter]=%d,catchy[catchcounter]=%d\n",catchcounter,catchh[catchcounter],catchx[catchcounter],catchy[catchcounter]);
										catchcounter++;
											if (catchcounter==3)
										{
											printf("in\n");
											hold=1;
										}
									   break;
									  }
									}
								}
							}


							printf("centx=%d,centery=%d",centerplzx,centerplzy);
							if (catchcounter<2)
							{
								printf("data too bad");
                                writemode(9,0,centerplzx,centerplzy);
							}

							if (catchcounter>=2)
							{
								printf("in");
								//{
								int x_1,y_1,z_1;
								int x_2,y_2,z_2;
								int x_3,y_3,z_3;
								int ztx_1,zty_1,ztz_1;
								//}pt;
								//struct vector_ab
								//{
								int abx_1,aby_2,abz_3;
								int acx_1,acy_2,acz_3;
								int tabx_1,taby_2,tabz_3;
								int numcount=0;
								int countsum=0;
								//	}vect;

								x_1=catchx[0];
								//printf("catchx[0]=%d\n",catchx[0]);
								//pt.
								y_1=catchy[0];	//printf("catchy[0]=%d\n",catchy[0]);
								//pt.
								//z_1=pDepth[pt.x_1+pt.y_1*640];
								z_1=catchh[0];//printf("catchh[0]=%d\n",catchh[0]);
								if (z_1==0)
								{z_1=1;
								}

								//pt.
								x_2=catchx[1];//printf("catchx[1]=%d\n",catchx[1]);
								//pt.
								y_2=catchy[1];//printf("catchy[1]=%d\n",catchy[1]);
								//pt.
								//z_1=pDepth[pt.x_2+pt.y_2*640];
								z_2=catchh[1];//printf("catchh[1]=%d\n",catchh[1]);
								if (z_2==0)
								{z_2=1;
								}

								//pt.
								x_3=catchx[2];//printf("catchx[2]=%d\n",catchx[2]);
								//pt.
								y_3=catchy[2];//printf("catchy[2]=%d\n",catchy[2]);
								//pt.
								//z_3=pDepth[pt.x_3+pt.y_3*640];
								z_3=catchh[2];//printf("catchh[2]=%d\n",catchh[2]);
								if (z_3==0)
								{z_3=1;
								}


								//pt.
								ztx_1=centerplzx;//printf("ztx_1=%d\n",ztx_1);
								//pt.
								zty_1=centerplzy;//printf("zty_1=%d\n",zty_1);
								//pt.ztz_1=0;

								//vect.
								//abx_1=pt.x_2-pt.x_1;
								abx_1=x_2-x_1;//printf("abx_1=%d\n",abx_1);
								//vect.
								//aby_2=pt.y_2-pt.y_1;
								aby_2=y_2-y_1;//printf("aby_2=%d\n",aby_2);
								//vect.
								//abz_3=pt.z_2-pt.z_1;
								abz_3=z_2-z_1;//printf("abz_3=%d\n",abz_3);

								//vect.
								acx_1=x_3-x_1;//printf("acx_1=%d\n",acx_1);
								//acx_1=pt.x_3-pt.x_1;
								//vect.
								//acy_2=pt.y_3-pt.y_1;
								acy_2=y_3-y_1;//printf("acy_2=%d\n",acy_2);
								//vect.
								//acz_3=pt.z_3-pt.z_1;
								acz_3=z_3-z_1;//printf("acz_3=%d\n",acz_3);

								//vect.
								//tabx_1=(vect.aby_2*vect.acz_3)-(vect.abz_3*vect.acy_2);
								tabx_1=(aby_2*acz_3)-(abz_3*acy_2);
								//vect.
								//taby_2=(vect.abz_3*vect.acx_1)-(vect.abx_1*vect.acz_3);
								taby_2=(abz_3*acx_1)-(abx_1*acz_3);
								//vect.
								//tabz_3=(vect.abx_1*vect.acy_2)-(vect.aby_2*vect.acx_1);
								tabz_3=(abx_1*acy_2)-(aby_2*acx_1);if (tabz_3==0)
								{tabz_3=1;
								}
								//pt.ztz_1=((vect.tabx_1*(pt.ztx_1-pt.x_1)+vect.taby_2*(pt.zty_1-pt.y_1))/vect.tabz_3)+pt.z_1;
								ztz_1=((tabx_1*(ztx_1-x_1)+taby_2*(zty_1-y_1))/tabz_3)+z_1;
								//printf("ztz1=%d,center=%d",ztz_1,pDepth[centerplzx+(640*centerplzy)]);
								for(int i=0;i<50;i++)
								{
									for (int j=0;j<distance[linedis];j++)
							     	{
									ztx_1=centerplzx+i;//printf("ztx_1=%d\t",ztx_1);
									zty_1=centerplzy-j;//printf("zty_1=%d\t",zty_1);
									ztz_1=((tabx_1*(ztx_1-x_1)+taby_2*(zty_1-y_1))/tabz_3)+z_1;
                                    printf("x=%d y=%d ztz1=%d,center=%d\t",ztx_1,zty_1,ztz_1,pDepth[centerplzx+(640*centerplzy)]);
									//system("pause");
									if(pDepth[centerplzx+(640*centerplzy)]!=0){
									countsum=countsum+(ztz_1-pDepth[centerplzx+(640*centerplzy)]);
									numcount++;
             						}

								   }
								}
								ztx_1=centerplzx;//printf("ztx_1=%d\t",ztx_1);
							    zty_1=centerplzy;//printf("zty_1=%d\t",zty_1);
                                ztz_1=((tabx_1*(ztx_1-x_1)+taby_2*(zty_1-y_1))/tabz_3)+z_1;
								//printf("ztz1=%d,center=%d",ztz_1,pDepth[centerplzx+(640*centerplzy)]);
                                printf("3mode,centerdepth=%d-------------------------------\n",ztz_1);
								*x=ztz_1;
								 writemode(3,ztz_1,centerplzx,centerplzy);
								//printf("countsum=%d\n",countsum);
								//printf("disl=%f,si=%f\t",distance[linedis],(countsum/(distance[linedis]*50)));


							}
						}









					        printf("averagee=%d totall=%d\n",averagee,totall);

						   //printf("xc%d yc%d\n",xcenter,ycenter);
			              {//printf("down stair =%d\n",pDepth[xcenter+ycenter*640]);
			              }
						  // cvCircle(pColorImg,cvPoint(xcenter,ycenter),5,CV_RGB(0,255,255),-1,CV_AA,0);
						  cv::imshow( "Clone Image", imageClone );


					   // d=yvvs[0]-
                    cv::circle(imageClone,cvPoint(xvve[(lines->total)-1],yvve[(lines->total)-1]),20, CV_RGB(70,0,0), -1, CV_AA);
					cv::circle(imageClone,cvPoint(xvvs[(lines->total)-1],yvvs[(lines->total)-1]),20, CV_RGB(125,0,0), -1, CV_AA);
						//cv::circle(imageClone,cvPoint(xvvs[ lines->total],yvvs[ lines->total]),20, CV_RGB(0,70,0), -1, CV_AA);
					//printf("%d\n",(yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2);

					if(  ((yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2) >=240)
					{vpixel=((yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2)-240;
					//printf("vp=%d\n",int (vpixel));
					thetaL=(atan(float (vpixel/525)))*180/3.14;
					//printf("L=%f\n",thetaL);
					thetaD=(65-thetaL);
					//printf("d=%f\n",thetaD);
					// printf("td=%f\n",tan(thetaD*3.14/180));
					D=abs(30*tan((thetaD*3.14/180)));}


					if(  ((yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2) <240)
					{vpixel=240-((yvvs[(lines->total)-1]+yvve[(lines->total)-1])/2);
					//printf("vp=%d\n",int (vpixel));
					thetaL=(atan(float (vpixel/525)))*180/3.14;
					//printf("L=%f\n",thetaL);
					thetaD=(65+thetaL);
					//printf("d=%f\n",thetaD);
                    //printf("td=%f\n",tan(thetaD*3.14/180));
					D=abs(30*tan((thetaD*3.14/180)));}

					//printf("dist=%f\n",D);
					//printf("%d\n",(yvvs[0]+yvve[0])/2);



					int count[15000]={0};

					//------------------------------choose lines-------------------------------------------------------------------------compare
			        for(int i = 0; i < lines->total; i++ )
					{
						CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);
						for(int il=0;il<iover;il++)
					{

						//-------------------------------
						if((float)(px[il]-line[0].x)!=0)
						{
							if(mvalue[i]<0.5||mvalue[i]>-0.5)
							{
							//printf("RRRRRRRRRRR1\t");
							float mvaluelocal=(float)(py[il]-line[0].y)/(float)(px[i]-line[0].x);
							//printf("line[0].y=%d\t",line[0].y);
							//printf("line[0].x=%d\t",line[0].x);
								//printf("mvaluelocal=%f\t",mvaluelocal);
								//printf("mvalue[%d]=%f\t",i,mvalue[i]);
								//--------------------------------------
								 if((int)mvaluelocal==(int)mvalue[i])
								 { count[i]=count[i]+1;
								 // printf("RRRRRRRRRRR2\t");
								// printf("count[%d]=%d\t",i ,count[i]); //kkjjj
								 }
								 //--------------------------
								 else
								 {  // printf("cff\t");
									// printf("count[%d]=%d\t",i ,count[i]);
								 }
							}
							else
							{

							}

						}
						else
						{  int m=9999;

						  // printf("RRRRRRRRRRR3\n");
						}
					}
					}

					int maxlinepoint=count[0];
					int value=0;
					for(int ir=1;ir<lines->total;ir++)
					{
						if(count[ir]>maxlinepoint)
						{
							maxlinepoint=count[ir];
							value=ir;
							//printf("value=%d\n",value);
							//printf("maxlinepoint=%d\n",maxlinepoint);
						}
							//printf("math=%d\n",math);
                            //printf("max=%d\n",max);
					}


					CvPoint* line = (CvPoint*)cvGetSeqElem(lines, value);
				   // cvLine( pColorImg,cvPoint(xvvs[value],yvvs[value]) ,cvPoint(xvve[value],yvve[value]), CV_RGB(255,0,0), 1, CV_AA, 0 );-------------------------------------------------redline

						int pointx[10],pointy[10];
						//int ptx[10],pty[10];
						int sum=0;
						int average=777;
						int interseptx=line[1].x-line[0].x;
						int intersepty=line[1].y-line[0].y;
						int centerpointx=line[0].x+0.5*interseptx;
						int centerpointy=line[0].y+0.5*intersepty;
						int getDepthnew =500;
						int access;
						 // cvCircle(pColorImg,cvPoint(centerpointx,centerpointy),5,CV_RGB(0,0,255),-1,CV_AA,0);  ----------------------------bluepoint
						//float A=0.9957,
//B=0.0018,
//C=0,
//D=6.2057,
//E=0.0458,
//F=0.8384,
//G=0,
//H=20.9820;
						if( cv::waitKey( 1 ) == 'q' )
						{break;}

						float total=0.0001;

						for(int i=0;i<10;i++)
						{

						pointx[i]=(line[1].x)-i*0.1*(interseptx);
						pointy[i]=(line[1].y)-i*0.1*(intersepty);
						//ptx[i]=((A*pointx[i])+(B*pointy[i])+(C*pointx[i]*pointy[i])+D);
                        //pty[i]=((E*pointx[i])+(F*pointy[i])+(G*pointx[i]*pointy[i])+H);
						sum=sum+pDepth[pointx[i]+(640*pointy[i])];
						//printf("sum=%d",sum);
						//printf("a=%f %f %f",ptx[i],pty[i],i);
						//printf("a=%f %f",pointx[i],pointy[i]);

						if(pDepth[pointx[i]+640*pointy[i]]!=0)
						{
						 	total=total+1;
						}
						}
						average=(sum/total);
						//int mrate;
						//---------------------------------------
						//if(average>2948)
						//{
						//	mrate=(0.041*average)-88.5;
						//}
						//else if(average>2576)
						//{
						//	mrate=(0.0256*average)-34.4;
						//}
						//else
						//{mrate=(0.03254*average)-54.65;}

						//printf("mrate=%dmm",mrate);
						//printf("%dmm green\n",pDepth[px[math]+py[math]*640]);
						//printf("average=%dmm",average);
						if(  (pDepth[px[math]+py[math]*640])-150  <= average  && average <= pDepth[px[math]+py[math]*640]+150 )
						{
							//printf("good depth=%d at %d,%d \n",pDepth[px[math]+py[math]*640],px[math],py[math]);

							getDepthnew=pDepth[px[math]+py[math]*640];
							access=1;
					}
						else
						{
						//printf ("fault\n");
						  getDepthnew= getDepthnew-500;
						  if(getDepthnew<1000)
						  {
							  getDepthnew=0;
							  access=0;
						  }
						}
						//------------------------------------------------------------------------------------
				if(access==1){
						if(centerpointx<320)
						{

						 //   bodyvel(350,350);
						//	bodyact("left");
							//Sleep(500-(centerpointx-320));
							//bodyact("stop");

							//system("pause");
						}

						else if(centerpointx>320)
						{
							;
						   //   bodyvel(350,350);
							//bodyact("right");
							//Sleep(500);
							//bodyact("stop");

							//system("pause");
						}

						else if (centerpointx==320)
						{

							//system("pause");
						}

						if(getDepthnew>0)
						{
						//------------------------
						//bodyvel(350,350);
						//legact("fwd","");
						//bodyact("fwd");=]
			           // Sleep(5000);
			           // bodyact("stop");

					   // system("pause");
						//-----------------------
						}
						if( getDepthnew=0)
						{

							system("pause");

						}
					}
				else
				{
				    //printf("find is fault");
				}
					//----------------------------------------------------------------------------------------------------------
					//----------------------------------------------------------------------------------------------------------
					//printf("valu0e=%d\n",value);
					//printf("kt0=%d\n",count[0]);
					 //cvShowImage( "Source", pSrcImg );
					cvShowImage( "Hough", pColorImg );
					//rr=rr+1;
     //  }


	 }
      }
    }


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // 8a. get depth frame
    if( mDepthStream.readFrame( &mDepthFrame ) == STATUS_OK )
    {
      // 8b. convert data to OpenCV format
      const cv::Mat mImageDepth(
                mDepthFrame.getHeight(), mDepthFrame.getWidth(),
                CV_16UC1, (void*)mDepthFrame.getData() );
      // 8c. re-map depth data [0,Max] to [f0,255]
      cv::Mat mScaledDepth;
      mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / iMaxDepth );
      window_name2[5]= char(48+imagecount10);
      window_name2[6]= char(48+imagecount);
      imwrite(window_name2,mScaledDepth);
      // 8d. show imagec
     // cv::imshow( "Depth Image", mScaledDepth );
    }
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	//------------------------------------------------------------------------------

	 //-----------------------------------------------------------------------------
    // 6a. check keyboard

  // printf("see you\n");
	{break;}


  }

  // 9. stop
  mDepthStream.destroy();
  mColorStream.destroy();
  fclose(fPtr);
  mDevice.close();
  OpenNI::shutdown();

  return 0;
}

float slope_detection(test start_point, test end_point)
{
    test m;
    int slope;
    m.x = (float) end_point.x - start_point.x;
    m.y = (float) end_point.y - start_point.y;

    if (m.x != 0)
    {
        slope = m.y / m.x;
    }
    else
    {
        slope = 9999;
    }
    return slope;
}
