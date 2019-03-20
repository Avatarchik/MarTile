#include"../inc/readconfig.h"
#include"../inc/debug.h"

#define MAX 1000

double tmatrix[MAX][MAX]={0};

double vec[MAX]={0,0,1,0,0};
int second;
int tiles;
int cut[MAX]={0};
//return max value;
double matrixv(double aa[], double bb[MAX][MAX])
{
    double *res=(double *)malloc(tiles*sizeof(double));
    double max=0;
    for(int i=0;i<tiles-1;i++)
    {
        double x=0;
        for(int j=0;j<tiles-1;j++)
        {
            x+=aa[j]*bb[i][j];
        }
        res[i]=x;
        if(max<x){
            second=max;
            max=x;
        }
    }
    //cout<<max<<endl;
    return max;
}

//return max index;
int matrixi(double aa[], double **bb)
{
    double *res=(double *)malloc(tiles*sizeof(double));
    int max=0;
    for(int i=0;i<tiles-1;i++)
    {
        double x=0;
        for(int j=0;j<tiles-1;j++)
        {
            x+=aa[j]*bb[j][i];
        }
        res[i]=x;
        //vec[i]=res[i];
        if(res[max]<x)
        {
            second=max;
            max=i;
        }
    }
    for(int i=0;i<tiles-1;i++)
    {
        vec[i]=res[i];
    }
    
    return max;
}


void gmatrix2(char* s)
{
    int a[]={0,1,2,3,4};
    
    int ori[4000]={0};
    int b[4000]={0};
    double coun[8]={0};
   // ifstream in(s);
    int t;
    int i=0;
    FILE *fp;
    fp=fopen(s,"r");
    

    
    
    while(!feof(fp)){
        fscanf(fp,"%d",&t);
        ori[i]=t;
        b[i]=t;
        coun[b[i]]++;
        //cout<<b[i]<<endl;
        i++;
    }
    for(int j=0; j<tiles-1; j++){
        for(int m=0;m<tiles-1;m++)
        {
            int count=0;
            for(int n=1;n<i;n++)
            {
                if(b[n-1]==a[j]&&b[n]==a[m])
                count++;
            }
            tmatrix[j][m]= count/coun[j];
        }
    }
    fclose(fp);
}


//for generating the matrix inside;
void gmatrix(char* s,int g)
{
    int a[]={0,1,2,3,4};
    
    int ori[4000]={0};
    int b[4000]={0};
    double coun[8]={0};
   // ifstream in(s);
    int t;
    int i=0;
    int max=0;
    FILE *fp;
    fp=fopen(s,"r");
    
    while(!feof(fp)){
         fscanf(fp,"%d",&t);
        ori[i]=t;
        if (max<t)
        max=t;
        i++;
    }
    cut[g]=(max/100+1)*100;
    cut[g]=cut[g]/(tiles-1);
    for(int t=0;t<i;t++)
    {
        b[t]=ori[t]/cut[g];
        //        cout<<b[t]<<endl;
        coun[b[t]]++;
    }
    
    for(int j=0; j<tiles-1; j++){
        for(int m=0;m<tiles-1;m++)
        {
            int count=0;
            for(int n=1;n<i;n++)
            {
                if(b[n-1]==a[j]&&b[n]==a[m])
                count++;
            }
            tmatrix[j][m]= count/coun[j];
        }
    }
    fclose(fp);
}

double **f()
{
    //double **p = new double*[6];
    double **p= (double **)malloc(tiles*sizeof(double *));
    //  int n = 0;
    for (int i = 0; i < tiles; i++)
    {
       // p[i] = new double[6];
        p[i]=(double *)malloc(tiles*sizeof(double));
        for(int j = 0; j < tiles; j++)
        p[i][j] = tmatrix[i][j];
    }
    
    return p;
}

int  tenv(){
    int max=0;
    double totol=0;
    for(int i=0;i<tiles-1;i++)
    {
        vec[i]=rand()%10;
        if(vec[max]<vec[i])
        {
            max=i;
        }
        totol+=vec[i];
    }
    for(int i=0;i<tiles-1;i++)
    {
        vec[i]=vec[i]/totol;
    }
    return max;
}


int main(void)
{
    
    int clong =0;
    int cwide = 0;

    
    
    config_int_get( "./etc/martile.conf","setting", "long",&clong);
    
    config_int_get( "./etc/martile.conf","setting", "wide",&cwide);
    
    tiles=clong * cwide;
    srand(time(0));
    //printf("%d\n",tiles);
    double **mm[MAX];
   // ofstream out("/Users/herb/Documents/Gdownload/360camera/mare.txt",ios::trunc);
    gmatrix2("/Users/herb/Documents/markov/ppdd");
    double **mt=f();
    
    for(int i=0;i<1; i++){
    gmatrix("/Users/herb/Documents/markov/ppdd0",i);
    
    mm[i]=f();
    }
    gmatrix("/Users/herb/Documents/markov/ppdd1",1);
    mm[1]=f();
    gmatrix("/Users/herb/Documents/markov/ppdd2",2);
    mm[2]=f();
    gmatrix("/Users/herb/Documents/markov/ppdd3",3);
    mm[3]=f();
    gmatrix("/Users/herb/Documents/markov/ppdd4",4);
    mm[4]=f();
    for(int j=0; j<tiles-1; j++){
        for(int m=0;m<tiles-1;m++)
        {
           // cout<<tmatrix[j][m]<<" ";
            
            printf("%f ",tmatrix[j][m]);
        }
        printf("\n");
    }
    
    int tot=3000;
    int i=0;
    // double test[]={0.3,0.2,0.1,0.2,0.2};
    int previous=tiles+1;
    int res=tiles+1;
    while(i<=tot){
        //get location
        res=matrixi(vec, mt);
        do{
            res =  tenv();
        }while(res==previous);
        
        previous=res;
        
        
        //get time;
        //  cout<<"cut "<<cut[res]<<endl;
        
        int tt=matrixi(vec,mm[res]);
        double hhh=(rand()%100/(double)101);
        
        double hh = 1.0*tt*cut[res]+1.0*cut[res]*hhh;
        for(int j=0;j<hh;j++){
           // out<<res<<endl;
            if(i>tot) break;
            i++;
        }
        
    }
    return 0;
    
}
