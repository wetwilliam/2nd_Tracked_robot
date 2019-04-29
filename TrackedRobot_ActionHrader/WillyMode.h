void mode_WillyNear(float mmvalue);

void mode_WillyNear(float mmvalue)
{
    if( mmvalue <=0.06  &&   -0.06 <= mmvalue)
    {
            bodyJOGvel(150,150);
            // bodyJOGvel(50,50);//indoor

            bodyact("fwd");
            usleep(50000);
    }  //need go straight

    if(mmvalue>0.06)  //need turn left
    {
        if(mmvalue<=0.267)  //0.267= 15 degree //if degree under 15 go straight // ps.10 degree=0.17
         {
            bodyJOGvel(150,150);
            bodyact("left");
            usleep(3000000);
           // usleep(3000000+(mmvalue)*300000);
            bodyact("stop");
            usleep(50000);  //here may let the count time more slow in mode_1 chiwei use 50000
         }
         else if (mmvalue>0.267)
         {
            bodyJOGvel(150,150);
            bodyact("left");
            usleep(3000000);  //here may let the count time more slow in mode_1 chiwei use 50000  //if error can change here
            bodyact("stop");
            usleep(50000);
         }
    }

    else if (mmvalue< -0.06)  //need turn right  5degree
    {
        if(abs(mmvalue)<=0.267)  //0.267= 15 degree //if degree under 15 go straight // ps.10 degree=0.17
         {
            bodyJOGvel(150,150);
            bodyact("right");
            usleep(3000000);
            bodyact("stop");
            usleep(50000); //here may let the count time more slow in mode_1 chiwei use 50000
         }
         else if (abs(mmvalue)>0.267)
         {
              bodyJOGvel(150,150);
              bodyact("right");
             usleep(3000000);
              bodyact("stop");
              usleep(50000);  //here may let the count time more slow in mode_1 chiwei use 50000
         }
    }


}
