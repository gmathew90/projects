/*Author :    GEORGE MATHEW,ARCHANA NAIR,LEAH ABRAHAM NALONNIL

Institute :Federal Institute of Science And Technology,Kerala 

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include<opencv/cv.h>
#include <opencv/highgui.h>
#include<math.h>
#include<iostream>
#include <stdio.h>
IplImage* out;
IplImage* src;
IplImage* buff;
IplImage* dst;
CvSeq* lines=0;
CvMemStorage* storage=cvCreateMemStorage(0);
float arr[1000][10],intr[1000][7];
void detect();
void load();
void window();
void calc(int,int,int,int,int);
void display(int,int);
void linedisplay(int,int);
void intersect();
void extension();
void araydisply();
int dist(int,int);
int check(int);
void crction();
void arayy();
int total=0,ptl=0,buf=0,aray[1000][1000];
int main()
{
  arayy();
  load();
  detect();
  crction();
  int i=1,j=total;
  extension();
  linedisplay(i,j);
  //display(i,j);
  //intersect();
 // araydisply();
  window();
  cvWaitKey(0);
}

void detect()
{
  cvCanny(src,dst,50,150,3);
  lines=cvHoughLines2(dst,storage,CV_HOUGH_PROBABILISTIC,1,CV_PI/180,80,30,10);
  total=lines->total;
  for(int a,b,c,d,i=0;i<total;i++)
    {
      CvPoint* line=(CvPoint*)cvGetSeqElem(lines,i);
      a=line[0].x;
      b=line[0].y;
      c=line[1].x;
      d=line[1].y;
      calc(a,b,c,d,i);
    }
 
}

void crction()
{
  float cmp=0;
  int flag=0,d,ds;
  int b,c,di,v,u,s11,s12,s21,s22,e11,e12,e21,e22;
  for(int i=0;i<total;i++)
    {
       for(int j=i+1;j<total;j++)
	{
	  flag=0;
	  cmp=arr[i][7]-arr[j][7];
	  if(cmp<0)
	    {
	      cmp=cmp*-1;
	    }
	  if((arr[i][4]>=0)&&(arr[j][4]>=0))
	    {
	      flag=1;
	    }
	  if((arr[i][4]<0)&&(arr[j][4]<0))
	    {
	      flag=1;
	    }
	  if((cmp<2)&&(flag==1)&&(arr[i][8]==0)&&(arr[j][8]==0))
	    {
	      di=dist(i,j);
	      if((di<10))
		{
		  if(arr[i][6]>arr[j][6])
		    {
		      b=j;
		    }
		  else
		    {
		      b=i;
		    }
		  arr[b][8]=1;
		  buf++;
	       
		}
	    }
	}
    }
}




void load()
{
  src=cvLoadImage("68.jpeg",0);
  buff=cvLoadImage("68.jpeg",3);
  out=cvLoadImage("68.jpeg",3);
  dst=cvCreateImage(cvGetSize(src),8,0);
}


void calc(int x1,int y1,int x2,int y2,int var)
{
  float dy,dx;
  float c,m,ang,dist;
  dx=x2-x1;
  dy=y2-y1;
  m=dy/dx;
  ang=atan(m)*180/3.14;
  if(ang<0)
    {
      ang=ang*-1;
    }
  c=y1-(m*x1);
  dist=sqrt((dx*dx)+(dy*dy));
  arr[var][0]=x1;
  arr[var][1]=y1;
  arr[var][2]=x2;
  arr[var][3]=y2;
  arr[var][4]=m;
  arr[var][5]=c;
  arr[var][6]=dist;
  arr[var][7]=ang;
    arr[var][8]=0;
  arr[var][9]=0;
  // std::cout<<var<<"\n";
  for(int i=0;i<8;i++)
    {
      // std::cout<<arr[var][i]<<" ";
    }
}






void display(int a,int b)
{
  for(int i=(a-1);i<b;i++)
    {
      std::cout<<"\n";
      std::cout<<"points : " <<intr[i][2]<<" "<<intr[i][3]<<"\n ";
      int li1=intr[i][0];
      int li2=intr[i][1];
      if(arr[i][8]==0);
      {
	std::cout<<"line "<<li1<<": "<<arr[li1][0]<<" "<<arr[li1][1]<<" "<<arr[li1][2]<<" "<<arr[li1][3]<<" "<<arr[li1][4]<<" "<<arr[li1][7]<<"\n";
	std::cout<<"line "<<li2<<": "<<arr[li2][0]<<" "<<arr[li2][1]<<" "<<arr[li2][2]<<" "<<arr[li2][3]<<" "<<arr[li2][4]<<" "<<arr[li2][7]<<"\n";
      }
    }
}


void linedisplay(int a ,int b)
{
 char c,h[4000],s='"',str[40]="<dia:point val=";
  int i=0,r;
  FILE *f1;
  FILE *f2;
FILE *f3,*f4,*f5;
  f1=fopen("line1.txt","r");
  while(!(feof(f1)))
    {
      c=fgetc(f1);
      h[i++]=c;
    }
  printf("%d \n",i);
  h[i]='\0';
  //printf("%s",a);
  fclose(f1);
 f2=fopen("lines1.dia","w");
  fwrite(&h,(strlen(h)-1),1,f2);  
for(int i=(a-1);i<b;i++)
 {
      CvPoint p1,p2;
      p1.x=arr[i][0];
      p1.y=arr[i][1];
      p2.x=arr[i][2];
      p2.y=arr[i][3];
      if(arr[i][8]==0)
      	{
	  cvLine(out,p1,p2,CV_RGB(255,0,0),1,8);
	  f4=fopen("line2.txt","r");
	r=0;
while((!feof(f4)))
{
c=fgetc(f4);
h[r++]=c;
}
h[r]='\0';
fclose(f4);
fprintf(f2,"\n");
fwrite(&h,(strlen(h)-1),1,f2);
fprintf(f2,"%s",str);
fprintf(f2,"%c",s);
  fprintf(f2,"%f,%f",(arr[i][0])/20,(arr[i][1])/20);
fprintf(f2,"%c/>",s);
fprintf(f2,"\n");
fprintf(f2,"%s",str);
fprintf(f2,"%c",s);
fprintf(f2,"%f,%f",(arr[i][2])/20,(arr[i][3])/20);
fprintf(f2,"%c/>",s);
f3=fopen("line3.txt","r");
fprintf(f2,"\n");
r=0;
while(!(feof(f3)))
{
c=fgetc(f3);
h[r++]=c;
}
h[r]='\0';
fclose(f3);
fwrite(&h,(strlen(h)-1),1,f2);
	}
    }
f5=fopen("line4.txt","r");
r=0;
while((!feof(f5)))
{
c=fgetc(f5);
h[r++]=c;
}
h[r]='\0';
fclose(f5);
fwrite(&h,(strlen(h)-1),1,f2);
  fclose(f2);
}

int check(int a)
{
  int flg=0,x,y;
  x=intr[ptl][2];
  y=intr[ptl][3];
  if(arr[a][4]>0)
    {
      if((x>=arr[a][0])&&(y>=arr[a][1])&&(x<=arr[a][2])&&(y<=arr[a][3]))
	{
	  flg=1;
	}
    }
  else
    {
      if((x>=arr[a][0])&&(y<=arr[a][1])&&(x<=arr[a][2])&&(y>=arr[a][3]))
	{
	  flg=1;
	}
    }
 
  return(flg);
}





void window()
{
  cvNamedWindow("source",1);
  cvShowImage("source",dst);
  cvNamedWindow("output",1);
  cvShowImage("output",out);
}







void arayy()
{
  for(int i=0;i<total;i++)
    {
      for(int j=0;j<total;j++)
	{
	  aray[i][j]=0;
	}
    }
}


void extension()
{
   for(int i=0;i<total;i++)
    {
      if(arr[i][8]==0)
	{
	  if(arr[i][0]!=arr[i][2])
	  {
	    int t=arr[i][0]-arr[i][2];
	    int p=sqrt(t*t);
	    if (p<2)
	      {
	      }
	    else
	      {
		arr[i][0]=(arr[i][0])-15;
		arr[i][1]=(((arr[i][4])*(arr[i][0]))+(arr[i][5]));
		arr[i][2]=(arr[i][2])+15;
		arr[i][3]=(((arr[i][4])*(arr[i][2]))+(arr[i][5]));
	      
	      }
	  }
	else
	  {
	     arr[i][1]=arr[i][1]+15;
	     arr[i][3]=arr[i][3]-15;
	  }
	}
	}
}

int dist(int a,int b)
{
  int d;
  if(arr[a][0]!=arr[a][2])
    {
      int m=arr[a][4];
      int c1=arr[a][5];
      int c2=arr[b][5];
      d=sqrt(((c2-c1)*(c2-c1))/(1+(m*m)));
    }
  else
    {
      int di=arr[a][0]-arr[b][0];
      if(di>0)
	d=di;
      else
	d=-di;
    }
    return (d);
}


