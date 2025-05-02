#include<iostream>
using namespace std;

class pizza_par{
    int v,adj[10][10];
    string city[10];

    public:
    void accept();
    void SSSP();
    void display();
}p;

void pizza_par::accept(){
    cout<<"\nEnter the number of locations of customers:";
    cin>>v;

    cout<<"\nEnter the name of city or locations:";
    for(int i=0;i<v;i++)
    {
        cin>>city[i];
    }

    cout<<"\nEnter the distance required:";
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            if(i==j)
            {
                adj[i][j]=0;
            }
            else{
                cout<<"\nEnter the distance from "<<city[i]<<" to "<<city[j]<<":";
                cin>>adj[i][j];
            }
        }
    }
}

void pizza_par::display()
{
    
    for(int i = 0 ; i < v ;i++)
    {
        cout<<"\t"<<city[i];
    }
    cout<<endl;
    for(int i=0; i<v ;i++)
    {
        cout<<city[i];
        for(int j =0 ;j <v;j++)
        {
            cout<<"\t"<<adj[i][j];
        }
        cout<<"\n";
    }
}

//single source shortest path algorithm
void pizza_par::SSSP()
{
    int min,u;
    int visited[10];
    int dist[10];
    
    //remaining vertex mark with maximum value
    for(int i=1;i<v;i++) 
    {
        dist[i]=999;   //assigning the max value(infinity)
        visited[i] = 0;   //not visited intially 
    }

    dist[0] = 0; //source vertex mark as zero
    visited[0]=0;

    for (int count = 0; count < v - 1; count++) {
         min = 999, u;

        // Find the minimum distance vertex not yet included
        for (int i = 0; i < v; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                u = i;
            }
        }
    visited[u]=1;
    
   
    for(int j=0;j<v;j++)
    {
        if(adj[u][j] && !visited[j]  && (dist[u]+ adj[u][j] < dist[j]))
        {
            dist[j]=dist[u]+ adj[u][j];
        }
    }
    
    cout<<"\nShortest distance:\n";
    }
    for(int i=1;i<v;i++)
    {
        cout<<"Distance from "<<city[0]<<" to "<<city[i]<<":"<<dist[i]<<endl;
    }

}
int main()
{
    int choice;
    do{
    cout<<"\n1.Accept\n2.Display\n3.Shortest distance from source location to all other locations\n";
    cout<<"\nEnter your choice:";
    cin>>choice;

    switch(choice)
    {
        case 1:
        p.accept();
        break;

        case 2:
        p.display();
        break;

        case 3:
        p.SSSP();
        break;

        default:
        cout<<"\nExiting the program....\n";
        break;
    }
}while(choice!=0);

return 0;
}
