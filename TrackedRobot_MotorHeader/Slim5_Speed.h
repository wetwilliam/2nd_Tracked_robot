/*---Set Motor Velocity---*/

//JOG Speed
void bodyJOGvel(int v1,int v2);	//Set T1,T2 JOG Speed (rang:0~4000)
void legJOGvel(int v1,int v2);	//Set T0,T3 JOG Speed (rang:0~4000)


void bodyJOGvel_select(int motor_number,int motor_speed);   //Choose T1 or T2 to control speed.
void bodyJOGvel_select(int motor_number,double motor_speed);

//MA Speed
void bodyMAvel(int v1,int v2);	//Set T1,T2 MA Speed (rang:0~4000)
void legMAvel(int v1,int v2);	//Set T0,T3 MA Speed (rang:0~4000)

//Robot Acceleration Set
void bodyva(int v1, int v2);	//Set T1,T2 Acceleration	(rang:0~1000)
void legva(int v1, int v2);		//Set T0,T3 Acceleration	(rang:0~1000)


void bodyJOGvel_select(int motor_number,int motor_speed)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T%dPN14=%d\r\n",motor_number,motor_speed);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);
}

void bodyJOGvel_select(int motor_number,double motor_speed)
{
     if(motor_speed==0)
    {
        return ;
    }

    motor_speed = abs(motor_speed);

    if( ((int)(motor_speed * 10) % 10) >= 5)
        motor_speed = abs((int)(motor_speed + 1));
    else
        motor_speed = (int)(motor_speed);


    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T%dPN14=%d\r\n",motor_number,(int)(motor_speed));
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);


}

void bodyJOGvel(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T1PN14=%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T2PN14=%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

void legJOGvel(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"PN14=%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T3PN14=%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

void bodyMAvel(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T1PN10=%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T2PN10=%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

void legMAvel(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"PN10=%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T3PN10=%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

void bodyva(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T1PN11=%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T2PN11=%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

void legva(int v1, int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"PN11=%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(50000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T3PN11=%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

