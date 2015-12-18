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
float arr[1000][10],intr[1000][7],ds[1000][18],tri[1000][6],square[1000][6];
int total=0,ptl=0,buf=0,aray[1000][1000],in[1000][3],inr=0,fig=0,trin=0,scn=0;
void detect();
void load();
void window();
void calc(int,int,int,int,int);
void display(int,int);
void linedisplay(int,int);
void intersect();
int check(int);
void crction();
void arayy();
void extension();
void triangle();
void foursi();
int color(int,int,int,int,int);
int search(int,int);
int dist(int,int);
void araydisply();
void stac();
int angle(int,int);
void op();
void dia();
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
  intersect();
  araydisply();
  //  display(i,ptl);
  triangle();
  foursi();
  op();
  window();
  dia();
  for(int l=0;l<scn;l++)
    {std::cout<<"\n";
      for(int m=0;m<6;m++)
	{std::cout<<square[l][m]<<" ";
	}
    }
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
  src=cvLoadImage("Diagram1.jpeg",0);
  buff=cvLoadImage("Diagram1.jpeg",3);
  out=cvLoadImage("Diagram1.jpeg",3);
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
  for(int i=(a-1);i<b;i++)
    {
      CvPoint p1,p2;
      p1.x=arr[i][0];
      p1.y=arr[i][1];
      p2.x=arr[i][2];
      p2.y=arr[i][3];
      if(arr[i][8]==0)
      	{
	  std::cout<<"\n";
	  for(int k=0;k<4;k++)
	    {
	      std::cout<<arr[i][k]<<" ";
	    }
	  cvLine(out,p1,p2,CV_RGB(255,0,0),1,8);
	}
    }
}




void intersect()
{
  for(int i=0;i<(total-1);i++)
    {
      for(int j=(i+1);j<total;j++)
	{
	  if((arr[i][8]==0)&&(arr[j][8]==0))
	    {
	      intr[ptl][0]=i;
	      intr[ptl][1]=j;
	      if((arr[i][0]!=arr[i][2])&&(arr[j][0]!=arr[j][2]))
		{
		  intr[ptl][2]=((arr[j][5]-arr[i][5])/(arr[i][4]-arr[j][4]));
		  intr[ptl][3]=(((arr[i][4])*(intr[ptl][2]))+arr[i][5]);
		}
	      else
		{
		  if(arr[i][0]==arr[i][2])
		    {
		      intr[ptl][2]=arr[i][0];
		      intr[ptl][3]=(((arr[j][4])*(intr[ptl][2]))+arr[j][5]);
		    }
		  else
		    {
		      intr[ptl][2]=arr[j][0];
		      intr[ptl][3]=(((arr[i][4])*(intr[ptl][2]))+arr[i][5]);
		    }
		}
	      intr[ptl][4]=check(i);
	      intr[ptl][5]=check(j);
	      intr[ptl][6]=0;
	      CvPoint p;
	      p.x=intr[ptl][2];
	      p.y=intr[ptl][3];
	      if((intr[ptl][4]==1)&&(intr[ptl][5]==1))
		{
		      intr[ptl][6]=1;
		      aray[i][j]=1;
		      std::cout<<" "<<i<<" "<<j<<"\n";
		      in[inr][0]=i;
		      in[inr][1]=j;
		      in[inr][2]=0;
		      inr++;
		      cvCircle(out,p,10,CV_RGB(0,0,255),4,8);
		      // std::cout<<"intersection"<<i<<" "<<j<<"\n";
		}
	      ptl++;
	    }
	}
    }
  //  std::cout<<ptl;
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







void triangle()
{
  int l,m,n,flag=0,flag1=0;
  for(int i=0;i<total;i++)
    {
      flag=0;
      for(int j=0;j<total;j++)
	{
	  if(aray[i][j]==1)
	    {/*
	      if(flag==0)
		{
		  l=j;
		  flag=1;
		}
	      else
		{
		  m=j;
		  flag1=1;
	     */
	      for(int h=j+1;h<total;h++)
		{
		  if(aray[i][h]==1)
		    {
		      l=j;
		      m=h;
		      flag1=1;
		    }
	
		  if(flag1==1)
		    {
		      flag1=0;
		      flag=0;
		      if((aray[l][m]==1))
			{
			  ds[fig][0]=3;
			  // std::cout<<i<<" "<<l<<" "<<m<<"\n";
			  int a=search(i,l);
			  int b=search(i,m);
			  int c=search(l,m);
			  ds[fig][2]=intr[a][2];
			  ds[fig][3]=intr[a][3];
			  ds[fig][4]=intr[b][2];
			  ds[fig][5]=intr[b][3];
			  ds[fig][6]=intr[c][2];
			  ds[fig][7]=intr[c][3];
			  // std::cout<<a<<" "<<b<<" "<<c<<"\n";
			  std::cout<<"TRIANGLE \n dimensions \n";
			  ds[fig][8]=color(a,b,0,255,0);
			  ds[fig][9]=color(b,c,0,255,0);
			  ds[fig][10]=color(a,c,0,255,0);
			  ds[fig][11]=angle(a,b);
			  ds[fig][12]=angle(b,c);
			  ds[fig][13]=angle(a,c);
			  fig++;
			}
		    }
		}
	    }
	}
      
    }
}







int color(int a,int b,int l,int m,int n)
{
  int dx,dy,dist;
  dx=intr[b][2]-intr[a][2];
  dy=intr[b][3]-intr[a][3];
  if(dx==0)
    {
      dist=sqrt(dy*dy);
    }
  else
    {
  dist=sqrt((dx*dx)+(dy*dy));
    }
  std::cout<<dist<<"\n";
  CvPoint p1,p2;
  p1.x=intr[a][2];
  p1.y=intr[a][3];
  p2.x=intr[b][2];
  p2.y=intr[b][3];
  cvLine(out,p1,p2,CV_RGB(l,m,n),3,8);
  return(dist);
}






int search(int a,int b)
{
  int c=0;
  for(int e=0;e<ptl;e++)
    {
      if((intr[e][0]==a)&&(intr[e][1]==b))
	{
	  c=e;
	}
    }
  for(int e=0;e<inr;e++)
    {
      if((in[e][0]==a)&&(in[e][1]==b))
	{
	  in[e][2]=1;
	}
    }
  return c;
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







void foursi()
{
  int a,b,c,d,j,k,l,flag=0,flag1=0,flag3=0;
  for(int i=0;i<total;i++)
    {
      flag=0;
      for(int n=0;n<total;n++)
	{
	  if(aray[i][n]==1)
	    {
	     
	      for(int h=n+1;h<total;h++)
		{
		 
		  if(aray[i][h]==1)
		    {
		     		     
		      flag1=1;
		      j=n;
		      k=h;
		      // std::cout<<i<<j<<k<<"\n";
		    }
		
		  if(flag1==1)
		    {
		      // std::cout<<"\n"<<i<<" "<<j<<" "<<k;
		      flag1=0;
		      flag=0;
		      for(int t=0;t<total;t++)
			{
			  if((aray[j][t]==1)&&(aray[k][t]==1))
			    {
			 
			      l=t;
			      a=search(i,j);
			      b=search(j,l);
			      c=search(k,l);
			      d=search(i,k);
			      std::cout<<"Square \n dimensions1 \n";
			      ds[fig][10]=color(a,b,0,0,255);
			      ds[fig][11]=color(c,b,0,0,255);
			      ds[fig][12]=color(c,d,0,0,255);
			      ds[fig][13]=color(a,d,0,0,255);
			      ds[fig][0]=4;
			      ds[fig][2]=intr[a][2];
			      ds[fig][3]=intr[a][3];
			      ds[fig][4]=intr[b][2];
			      ds[fig][5]=intr[b][3];
			      ds[fig][6]=intr[c][2];
			      ds[fig][7]=intr[c][3];
			      ds[fig][8]=intr[d][2];
			      ds[fig][9]=intr[d][3];
			      ds[fig][14]=angle(a,b);
			      ds[fig][15]=angle(c,b);
			      ds[fig][16]=angle(c,d);
			      ds[fig][17]=angle(a,d);
			      fig++;
			    }
		      
			  if((aray[j][t]==1)&&(aray[t][k]==1))
			    {
			      
			      l=t;
			      std::cout<<l<<"\n";
			      
			      a=search(i,j);
			      b=search(j,l);
			     
			      c=search(l,k);
			      d=search(i,k);
			      
			      std::cout<<i<<"Square \n dimensions2 \n";
			      ds[fig][10]=color(a,b,0,0,255);
			      ds[fig][11]=color(c,b,0,0,255);
			      ds[fig][12]=color(c,d,0,0,255);
			      ds[fig][13]=color(a,d,0,0,255);
			      ds[fig][0]=4;
			      ds[fig][2]=intr[a][2];
			      ds[fig][3]=intr[a][3];
			      ds[fig][4]=intr[b][2];
			      ds[fig][5]=intr[b][3];
			      ds[fig][6]=intr[c][2];
			      ds[fig][7]=intr[c][3];
			      ds[fig][8]=intr[d][2];
			      ds[fig][9]=intr[d][3];
			      ds[fig][14]=angle(a,b);
			      ds[fig][15]=angle(c,b);
			      ds[fig][16]=angle(c,d);
			      ds[fig][17]=angle(a,d);
			      fig++;
			    }
			        if((aray[t][j]==1)&&(aray[t][k]==1)&&(t>i))
				  {
				    l=t;
				    a=search(i,j);
				    b=search(l,j);
				    c=search(l,k);
				    d=search(i,k);
				    std::cout<<"Square \n dimensions3 \n ";
				    ds[fig][10]=color(a,b,0,0,255);
				    ds[fig][11]=color(c,b,0,0,255);
				    ds[fig][12]=color(c,d,0,0,255);
				    ds[fig][13]=color(a,d,0,0,255);
				    ds[fig][0]=4;
				    ds[fig][2]=intr[a][2];
				    ds[fig][3]=intr[a][3];
				    ds[fig][4]=intr[b][2];
				    ds[fig][5]=intr[b][3];
				    ds[fig][6]=intr[c][2];
				    ds[fig][7]=intr[c][3];
				    ds[fig][8]=intr[d][2];
				    ds[fig][9]=intr[d][3];
				    ds[fig][14]=angle(a,b);
				    ds[fig][15]=angle(c,b);
				    ds[fig][16]=angle(c,d);
				    ds[fig][17]=angle(a,d);
				    fig++;
				  }
			}
		    }	
		}
	    }
	}
    }
}






void araydisply()
{
  for(int i=0;i<total;i++)
    {
      std::cout<<"\n";
      for(int j=0;j<total;j++)
	{
	  std::cout<<aray[i][j];
	}
    }
}






int angle(int a,int b)
{
  float m;
  float dx=intr[b][2]-intr[a][2];
  float dy=intr[b][3]-intr[a][3];
  if(dx==0)
    {
      m=90;
    }
  else
    {
      m=atan(dy/dx)*180/3.14;
    }
  m=sqrt(m*m);
  return(m);
}




	  



void op()
{
  float y[6],z[8];
  for(int i=0;i<fig;i++)
    {
      if(ds[i][0]==3)
	{
	  // std::cout<<"\n";
	  if((ds[i][11]<ds[i][12])&&(ds[i][11]<ds[i][13]))
	    {
	      int dst=ds[i][2]-ds[i][6];
	      y[0]=ds[i][2];
	      y[1]=ds[i][3];
	      y[2]=ds[i][6]-dst;
	      y[3]=ds[i][3];
	      y[4]=ds[i][6];
	      y[5]=ds[i][7];
	      tri[trin][1]=y[0];
	      tri[trin][2]=y[1];
	      tri[trin][3]=y[2];
	      tri[trin][4]=y[3];
	      tri[trin][5]=sqrt((y[5]-y[1])*(y[5]-y[1]));
	      if(y[5]>y[1])
		{
		  tri[trin][0]=1;
		}
	      else
		{
		  tri[trin][0]=2;
		}
	      trin++;
	    }	    
	  if((ds[i][12]<ds[i][11])&&(ds[i][12]<ds[i][13]))
	    {
	      int dst=ds[i][2]-ds[i][4];
	      y[0]=ds[i][2];
	      y[1]=ds[i][3];
	      y[2]=ds[i][4];
	      y[3]=ds[i][5];
	      y[4]=ds[i][2]+dst;
	      y[5]=ds[i][5];
	      tri[trin][1]=y[2];
	      tri[trin][2]=y[3];
	      tri[trin][3]=y[4];
	      tri[trin][4]=y[5];
	      tri[trin][5]=sqrt((y[3]-y[1])*(y[3]-y[1]));
	      if(y[3]>y[1])
		tri[trin][0]=2;
	      else
		tri[trin][0]=1;
	      trin++;
	    }
	  if((ds[i][13]<ds[i][12])&&(ds[i][13]<ds[i][11]))
	    {
	      int dst=ds[i][4]-ds[i][2];
	      y[0]=ds[i][2];
	      y[1]=ds[i][3];
	      y[2]=ds[i][4];
	      y[3]=ds[i][5];
	      y[4]=ds[i][4]+dst;
	      y[5]=ds[i][3];
	      tri[trin][1]=y[0];
	      tri[trin][2]=y[1];
	      tri[trin][3]=y[4];
	      tri[trin][4]=y[5];
	      tri[trin][5]=sqrt((y[3]-y[1])*(y[3]-y[1]));
	      if(y[3]>y[1])
		tri[trin][0]=1;
	      else
		tri[trin][0]=2;
	      trin++;
	    }  
	  CvPoint p1,p2;
	      p1.x=y[0];
	      p1.y=y[1];
	      p2.x=y[2];
	      p2.y=y[3];
	      cvLine(out,p1,p2,CV_RGB(255,0,0),3,8);
	      p1.x=y[2];
	      p1.y=y[3];
	      p2.x=y[4];
	      p2.y=y[5];
	      cvLine(out,p1,p2,CV_RGB(255,0,0),3,8);
	      p1.x=y[0];
	      p1.y=y[1];
	      p2.x=y[4];
	      p2.y=y[5];
	      cvLine(out,p1,p2,CV_RGB(255,0,0),3,8);
	  for(int j=0;j<14;j++)
	    {
	      //  std::cout<<ds[i][j]<<" ";
	    }
	  
	}
    
      if(ds[i][0]==4)
	{
	  int flag=0;
	  std::cout<<"\n";
	  if(ds[i][14]==0)
	    {
	      int flag1=0;
	      flag=1;
	      if(ds[i][15]==90)
		{
		  flag1=1;
		  z[0]=ds[i][2];
		  z[1]=ds[i][3];
		  z[2]=ds[i][4];
		  z[3]=ds[i][5];
		  z[4]=ds[i][6];
		  z[5]=ds[i][7];
		  z[6]=z[0];
		  z[7]=z[5];
		  square[scn][0]=z[0];
		  square[scn][1]=z[1];
		  square[scn][2]=z[2];
		  square[scn][3]=z[3];
		  square[scn][4]=sqrt((z[1]-z[5])*(z[1]-z[5]));
		  square[scn][5]=1;
		}
	      if(ds[i][17]==90)
		{
		  flag1=1;
		  z[0]=ds[i][2];
		  z[1]=ds[i][3];
		  z[2]=ds[i][4];
		  z[3]=ds[i][5];
		  z[4]=ds[i][4];
		  z[5]=ds[i][9];
		  z[6]=ds[i][8];
		  z[7]=ds[i][9]; 
	       
		  square[scn][0]=z[0];
		  square[scn][1]=z[1];
		  square[scn][2]=z[2];
		  square[scn][3]=z[3];
		  square[scn][4]=sqrt((z[1]-z[7])*(z[1]-z[7]));
		  square[scn][5]=1;


		}
	      if(flag1==0)
		{
		  if(ds[i][11]>=ds[i][13])
		    {
		      z[0]=ds[i][2];
		      z[1]=ds[i][3];
		      z[2]=ds[i][4];
		      z[3]=ds[i][5];
		      z[4]=ds[i][6];
		      z[5]=ds[i][7];
		      z[6]=ds[i][2]+(ds[i][6]-ds[i][4]);
		      z[7]=ds[i][7];
		    }
		  else
		    {
     
		      z[0]=ds[i][2];
		      z[1]=ds[i][3];
		      z[2]=ds[i][4];
		      z[3]=ds[i][5];
		      z[4]=ds[i][4]+(ds[i][2]-ds[i][8]);
		      z[5]=ds[i][9];
		      z[6]=ds[i][8];
		      z[7]=ds[i][9];

		    }


		}
	      flag1=0;
	    }
	  if(ds[i][15]==0)
	    {
	      int flag1=0;
	      if(ds[i][14]==90)
		{
		  flag1=1;
		  z[0]=ds[i][2];
		  z[1]=ds[i][3];
		  z[2]=ds[i][4];
		  z[3]=ds[i][5];
		  z[4]=ds[i][6];
		  z[5]=ds[i][7];
		  z[6]=ds[i][6];
		  z[7]=ds[i][3];
		  square[scn][0]=z[2];
		  square[scn][1]=z[3];
		  square[scn][2]=z[4];
		  square[scn][3]=z[5];
		  square[scn][4]=sqrt((z[3]-z[1])*(z[3]-z[1]));
		  square[scn][5]=1;


	

		}
	      if(ds[i][16]==90)
		{
		  flag1=1;
		  z[0]=ds[i][4];
		  z[1]=ds[i][9];
		  z[2]=ds[i][4];
		  z[3]=ds[i][5];
		  z[4]=ds[i][6];
		  z[5]=ds[i][7];
		  z[6]=ds[i][8];
		  z[7]=ds[i][9];
		  square[scn][0]=z[2];
		  square[scn][1]=z[3];
		  square[scn][2]=z[4];
		  square[scn][3]=z[5];
		  square[scn][4]=sqrt((z[3]-z[7])*(z[3]-z[7]));
		  square[scn][5]=1;


		 

	  
		}
	      if(flag1==0)
		{
		  if(ds[i][10]>=ds[i][12])
		    {
		      z[0]=ds[i][2];
		      z[1]=ds[i][3];
		      z[2]=ds[i][4];
		      z[3]=ds[i][5];
		      z[4]=ds[i][6];
		      z[5]=ds[i][7];
		      z[6]=ds[i][6]+(ds[i][2]-ds[i][4]);
		      z[7]=ds[i][3];
		    }
		  else
		    {
		      z[0]=ds[i][4]-(ds[i][6]-ds[i][8]);
		      z[1]=ds[i][9];
		      z[2]=ds[i][4];
		      z[3]=ds[i][5];
		      z[4]=ds[i][6];
		      z[5]=ds[i][7];
		      z[6]=ds[i][8];
		      z[7]=ds[i][9];
		    }

		}
	      flag1=0;

	    
	    }
	  if(ds[i][16]==0)
	    {
	      int flag1=0;
	      flag=1;
	      if(ds[i][15]==90)
		{
		  flag1=1;
		  z[0]=ds[i][8];
		  z[1]=ds[i][5];
		  z[2]=ds[i][4];
		  z[3]=ds[i][5];
		  z[4]=ds[i][6];
		  z[5]=ds[i][7];
		  z[6]=ds[i][8];
		  z[7]=ds[i][9];
		  square[scn][0]=z[4];
		  square[scn][1]=z[5];
		  square[scn][2]=z[6];
		  square[scn][3]=z[7];
		  square[scn][4]=sqrt((z[5]-z[3])*(z[5]-z[3]));
		  square[scn][5]=1;



	 
		}
	      if(ds[i][17]==90)
		{
		 
		  flag1=1;
		  z[0]=ds[i][2];
		  z[1]=ds[i][3];
		  z[2]=ds[i][6];
		  z[3]=ds[i][3];
		  z[4]=ds[i][6];
		  z[5]=ds[i][7];
		  z[6]=ds[i][8];
		  z[7]=ds[i][9];
		  square[scn][0]=z[4];
		  square[scn][1]=z[5];
		  square[scn][2]=z[6];
		  square[scn][3]=z[7];
		  square[scn][4]=sqrt((z[1]-z[5])*(z[1]-z[5]));
		  square[scn][5]=1;

	  
		}
	      if(flag1==0)
		{
		  if(ds[i][11]>=ds[i][13])
		    {
		      z[0]=ds[i][8]+(ds[i][4]-ds[i][7]);
		      z[1]=ds[i][5];
		      z[2]=ds[i][4];
		      z[3]=ds[i][5];
		      z[4]=ds[i][6];
		      z[5]=ds[i][7];
		      z[6]=ds[i][8];
		      z[7]=ds[i][9];
		    }
		  else
		    {
		      z[0]=ds[i][2];
		      z[1]=ds[i][3];
		      z[2]=ds[i][6]+(ds[i][2]-ds[i][8]);
		      z[3]=ds[i][3];
		      z[4]=ds[i][6];
		      z[5]=ds[i][7];
		      z[6]=ds[i][8];
		      z[7]=ds[i][9];
		    }
		}
	      flag1=0;

	    }
	  if(ds[i][17]==0)
	    {
	     
	      int flag1=0;
	      flag=1;
	      if(ds[i][14]==90)
		{
		  flag1=1;
		  z[0]=ds[i][2];
		  z[1]=ds[i][3];
		  z[2]=ds[i][4];
		  z[3]=ds[i][5];
		  z[4]=ds[i][8];
		  z[5]=ds[i][5];
		  z[6]=ds[i][8];
		  z[7]=ds[i][9]; 
		  square[scn][0]=z[0];
		  square[scn][1]=z[1];
		  square[scn][2]=z[6];
		  square[scn][3]=z[7];
		  square[scn][4]=sqrt((z[1]-z[3])*(z[1]-z[3]));
		  square[scn][5]=1;

      


		}
	      if(ds[i][16]==90)
		{
		  flag1=1;
		  z[0]=ds[i][2];
		  z[1]=ds[i][3];
		  z[2]=ds[i][2];
		  z[3]=ds[i][7];
		  z[4]=ds[i][6];
		  z[5]=ds[i][7];
		  z[6]=ds[i][8];
		  z[7]=ds[i][9];

		  square[scn][0]=z[0];
		  square[scn][1]=z[1];
		  square[scn][2]=z[6];
		  square[scn][3]=z[7];
		  square[scn][4]=sqrt((z[1]-z[5])*(z[1]-z[5]));
		  square[scn][5]=1;

	     
 

		}
	      if(flag1==0)
		{
		  if(ds[i][10]>=ds[i][12])
		    {
		      z[0]=ds[i][2];
		      z[1]=ds[i][3];
		      z[2]=ds[i][4];
		      z[3]=ds[i][5];
		      z[4]=ds[i][8]+(ds[i][4]-ds[i][2]);
		      z[5]=ds[i][5];
		      z[6]=ds[i][8];
		      z[7]=ds[i][9];
		    }
		  else
		    {
		      z[0]=ds[i][2];
		      z[1]=ds[i][3];
		      z[2]=ds[i][2]+(ds[i][6]-ds[i][8]);
		      z[3]=ds[i][7];
		      z[4]=ds[i][6];
		      z[5]=ds[i][7];
		      z[6]=ds[i][8];
		      z[7]=ds[i][9];
		    }
		}
	      flag1=0;

	    }
	  if(flag==0)
	    {

	    }
	  flag=0;
	  CvPoint p1,p2;
	  p1.x=z[0];
	  p1.y=z[1];
	  p2.x=z[2];
	  p2.y=z[3];
	  cvLine(out,p1,p2,CV_RGB(255,0,0),3,8);
	  p1.x=z[2];
	  p1.y=z[3];
	  p2.x=z[4];
	  p2.y=z[5];
	  cvLine(out,p1,p2,CV_RGB(255,0,0),3,8);
	  p1.x=z[4];
	  p1.y=z[5];
	  p2.x=z[6];
	  p2.y=z[7];
	  cvLine(out,p1,p2,CV_RGB(255,0,0),3,8);
	 
	  p1.x=z[0];
	  p1.y=z[1];
	  p2.x=z[6];
	  p2.y=z[7];
	  cvLine(out,p1,p2,CV_RGB(255,0,0),3,8);
	  if(square[scn][5]==1)
	    {
	      std::cout<<"\n";
	      for(int h=0;h<8;h++)
		{
		  std::cout<<square[scn][h]<<" ";
		}
	      square[scn][0]=z[0];
	      square[scn][1]=z[1];
	      for(int h=0;h<8;h=h+2)
		{
		  if(z[h]<square[scn][0])
		    {
		      square[scn][0]=z[h];
		    }
		  if(z[h]>square[scn][2])
		    {
		      square[scn][2]=z[h];
		    }
		}
	      for(int h=1;h<8;h=h+2)
		{
		  if(z[h]>square[scn][1])
		    {
		      square[scn][1]=z[h];
		    }
		}
	      scn++;
	    }
	  for(int j=0;j<18;j++)
	    {
	      std::cout<<ds[i][j]<<" ";
	    }
     

	}
    }
  for(int i=0;i<trin;i++)
    {
      std::cout<<"\n";
      for(int j=0;j<6;j++)
	{
	  std::cout<<tri[i][j]<<" ";
	}
    }
}





void dia()
{
  FILE *fp;
  FILE *fp2;
  char arr[4000],ch;
  int i=0;
  fp=fopen("com.txt","r");
  while(!feof(fp))
    {
      ch=fgetc(fp);
      arr[i]=ch;
      i++;
    }
  fclose(fp);
  fp2=fopen("ot.dia","w");
  fwrite(&arr,i-1,1,fp2);
  for(int k=0;k<trin;k++)
    {
      if(tri[k][0]==2)
	{
	  float t,m,p;
	  if(tri[k][1]<tri[k][3])
	    {
	      t=tri[k][1];
	      m=tri[k][2];
	      p=tri[k][3]-tri[k][1];
	    }
	  else
	    {
	      t=tri[k][3];
	      m=tri[k][4];
	      p=tri[k][1]-tri[k][3];
	    }
	  fp=fopen("tria2.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	  i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  fprintf(fp2,"%f,%f",(t/20),(m/20));
	  fp=fopen("tria3.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	      i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  fprintf(fp2,"%f",p/20);
	  fp=fopen("tria4.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	      i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  fprintf(fp2,"%f",(tri[k][5]/20));
	  fp=fopen("tria5.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	      i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  std::cout<<"\n"<<t<<" "<<m;
	}

      if(tri[k][0]==1)
	{
	  float t,m,p;
	  if(tri[k][1]<tri[k][3])
	    {
	      t=tri[k][1];
	      m=tri[k][2];
	      p=tri[k][3]-tri[k][1];
	    }
	  else
	    {
	      t=tri[k][3];
	      m=tri[k][4];
	      p=tri[k][1]-tri[k][3];
	    }
	  fp=fopen("tria2.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	  i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  fprintf(fp2,"%f,%f",(t/20),(m/20));
	  fp=fopen("tria3.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	      i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  fprintf(fp2,"%f",p/20);
	  fp=fopen("tria4.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	      i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  fprintf(fp2,"%f",(tri[k][5]/20));
	  fp=fopen("trias.txt","r");
	  i=0;
	  while(!feof(fp))
	    {
	      ch=fgetc(fp);
	      arr[i]=ch;
	      i++;
	    }
	  fclose(fp);
	  fwrite(&arr,i-1,1,fp2);
	  std::cout<<"\n"<<t<<" "<<m;

	}
    }
  for(int k=0;k<scn;k++)
    {
      if(square[k][5]==1)
	{
	  std::cout<<"hai";
	  float t,m,p;
	  t=square[k][0];
	  m=square[k][1];
	  p=square[k][2]-square[k][0];
	fp=fopen("rect1.txt","r");
	i=0;
	while(!feof(fp))
	  {
	    ch=fgetc(fp);
	    arr[i]=ch;
	    i++;
	  }
	fclose(fp);
	fwrite(&arr,i-1,1,fp2);
	fprintf(fp2,"%f,%f",(t/20),(m/20));
	fp=fopen("rect2.txt","r");
	i=0;
	while(!feof(fp))
	  {
	    ch=fgetc(fp);
	    arr[i]=ch;
	    i++;
	  }
	fclose(fp);
	fwrite(&arr,i-1,1,fp2);
	fprintf(fp2,"%f",p/20);
	fp=fopen("rect3.txt","r");
	i=0;
	while(!feof(fp))
	  {
	    ch=fgetc(fp);
	    arr[i]=ch;
	    i++;
	  }
	fclose(fp);
	fwrite(&arr,i-1,1,fp2);
	fprintf(fp2,"%f",(square[k][4]/20));
	fp=fopen("rect4.txt","r");
	i=0;
	while(!feof(fp))
	  {
	    ch=fgetc(fp);
	    arr[i]=ch;
	    i++;
	  }
	fclose(fp);
	fwrite(&arr,i-1,1,fp2);
	  std::cout<<"\n"<<t<<" "<<m;

      }
    }
  fp=fopen("end.txt","r");
  i=0;
  while(!feof(fp))
    {
      ch=fgetc(fp);
      arr[i]=ch;
      i++;
    }
  fclose(fp);
  fwrite(&arr,i-1,1,fp2);
}

