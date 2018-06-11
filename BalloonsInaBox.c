#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

# define PI 3.14159265358979323846
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
int npoints;

double cal_vol(double r[npoints])
{
    double vol = 0.0;
    int i;
    for(i=0;i<npoints;i++)
        vol = vol + (4.0/3.0)*PI*pow(r[i],3);

    return round(vol);
}

int distance_balloon(int balloon[npoints][3],int index1,int index2)
{

    int dist;
    dist = pow(balloon[index1][0]-balloon[index2][0],2)+pow(balloon[index1][1]-balloon[index2][1],2)+pow(balloon[index1][2]-balloon[index2][2],2);
    return dist;
}

int distace_end(int balloon[npoints][3],int box[2][3],int index)
{
    int t_rad[3];
    int k;
    for(k=0;k<3;k++)
    {
        t_rad[k] = MIN(abs(balloon[index][k]-box[0][k]),abs(balloon[index][k]-box[1][k]));
    }
    return MIN(MIN(t_rad[0],t_rad[1]),t_rad[2]);

}

int fact(int num)
{
    if(num == 1)
        return 1;
    else
        return num*fact(num-1);
}

int calculatevol(int balloon[npoints][3],int box[2][3],int flag[npoints],int vol)
{
    int i,j,perm=1;
    int myint[npoints];
    double r[npoints],d_centre,auxV,auxx,volballoon=0.0;
    for(i=0;i<npoints;i++)
        myint[i] = i;
     perm = fact(npoints);

     for(i=0;i<npoints;i++)
        printf("%d ",myint[i]);
        printf("\n");
        printf("%d\n", perm);

     do{
         memset(r, 0.0, sizeof(double) * npoints);
         for(i=0;i<npoints;i++)
         {
             if(flag[myint[i]]!=1)
             {
                 r[myint[i]] = distace_end(balloon,box,myint[i]);
                 printf("Radius of %d : %f\n",myint[i],r[myint[i]]);

                 for(j=0;j<i;j++)
                 {
                     d_centre = distance_balloon(balloon,myint[i],myint[j]);
                     printf("distance bw centres : %f and %f\n",d_centre ,pow(r[myint[i]]+r[myint[j]],2));

                     if(d_centre < pow(r[myint[i]]+r[myint[j]],2))
                     {
                         auxx = sqrt((d_centre)-r[myint[j]]);

                         if(auxx<0){
                             r[myint[i]] = 0;
                         }
                         else{
                             r[myint[i]] = MIN(distace_end(balloon,box,myint[i]),auxx);
                         }
                     }
                 }
             }
         }
         printf("radiuses : ");
         for(i=0;i<2;i++)
            printf("%f ",r[i]);
            printf("\n");
         auxV = cal_vol(r);
         if(auxV>volballoon)
            volballoon = auxV;



     }while(0);


     printf("total balloon space %f\n",volballoon );

     return volballoon;
}

int main()
{
    int i,j,temp,vol,fsum=0,bval=1;
    int bvol = 0;
    int box[2][3];
    scanf("%d",&npoints);
    int balloon[npoints][3];
    int flag[npoints];
    memset(flag,0,npoints*sizeof(flag[0]));

    while(npoints != 0)
    {

        for(i=0;i<2;i++)
            for(j=0;j<3;j++)
            {
                scanf("%d",&box[i][j]);
            }

        for(i=0;i<npoints;i++)
            for(j=0;j<3;j++)
            {
                scanf("%d",&temp);
                if (temp>MAX(box[0][j],box[1][j])||temp<MIN(box[0][j],box[1][j])||temp == box[0][j]||temp == box[1][j])
                    flag[i] = 1;
                balloon[i][j] = temp;
            }

        for(i=0;i<2;i++){
            for(j=0;j<3;j++)
            {
                printf("%d ",box[i][j]);
            }
            printf("\n");
        }
        for(i=0;i<npoints;i++){
            for(j=0;j<3;j++)
            {
                printf("%d ",balloon[i][j]);
            }
            printf("\n");
        }
        for(i=0;i<npoints;i++){
            printf("%d ",flag[i]);
            fsum = fsum+flag[i];
        }
        printf("\n");




        vol = (abs(box[0][0]- box[1][0]))*(abs(box[0][1]- box[1][1]))*(abs(box[0][2]-box[1][2]));
        printf("Volume : %d\n",vol );

        if(fsum == npoints)
            printf("Box %d: %d\n",bval,vol );
        else
        {
            bvol = calculatevol(balloon,box,flag,vol);
            printf("Box %d: %d\n",bval, vol-bvol);
        }

        bval++;

        scanf("%d",&npoints);

    }


    return 0;
}
