/*---Motor Move---*/


bool bodyact(char *ac1);	//T1,T2 Move
bool legact(char *ac1,char *ac2);	//T0,T3 Move

bool Left_Tracked(double motor_speed);
bool Right_Tracked(double motor_speed);

bool bodyact(char *ac1)
{
    int wordsWritten=-1;

RE_bodyact:

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));

    if(ac1=="fwd")
    {

        sprintf(Writtenbuf,"\r\nT1JGF\r\n");   //1
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);

        sprintf(Writtenbuf,"\r\nT2JGF\r\n");   //2
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

//        sprintf(Writtenbuf,"T1JGF\r\n");
//        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
//
//        tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
//        usleep(10000);
//
//        memset(Writtenbuf, '\0', sizeof(Writtenbuf));
//        sprintf(Writtenbuf,"T2JGF\r\n");
//        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }

    else if(ac1=="back")
    {
        sprintf(Writtenbuf,"\r\nT1JGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);

        sprintf(Writtenbuf,"\r\nT2JGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }

    else if(ac1=="left")
    {
        sprintf(Writtenbuf,"\r\nT1JGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);

        sprintf(Writtenbuf,"\r\nT2JGF\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }

    else if(ac1=="right")
    {
        sprintf(Writtenbuf,"\r\nT1JGF\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);

        sprintf(Writtenbuf,"\r\nT2JGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }

    else if(ac1=="stop")
    {
        sprintf(Writtenbuf,"\r\nT1JG0\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);

        sprintf(Writtenbuf,"\r\nT2JG0\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

//        write(fd_Slim5,"STOP\r\n",6);
//        write(fd_Slim5,"T1STOP\r\n",8);
//        write(fd_Slim5,"T2STOP\r\n",8);
//        write(fd_Slim5,"T3STOP\r\n",8);
    }
    else
        return FALSE;


    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(5000);
    //usleep(200000);


    if(wordsWritten <= 0)
        goto RE_bodyact;

    return TRUE;

}

bool legact(char *ac1,char *ac2)
{
    int wordsWritten = -1;

RE_legact:

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));

    if(ac1=="fwd")
    {
        sprintf(Writtenbuf,"\r\nJGF\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }
    else if(ac1=="rev")
    {
        sprintf(Writtenbuf,"\r\nJGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }
    else if(ac2=="fwd")
    {
        sprintf(Writtenbuf,"\r\nT3JGF\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }
    else if(ac2=="rev")
    {
        sprintf(Writtenbuf,"\r\nT3JGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }
    else if(ac1=="stop" && ac2=="stop")
    {
        sprintf(Writtenbuf,"\r\nJG0\r\nT3JG0\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    }
    else
        return FALSE;

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    //usleep(1000);
    usleep(200000);

    if(wordsWritten <= 0)
        goto RE_legact;

    return TRUE;
}


bool Left_Tracked(double motor_speed)
{
    int wordsWritten=-1;

//RE_Left_Tracked1:
//
//
//    if(Speed != 0)
//    {
//        memset(Writtenbuf, '\0', sizeof(Writtenbuf));
//        sprintf(Writtenbuf,"T1PN14=%d\r\n",V_speed);
//        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
//        usleep(1000);
//        tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
//        usleep(1000);
//        if(wordsWritten <= 0)
//            goto RE_Left_Tracked1;
//    }


RE_Left_Tracked2:

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));

   if(motor_speed > 0)
   {
        sprintf(Writtenbuf,"\r\nT1JGF\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);
   }
   else if(motor_speed < 0)
   {
        sprintf(Writtenbuf,"\r\nT1JGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);
   }
   else if(motor_speed == 0)
   {
        sprintf(Writtenbuf,"\r\nT1STOP\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);
   }

   else
        return FALSE;


    if(wordsWritten <= 0)
        goto RE_Left_Tracked2;

    return TRUE;
}

bool Right_Tracked(double motor_speed)
{
    int wordsWritten=-1;

//RE_Right_Tracked1:
//
//
//    if(Speed != 0)
//    {
//        memset(Writtenbuf, '\0', sizeof(Writtenbuf));
//        sprintf(Writtenbuf,"T2PN14=%d\r\n",V_speed);
//        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
//        usleep(1000);
//        tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
//        usleep(1000);
//        if(wordsWritten <= 0)
//            goto RE_Right_Tracked1;
//    }


RE_Right_Tracked2:

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));

   if(motor_speed > 0)
   {
        sprintf(Writtenbuf,"\r\nT2JGF\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);
   }
   else if(motor_speed < 0)
   {
        sprintf(Writtenbuf,"\r\nT2JGR\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);
   }
   else if(motor_speed == 0)
   {
        sprintf(Writtenbuf,"\r\nT2STOP\r\n");
        wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
        usleep(1000);
        tcflush(fd_Slim5, TCIFLUSH);
        usleep(1000);
   }

   else
        return FALSE;


    if(wordsWritten <= 0)
        goto RE_Right_Tracked2;

    return TRUE;
}
