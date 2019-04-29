/*---WallFollowing---*/

void WallFollowing_LeftWall();	/*---Wall on the left hand side---*/
void WallFollowing_RightWall();	/*---Wall on the right hand side---*/

void WallFollowing_LeftWall()
{
    /*---Time---*/
//    time_t t1 = time(NULL);

    /*------*/
    int wv1=1000,wv2=1000;
    int wd1=0,wd2=0,wd3=0;

    bodyJOGvel(1000,1000);
	usleep(10000);
    legJOGvel(300,300);
	usleep(10000);


    //legMAvel(,)
    /*---Data Record - Open---*/
//    FILE *WFLXD=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/Recore Data/WFL_XtionDistance.txt","w");
//    FILE *WFLVL=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/Recore Data/WFL_VelLeft.txt","w");
//    FILE *WFLVR=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/Recore Data/WFL_VelRight.txt","w");

    XtionMotor(0,-500); //-:left , +:right
    sleep(2);

    bodyact("fwd");

	while(1)
	{

		streamDepth.readFrame( &frameDepth );
		wd3=depthMD(256,240);
        wd2=depthMD(384,240);
        wd1=depthMD(412,240);

        //printf("wd1=%d , wd2=%d ,wd3=%d \n",wd1,wd2,wd3);
//        fprintf(WFLXD,"%d\r%d\r%d\n",wd1,wd2,wd3);

		if((wd1>800&&wd1<2999)&&(wd2>835&&wd2<2999)&&(wd3>1000&&wd3<2999)) // right ++
		{
            if(wv2<2000)
            {

                if(wv1!=1000)
                {
                    bodyJOGvel_select(1,1000);
                }
                wv2+=30; //30
                bodyJOGvel_select(2,wv2);
                usleep(50000); //test(90000)

            }

//            fprintf(WFLVL,"%d\n",wv1);
//            fprintf(WFLVR,"%d\n",wv2);
		}
		else if(wd1<750&&wd2<790&&wd3<900)// left ++
		{
            if(wv1<2000)
            {

                if(wv2!=1000)
                {
                    bodyJOGvel_select(2,1000);
                }
                wv1+=30; //30
                bodyJOGvel_select(1,wv1);
                usleep(50000);
            }

//            fprintf(WFLVL,"%d\n",wv1);
//            fprintf(WFLVR,"%d\n",wv2);
		}
		else if(wd1>3001&&wd2>3001&&wd3>3001) //last "break" condition;
		{
            bodyact("stop");
            usleep(100000); //test(90000)
            printf("Wall Following(Left) Ending.\n");

        // ---> Work stairs (for 5F mission)
//            bodyact("fwd");
//            sleep(10);
//            bodyact("right");
//            usleep(3000000);
//            bodyact("stop");
//            XtionMotor(0,0); //motor 01
//            usleep(2000000);
            break;
		}
		else
		{
			if(wv1!=1000)
			{
                wv1=1000;
                bodyJOGvel_select(1,wv1);
			}
            if(wv2!=1000)
			{
                wv2=1000;
                bodyJOGvel_select(2,wv2);
			}

//			fprintf(WFLVL,"%d\n",wv1);
//            fprintf(WFLVR,"%d\n",wv2);
		}
	} //while end

	/*---Time end---*/
//    time_t t2 = time(NULL);
//    fprintf(WFLXD,"Wall Following Left Time = %d\n",t2-t1);

    /*---Data Record - Close---*/
//    fclose(WFLXD);
//    fclose(WFLVL);
//    fclose(WFLVR);
}

void WallFollowing_RightWall()
{
    /*---Time---*/
//    time_t t1 = time(NULL);
    /*------*/
    int wv1=1000,wv2=1000;
    int wd1=0,wd2=0,wd3=0;
    int i=0;//For count

    /*---Data Record - Open---*/
//    FILE *WFRXD=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/Recore Data/WFR_XtionDistance.txt","w");
//    FILE *WFRVL=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/Recore Data/WFR_VelLeft.txt","w");
//    FILE *WFRVR=fopen("/home/ubuntu/CodeBlocks/TrackedRobot_Control/Recore Data/WFR_VelRight.txt","w");

    XtionMotor(0,500); //-:left , +:right
    usleep(1500000);

    bodyact("fwd");

	while(i<940)//35
	{
		streamDepth.readFrame( &frameDepth );
		wd3=depthMD(384,240);//256
        wd2=depthMD(256,240);//384
        wd1=depthMD(228,240);//412

        printf("WD1=%d\tWD2=%d\tWD3=%d \n",wd1,wd2,wd3);

//        fprintf(WFRXD,"%d\r%d\r%d\n",wd1,wd2,wd3);

		if((wd1>800&&wd1<2999)&&(wd2>835&&wd2<2999)&&(wd3>1000&&wd3<2999)) // left ++
		{
            if(wv1<2000)
            {
                if(wv2!=1000)
                {
                    bodyJOGvel_select(2,1000);
                }
                wv1+=30; //30
                bodyJOGvel_select(1,wv1);

                usleep(50000);
            }

//            fprintf(WFRVL,"%d\n",wv1);
//            fprintf(WFRVR,"%d\n",wv2);

		}
		else if(wd1<750&&wd2<790&&wd3<900)// right ++
		{
            if(wv2<2000)
            {
                if(wv1!=1000)
                {
                    bodyJOGvel_select(1,1000);
                }

                wv2+=30; //30
                bodyJOGvel_select(2,wv2);
                usleep(50000);
            }

//            fprintf(WFRVL,"%d\n",wv1);
//            fprintf(WFRVR,"%d\n",wv2);
		}
		else
		{
			if(wv1!=1000)
			{
                wv1=1000;
                bodyJOGvel_select(1,wv1);
			}

            if(wv2!=1000)
			{
                wv2=1000;
                bodyJOGvel_select(2,wv2);
			}

//            fprintf(WFRVL,"%d\n",wv1);
//            fprintf(WFRVR,"%d\n",wv2);
		}

		i++; //For count
        //printf("WF_R count i = %d \n",i);
	}//while end


	/*---Time end---*/
//    time_t t2 = time(NULL);
//    fprintf(WFRXD,"Wall Following Right Time = %d\n",t2-t1);

    /*---Data Record - Close---*/
//    fclose(WFRXD);
//    fclose(WFRVL);
//    fclose(WFRVR);
}
