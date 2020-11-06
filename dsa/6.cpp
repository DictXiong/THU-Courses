#include<cstdio>

const unsigned short LEN=30000;
unsigned short preOrder[LEN], inOrder[LEN], size=0;
//unsigned short *preOrder, *inOrder, size=0;

struct pair
{
    unsigned short first,second;
    pair(unsigned short f,unsigned short s): first(f),second(s){};
};

template<class T>void read(T &x)
{
    x=0;char ch=getchar();
    while(ch<'0'||ch>'9')  {ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    //x=f?-x:x;
    return;
}

void postOrder(pair indexPre, pair indexIn)
{
    unsigned short root=preOrder[indexPre.first], pos=indexIn.first, size=indexPre.second-indexPre.first+1;
    for (;inOrder[pos]!=root;pos++);
    unsigned short lcSize=pos-indexIn.first, rcSize=indexIn.second-pos;
    
    if (lcSize==1)
    {
        printf("%d ", inOrder[indexIn.first]);
    }
    else if (lcSize!=0)
    {
        postOrder(pair(indexPre.first+1,indexPre.first+lcSize),pair(indexIn.first,indexIn.first+lcSize-1));
    }

    if (rcSize==1)
    {
        printf("%d ", inOrder[indexIn.second]);
    }
    else if (rcSize!=0)
    {
        postOrder(pair(indexPre.second-rcSize+1,indexPre.second),pair(indexIn.second-rcSize+1,indexIn.second));
    }

    printf("%d ", preOrder[indexPre.first]);
}

int main()
{
    int N;
    read(N);
    for (int i=0;i!=N;i++)
    {
        read(size);
        //preOrder=new unsigned short[size];
        ////inOrder=new unsigned short[size];
        for (unsigned short i=0;i!=size;i++)
        {
            read(preOrder[i]);
        }
        for (unsigned short i=0;i!=size;i++)
        {
            read(inOrder[i]);
        }
        postOrder(pair(0,size-1),pair(0,size-1));
        printf("\n");
        //delete[] preOrder;
        //delete[] inOrder;
    }
    return 0;
}
