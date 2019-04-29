/*---Tracked Robot Manual Control---*/

int TrackRobot_ManualControl();


int vv1=1000,vv2=1000,y=0;
int wd1=0,wd2=0,wd3=0;


int TrackRobot_ManualControl()
{
    printf("Manual control \n");

    while(1)
    {
        y=getch();

        if(y==32){
            bodyact("stop");
            legact("stop","stop");
            //usleep(50000);
        }
        else if(y==65){
            bodyact("fwd");
            //usleep(50000);
        }
        else if(y==66){
            bodyact("back");
            //usleep(50000);
        }
        else if(y==68){
            bodyact("left");
            //usleep(50000);
        }
        else if(y==67){
            bodyact("right");
            //usleep(50000);
        }
        else if(y==97||y==65)//A
            //legma(0,5000);
            legact("","fwd");
        else if(y==122||y==90)//Z
            //legma(0,-5000);
            legact("","rev");
        else if(y==83||y==115)//S
            //legma(5000,0);
            legact("rev","");
        else if(y==120||y==88)//X
            //legma(-5000,0);
            legact("fwd","");
        else if(y==114||y==82)//R reset speed
        {
            bodyJOGvel(350,350);
            legJOGvel(100,100);
        }
        else if(y==102||y==70)//F fast speed
        {
            bodyJOGvel(1000,1000);
            legJOGvel(300,300);
        }
        else if(y==85||y==117)//U add speed
        {
            if(vv1<3000)
                vv1+=100;
            if(vv1<3000)
                vv2+=100;
            bodyJOGvel(vv1,vv2);
        }
        else if(y==101||y==69)//E end for break
        {
            bodyact("stop");
            legact("stop","stop");
            break;
        }
        else if(y==106)//E end for break
        {
            legma(-26000,-27000); //climb stairs legs initial
        }


		/*---For data get---*/
		//Data_test_Climb();
		//Data_test_mode9();
    }

	return 1;
}



