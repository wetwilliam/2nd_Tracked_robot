#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <cstdio>
#include <iostream> //lib use in c++
#include <time.h>
#define NUM_THREADS 5

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

///*---Header Files---*/
////OpenNI
#include "TrackedRobot_ActionHrader/OpenniSet.h" //OpenNI Setting
//
////Tracked Robot Motor Control
#include "TrackedRobot_MotorHeader/MotorSet.h"
#include "TrackedRobot_MotorHeader/Slim5_CS.h"
#include "TrackedRobot_MotorHeader/Slim5_JG.h"
#include "TrackedRobot_MotorHeader/Slim5_MA.h"
#include "TrackedRobot_MotorHeader/Slim5_MR.h"
#include "TrackedRobot_MotorHeader/Slim5_Speed.h"
#include "TrackedRobot_MotorHeader/Slim9_XtionMotor.h"
#include "TrackedRobot_MotorHeader/MotorEncoder.h"
#include "TrackedRobot_ActionHrader/SelfMode.h"
#include "TrackedRobot_ActionHrader/WillyMode.h"
#include "TrackedRobot_ActionHrader/MaskMode.h"

//
////Tracked Robot Mission
#include "TrackedRobot_ActionHrader/Fuzzy.h"
#include "TrackedRobot_ActionHrader/XtionDepth.h"
#include "TrackedRobot_ActionHrader/WallFollowing.h"
#include "TrackedRobot_ActionHrader/OtherFunction.h"
#include "TrackedRobot_ActionHrader/UpStairsMode.h"
#include "TrackedRobot_ActionHrader/DownStairsMode.h"
#include "TrackedRobot_ActionHrader/ObstacleAvoidance.h"
#include "TrackedRobot_ActionHrader/TR_ManualControl.h"

//// OpenCV Header
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//////pthread Header
#include <pthread.h>
#define NUM_THREADS 5
#define OpenNI_Resolution_x 640
#define OpenNI_Resolution_y 480
//
//int* test()
//{
//    int a = 0;
//    int b = 1;
//    int c = 2;
//    ///////////
//    //dynamic matrix
//    int* d;
//    d = new int[3];
//
//    ///////////
//    //mid_x mid_y
//    d[0] = a;
//    d[1] = b;
//    d[2] = c;
//
//    return d;
//}
int x=88888;
float mmvalue=0.0000000;
int imagecount= 0, imagecount10= 0;
int mode =0;
int main( int argc, char** argv )
{

  if(Motor_initial() < 0) //  Check Motor Open
    {
        printf("End\n");
        return 0;
    }
       //---Set JG vel
	bodyJOGvel(1000,1000);
	usleep(10000);
    legJOGvel(300,300);
	usleep(10000);
    //---Set MA vel
	bodyMAvel(700,700); //700
    usleep(10000);
	legMAvel(200,200);  //200
	usleep(10000);
    //---Set CS
	legcs(0,0);
	usleep(10000);
	bodycs(0,0); //0,0
	usleep(10000);
    //---Set VA
	bodyva(900,900); //set Acceleration : 900, 500
	legva(600,600);
    usleep(10000);
    //---Climb stairs leg set 90 Degree
    //legma(-30000,-28500); //climb stairs legs initial
    //XtionMotor(900,0);
/*---Tracked Robot Manual Control---*/

    if(TrackRobot_ManualControl() < 0)
    {
        printf("TrackRobot_ManualControl End\n");
        return 0;
    }

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////    bodyJOGvel(350,350);
////////////////////////////////////////////////////////////////////////////////////////////////    bodyact("fwd");
////////////////////////////////////////////////////////////////////////////////////////////////    usleep(50000);   //here may let the count time more slow
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////    printf("%d\n",MotorPE(0));
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////    bodyJOGvel(350,350);
////////////////////////////////////////////////////////////////////////////////////////////////    bodyact("left");
////////////////////////////////////////////////////////////////////////////////////////////////    usleep(50000);   //here may let the count time more slow

//    int* a;
//    a = test();
//    printf("%d\t%d\t%d\n", a[0], a[1], a[2]);
//
//------------------------
//while(x>800)  //for outside version
//   {
//      Motor_close();
//      SelfMode(&x,&mvalue); //call calculate
//      printf("depth=%d!!!!!!!!!!!!!!!!!!!!!!!!!!!  mvalue=%f",x,mvalue); //show data
//
//     //--
//          while(x==0)
//           { SelfMode(&x,&mvalue); //call calculate
//             printf("%d",x); //show data
//           }
//        if(Motor_initial() < 0) //  Check Motor Open
//    {
//        printf("End\n");
//        return 0;
//    }
//
//    mode_WillyNear(mvalue);
//
//
//   }
//       printf("wait\n");
//   bodyJOGvel(350,350);
//    bodyact("fwd");
//    usleep(3000000);   //here may let the count time more slow
//
//
//    legact("stop","stop");
//    usleep(50000);
//--------------------------
OpenNI_initialize();  //In order to change mode ,we first use mode to detect whether it is bright or dark. If dark, it will turn to depth
//mode_1();
//mode_21();
//mode_3();
//OpenNI_close();

//    XtionMotor(1000,0); //Put in mode 9
//    usleep(50000);


//WallFollowing_LeftWall();

//
//while(x>1000)
//{
//    mode = 1;
//      Motor_close();
//      SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//      printf("depth=%d mmvalue=%f",x,mmvalue); //show data
//
//     //--
//     while(x ==0)  //for outside version
//          { SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//           printf("%d",x); //show data
//          }
//        if(Motor_initial() < 0) //  Check Motor Open
//    {
//        printf("End\n");
//        return 0;
//    }
//
//    mode_WillyNear(mmvalue);
//
//   imagecount=imagecount+1;
//   if(imagecount>=10)
//     {
//         imagecount=imagecount-10;
//         imagecount10=imagecount10+1;
//     }
//   }
//       printf("wait\n");
//   bodyJOGvel(350,350);
//    bodyact("fwd");
//    usleep(5000000);   //here may let the count time more slow
//
//
//    legact("stop","stop");
//    usleep(50000);
////----------------------------

/*----------------01 for outside climbing----------*/
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////while(x>800)
//////////////////////////////////////////////////////////////////////////////////////{
//////////////////////////////////////////////////////////////////////////////////////    mode = 0;
//////////////////////////////////////////////////////////////////////////////////////      Motor_close();
//////////////////////////////////////////////////////////////////////////////////////      SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//////////////////////////////////////////////////////////////////////////////////////      printf("depth=%d mmvalue=%f",x,mmvalue); //show data
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////     //--
//////////////////////////////////////////////////////////////////////////////////////     while(x ==0)  //for outside version
//////////////////////////////////////////////////////////////////////////////////////          { SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//////////////////////////////////////////////////////////////////////////////////////           printf("%d",x); //show data
//////////////////////////////////////////////////////////////////////////////////////          }
//////////////////////////////////////////////////////////////////////////////////////        if(Motor_initial() < 0) //  Check Motor Open
//////////////////////////////////////////////////////////////////////////////////////    {
//////////////////////////////////////////////////////////////////////////////////////        printf("End\n");
//////////////////////////////////////////////////////////////////////////////////////        return 0;
//////////////////////////////////////////////////////////////////////////////////////    }
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////    mode_WillyNear(mmvalue);
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////   imagecount=imagecount+1;
//////////////////////////////////////////////////////////////////////////////////////   if(imagecount>=10)
//////////////////////////////////////////////////////////////////////////////////////     {
//////////////////////////////////////////////////////////////////////////////////////         imagecount=imagecount-10;
//////////////////////////////////////////////////////////////////////////////////////         imagecount10=imagecount10+1;
//////////////////////////////////////////////////////////////////////////////////////     }
//////////////////////////////////////////////////////////////////////////////////////   }
//////////////////////////////////////////////////////////////////////////////////////       printf("wait\n");
//////////////////////////////////////////////////////////////////////////////////////   bodyJOGvel(350,350);
//////////////////////////////////////////////////////////////////////////////////////    bodyact("fwd");
//////////////////////////////////////////////////////////////////////////////////////    usleep(5000000);   //here may let the count time more slow

//////////////////          printf("wait\n");
//////////////////   bodyJOGvel(350,350);
//////////////////    bodyact("fwd");
//////////////////    usleep(8000000);   //here may let the count time more slow 33000000


    legact("stop","stop");
    usleep(50000);


/*---------------------01 out side climbing-------------------------*/

//OpenNI_initialize();
//////////////
////////////    mode_021();
////////////    mode_03();
////////////    mode_04();
////////////
//////////////    mode_21();
//////////////    mode_3();
//////////////    mode_4();
////////////
////////////
//////////////---Mission.01 : Down Stairs---
//////////////===========================
////////////    mode_9(1); //turn 180
/////////////*===========================*/
////////////
////////////    //mode_5();
////////////    if(mode_6() < 0)  //Check Sensor Open
////////////    {
////////////        printf("Mode6 End.\n  ");
////////////        return 0;
////////////    }
////////////    mode_7(); //act_4f, in side


/*---------------------02 outside both up and down use rgbd-------------------*/

//while(x>800)
//{
//    mode = 0;
//      Motor_close();
//      SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//      printf("depth=%d mmvalue=%f",x,mmvalue); //show data
//
//     //--
//     while(x ==0)  //for outside version
//          { SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//           printf("%d",x); //show data
//          }
//        if(Motor_initial() < 0) //  Check Motor Open
//    {
//        printf("End\n");
//        return 0;
//    }
//
//    mode_WillyNear(mmvalue);
//
//   imagecount=imagecount+1;
//   if(imagecount>=10)
//     {
//         imagecount=imagecount-10;
//         imagecount10=imagecount10+1;
//     }
//   }
//       printf("wait\n");
//   bodyJOGvel(350,350);
//    bodyact("fwd");
//    usleep(5000000);   //here may let the count time more slow
//
//
//    legact("stop","stop");
//    usleep(50000);


//    mode_021();
//    mode_03();
//    mode_04();
//
//
////---Mission.01 : Down Stairs---
////===========================
//    mode_9(1); //turn 180
///*===========================*/
//
//        XtionMotor(550,0); //Put in mode 9
//    usleep(2000000);
//
//while(x>800)
//{
//    mode = 1;
//      Motor_close();
//      SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//      printf("depth=%d mmvalue=%f",x,mmvalue); //show data
//
//     //--
//     while(x ==0)  //for outside version
//          { SelfMode(&x,&mmvalue,imagecount,imagecount10,mode); //call calculate
//           printf("%d",x); //show data
//          }
//        if(Motor_initial() < 0) //  Check Motor Open
//    {
//        printf("End\n");
//        return 0;
//    }
//
//    mode_WillyNear(mmvalue);
//
//   imagecount=imagecount+1;
//   if(imagecount>=10)
//     {
//         imagecount=imagecount-10;
//         imagecount10=imagecount10+1;
//     }
//   }
//       printf("wait\n");
//   bodyJOGvel(350,350);
//    bodyact("fwd");
//    usleep(5000000);   //here may let the count time more slow
//
//
//    legact("stop","stop");
//    usleep(50000);
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n  ");
//        return 0;
//    }
//    mode_7(); //act_4f, in side
/*-----------------------------02 -----------------------------------------------*/

   // OpenNI_initialize();
     // sleep(5000);

/*--- Mission.01 : UP stairs---*/

//    mode_1();
//    mode_21();
//    mode_3();
//    mode_4();
//
////---Mission.02 : Continuous "Up" Stairs---
////===========================
//    //mode_9(2);  //Continuous Up(4F to 5F)
//    mode_9(4);  //Continuous Up(3F to 4F)
////===========================
//    mode_21();
//    mode_3();
//    mode_4();

//    printf("Continuous Up Stairs End\n");
///12345 avoid
////---Close OpenNI (Xtion)---
//    OpenNI_close();
//    printf("Close OpenNI\n");
//
////---Open OpenNI (Xtion)---
//    OpenNI_initialize_OB();
//    printf("OpenNI initialize OB Open\n");
//
////---For Obstacle Avoidance Test---
//    double Car_VL=0,Car_VR=0;
//    double Last_Car_VL=0,Last_Car_VR=0;
//    double rlime=0;
//
//    double main_d1=0,main_d2=0;
//    char direction = NULL;
//
//    int ob_time = 0;
//    int key=0;
//    XtionMotor(900,0); //Ori: 730
//    sleep(3);
//
//    int High_speed=600;
//
//
//    bodyJOGvel(High_speed,High_speed);
//    usleep(2000);
//    bodyact("fwd");
//    usleep(2000);
//    Last_Car_VL=High_speed;
//    Last_Car_VR=High_speed;
//
//    int cnt_break=0;
//    int last_depth;
//
//    int j=0;
//
//    while(ob_time < 1000)
//    {
////        FILE *ob_VL=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/OBdata/VL.txt","a");
////        FILE *ob_VR=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/OBdata/VR.txt","a");
////        FILE *ob_rlime=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/OBdata/r.txt","a");
//
//       /*---ob st---*/
//        int st_c=0,st_b=0,st_a=0;
//
//
//        st_c = Avoidance_DataAnalysis_Block_C();
//        st_b = Avoidance_DataAnalysis_Block_B();
//        st_a = Avoidance_DataAnalysis_Block_A();
//
//        /*---print std---*/
//        int st_abc[3] = {st_a,st_b,st_c};
//        //system("clear");
//        for(int i=0; i<3; i++)
//        {
//            printf("here /n");
//            switch(st_abc[i])
//            {
//                case 0:
//                    printf("[ ][ ][ ]\n");
//                    break;
//                case 1:
//                    printf("[0][0][0]\n");
//                    break;
//                case 2:
//                    printf("[ ][0][0]\n");
//                    break;
//                case 3:
//                    printf("[0][0][ ]\n");
//                    break;
//                case 4:
//                    printf("[ ][ ][0]\n");
//                    break;
//                case 5:
//                    printf("[ ][0][ ]\n");
//                    break;
//                case 6:
//                    printf("[0][ ][ ]\n");
//                    break;
//                case 7:
//                    printf("[X][X][X]\n");
//                    break;
//            }
//
//        }
//
//        /*---ob r---*/
//        Avoidance_Motor_r_Control(st_a,st_b,st_c,Last_Car_VL,Last_Car_VR,&main_d1,&main_d2,&direction);
//
//        printf("d1 = %f\td2 = %f\tDIR=%c\n",main_d1,main_d2,direction);
//
//        /*---Motor speed---*/
//        Avoidance_speed_Control(direction,main_d1,main_d2,&Car_VL,&Car_VR,&rlime);
//
//        //printf("VL: %f\tVR: %f\n",Car_VL,Car_VR);
//
//
////        fprintf(ob_VL,"%d\t%f\n",j,Car_VL);
////        fprintf(ob_VR,"%d\t%f\n",j,Car_VR);
////        fprintf(ob_rlime,"%d\t%f\n",j,rlime);
//
//        j=j+1;
//
//        usleep(300000);
//
//        if(direction == NULL && (Last_Car_VL!=Car_VL) && (Last_Car_VR!=Car_VR))
//        {
//             bodyJOGvel(Car_VL,Car_VR);
//             usleep(5000);
//             bodyact("fwd");
//             usleep(5000);
//        }
//        else
//        {
//
//            if(Last_Car_VL!=Car_VL)
//            {
//                bodyJOGvel_select(1,Car_VL);
//            }
//
//            if(Last_Car_VR!=Car_VR)
//            {
//                bodyJOGvel_select(2,Car_VR);
//            }
//
//
//
//            if(Car_VL==0 && (Last_Car_VL!=Car_VL))
//            {
//                Left_Tracked(0);
//                usleep(2000);
//            }
//            else if(Last_Car_VL == 0 && Car_VL != 0)
//            {
//                Left_Tracked(Car_VL);
//                usleep(2000);
//            }
//            else if( Last_Car_VL*Car_VL < 0 )
//            {
//                Left_Tracked(Car_VL);
//                usleep(2000);
//            }
//
//            if(Car_VR==0 && (Last_Car_VR!=Car_VR))
//            {
//                Right_Tracked(0);
//                usleep(2000);
//            }
//            else if(Last_Car_VR == 0 && Car_VR != 0)
//            {
//                Right_Tracked(Car_VR);
//                usleep(2000);
//            }
//            else if( Last_Car_VR*Car_VR < 0 )
//            {
//                Right_Tracked(Car_VR);
//                usleep(2000);
//            }
//        }
//
//
//        Last_Car_VL = Car_VL;
//        Last_Car_VR = Car_VR;
//
//        legJOGvel(1,1);
//        usleep(10000);
//
////        fclose(ob_VL);
////        fclose(ob_VR);
////        fclose(ob_rlime);
//
//    /*---if you ob want to stop 01---*/
//
//        int mid_depth=depthMD(137,15);
//
//
//
//        if(mid_depth>=1600)
//        {
//            cnt_break++;
//            last_depth=mid_depth;
//
//            if(last_depth>1600&&cnt_break>3)
//            {
//                bodyact("stop");
//                break;
//            }
//
//        }
//        else
//        {
//            cnt_break=0;
//        }
//        printf("\nmid_depth = %d , cnt_break = %d \n",mid_depth,cnt_break);
//
//
//        ob_time++;
//        printf("ob_time = %d \n",ob_time);
//
//    }
//
////---Obstacle Avoidance---
//
////---if you ob want to stop 02---
////    bodyact("stop");
////    usleep(50000);
////    bodyact("stop");
////    usleep(20000);
//
////---For r test---
////    double r=0;
////
////    legJOGvel(1,1);
////    usleep(10000);
////
////    //bodyact("fwd");
////    //usleep(2000);
////
////    Avoidance_MotorControl(r,&Car_VL,&Car_VR);
////
////    Left_Tracked(Car_VL);
////    Right_Tracked(Car_VR);
////
////
////    printf("Car_VL=%f\tCar_VR=%f\t\n",Car_VL,Car_VR);
////
////    //bodyJOGvel(Car_VL,Car_VR);
////    usleep(100000);
//
//    OpenNI_close();
///12345


/*======Mission :4F to 3F &continuos=======*/
//    OpenNI_initialize();
//    mode_5();
//
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n");
//        return 0;
//    }
//    mode_7(); //act_4f, in side
//
//
//    mode_9(5);  //Continuous Down stairs (4F to 3F)
//////===========================
//
//    mode_5();
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n");
//        return 0;
//    }
//    mode_7(); //act_4f, in side
/*======END Mission======*/


/*---Stair Climbing---*/

/*======Mission : 4F to 5F & Wall-Following======*/

//    OpenNI_initialize();
//    mode_5();
//
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n");
//
//
//        return 0;
//    }
//    mode_7(); //act_4f, in side

///*---Step.1 Down Stair to 4F---*/
    //mode_9(3);  //Continuous Down stairs (5F to 4F)
////===========================
      //mode_52();
      //mode_6();

//    mode_5();
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n");
//        return 0;
//    }
//    mode_7(); //act_4f, in side
/*======END Mission======*/

///* ---Step.2 4F Action---
//    action_4f();
//
///*---Step.3 Up Stair to 4F-1 ---*/
//    mode_1();
//    mode_21();
//    mode_3();
//    mode_4();

///*---Step.4 Act to 4F-2 ---*/
//    mode_9(2);
//
///*---Step.5 Up Stair to 5F ---*/
//    mode_21();
//    mode_3();
//    mode_4();
//
///*---Step.6 5F Action ---*/
//    action_5f();



/*=================01===================*/

/*--- Mission.01 : Climbing stairs---*/

    mode_1();    //do my thing don`t write this
    mode_21();
    mode_3();
    mode_4();
 /*------for demo here----*/
//
//
// /*----for operation out door----*/
//
////////    mode_021();
////////    mode_03();
////////    mode_04();
//
//
////---Mission.01 : Down Stairs---
////===========================
//    mode_9(1); //turn 180
/*===========================*/
//
//    mode_5();
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n");
//        return 0;
//    }
//    mode_7(); //act_4f, in side


///*=================01===================*/  //////////////////////////1 2016/08/24
//
///*--- Mission.01 : Climbing stairs 5F-6F-5F ---*/
////
//        XtionMotor_MR(100,0);
//
//        //mode_1();    //do my thing don`t write this
//        mode_21();
//        mode_3();
//        mode_4();
// /*------for demo here----*/
//
// /*----for operation out door----*/
////
////    mode_021();
////    mode_03();
////    mode_04();
//
//
//
////---Mission.01 : Down Stairs---
////===========================
//    mode_9(1); //turn 180
/////*===========================*/
////
//
//    mode_5();
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n  ");
//        return 0;
//    }
//    mode_7(); //act_4f, in side

///*=================01===================*/  //////////////////////////1 ~2016/08/24

  ///*=================01===================*/  //////////////////////////2
//
////
//////    //mode_5();
////  XtionMotor(550,0); //Put in mode 9
////    usleep(50000);
////
////    if(mode_6() < 0)  //Check Sensor Open
////    {
////        printf("Mode6 End.\n");
////        return 0;
////    }
////    mode_7(); //act_4f, in side
////





/*=================02===================*/

/*---Mission.02 : Continuous "Up" Stairs---*/
/*===========================*/
//      mode_9(2); //Continuous Up(4F to 5F)
///*===========================*/
//      mode_21();
//      mode_3();
//      mode_4();

/*---Mission.02 : Continuous "Down" Stairs---*/
/*===========================*/
//    mode_9(3);  //Continuous Down stairs (5F to 4F)
/*===========================*/
//    mode_5();
//    if(mode_6() < 0)  //Check Sensor Open
//    {
//        printf("Mode6 End.\n");
//        return 0;
//    }
//    mode_7(); //act_4f, in side




/*======Other Not use but need======*/
/*---Up Stairs Function 1---*/
//    mode_1();
//    int state;
//    do{
//        state = mode_21();
//
//        if(state==1) exceptionLeft();
//        else if(state==2) exceptionRight();
//    }while(state!=0);



/*======Program End and Shut Down All Setting======*/

	/*---Close OpenNI (Xtion)---*/
    OpenNI_close();
	/*---Close Motor USB Port---*/
	Motor_close();

	printf("Thanks for your attention!\n");
	return 0;

}
