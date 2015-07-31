#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

//Variables globales
int casos;
vector <string> names;
vector <string> numbers;
int result[5][6];
int horizontal[6];
int vertical[5];
int products;
int k;
bool sol;

//Prototipos
void back (string num, int pos_actual, int espacios_puestos, int acum, string total, int fila, int columna);

//Main
int main(){
    int i, j=0;
    string line, sbstr, num, name;
    cin>>casos;
    for(i=0; i<casos; i++){
        names.clear();
        numbers.clear();
        sol=false;
        cin>>line;
        for (int k=0; k<6;k++)
            vertical[k]=0;
        for (int k=0; k<5;k++)
            horizontal[k]=0;
        k=0;
        while(line!="Totals"){
            sbstr = line.substr(0,2);
            line = line.substr(2);
            k++;
        }
        products=k;
        cin>>line;
        sbstr = line.substr(0,2);
        while(sbstr!="TP"){
            while(!isdigit(line[j])){
                name+=line[j];
                j++;
            }
            names.push_back(name);
            name.clear();
            num = line.substr(j);
            numbers.push_back(num);
            j=0;
            k++;
            cin>>line;
            sbstr = line.substr(0,2);
        }
        sbstr = line.substr(0,2);
        names.push_back(sbstr);
        sbstr = line.substr(2);
        numbers.push_back(sbstr);
        back (numbers[numbers.size()-1], numbers[numbers.size()-1].length()-1, 0, 0, "", numbers.size()-1, products);
    }
}

//Funciones
void back (string num, int pos_actual, int espacios_puestos, int acum, string total, int fila, int columna)
{
    string sub;
    if (columna==-1 && fila==0){
        sol=true;
        for (int b=1; b<=products; b++)
            cout<<"P"<<b<<" ";
        cout<<"Totals"<<endl;

        for (int m=0; m<numbers.size(); m++){
            cout<<names[m]<<" ";
            for (int n=0; n<=products; n++){
                cout<<result[m][n]<<" ";
            }
            cout<<endl;
        }


    }
    if (espacios_puestos-1==products && acum==atoi(total.c_str()) && !sol){//solucion
        back(numbers[fila-1], numbers[fila-1].length()-1, 0, 0, "", fila-1, products);


    }else{
        if (fila==numbers.size()-1 && !sol)//Para una fila igual a la ultima
        {
            if (total!="" && !sol){
                for (int i=pos_actual; i>=0 && total.length() >= sub.length() && sub.length()<5 && !sol; i--){
                    sub= num.substr(i, pos_actual-i+1);
                    if ((sub[0]!='0' || (sub[0]=='0' && sub.length()==1)) && acum+atoi(sub.c_str())<=atoi(total.c_str())&& !sol){
                        result[fila][columna]=atoi(sub.c_str());
                        back (num, i-1, espacios_puestos+1, acum+atoi(sub.c_str()), total, fila, columna-1);
                    }else{
                        if(acum+atoi(sub.c_str())>atoi(total.c_str())&& !sol)
                            break;
                    }
                }
            }else{
                for (int i=pos_actual; i>0 && sub.length()<5; i--){
                    sub=num.substr(i, pos_actual-i+1);
                    if (sub[0]!=0 && !sol){
                        result[fila][columna]=atoi(sub.c_str());
                        back (num, i-1, espacios_puestos+1, 0, sub, fila, columna-1);
                    }
                }
            }
        }else{
            if (fila==0){
                if (total!=""){ //Para la primera fila
                    for (int i=pos_actual; i>=0 && total.length() >= sub.length() && sub.length()<5 && !sol; i--){
                        sub= num.substr(i, pos_actual-i+1);
                        if ((sub[0]!='0' || (sub[0]=='0' && sub.length()==1)) && acum+atoi(sub.c_str())<=atoi(total.c_str()) && atoi(sub.c_str())+horizontal[columna]==result[numbers.size()-1][columna] && !sol){
                            result[fila][columna]=atoi(sub.c_str());
                            horizontal[columna]+=atoi(sub.c_str());
                            back (num, i-1, espacios_puestos+1, acum+atoi(sub.c_str()), total, fila, columna-1);
                            horizontal[columna]-=atoi(sub.c_str());
                        }else{
                            if(acum+atoi(sub.c_str())>atoi(total.c_str()) && !sol)
                                break;
                        }
                    }
                }else{
                    for (int i=pos_actual; i>0 && sub.length()<5; i--){
                        sub=num.substr(i, pos_actual-i+1);
                        if (sub[0]!=0 && (atoi(sub.c_str())+horizontal[columna])==result[numbers.size()-1][products] && !sol){
                            result[fila][columna]=atoi(sub.c_str());
                            horizontal[columna]+=atoi(sub.c_str());
                            back (num, i-1, espacios_puestos+1, 0, sub, fila, columna-1);
                            horizontal[columna]-=atoi(sub.c_str());
                        }
                    }
                }

            }else{
                if (total!=""){ //Para una fila distinta a la ultima
                    for (int i=pos_actual; i>=0 && total.length() >= sub.length() && sub.length()<5; i--){
                        sub= num.substr(i, pos_actual-i+1);
                        if ((sub[0]!='0' || (sub[0]=='0' && sub.length()==1)) && acum+atoi(sub.c_str())<=atoi(total.c_str()) && atoi(sub.c_str())+horizontal[columna]<=result[numbers.size()-1][products] && !sol){
                            result[fila][columna]=atoi(sub.c_str());
                            horizontal[columna]+=atoi(sub.c_str());
                            back (num, i-1, espacios_puestos+1, acum+atoi(sub.c_str()), total, fila, columna-1);
                            horizontal[columna]-=atoi(sub.c_str());
                        }else{
                            if(acum+atoi(sub.c_str())>atoi(total.c_str()) && !sol)
                                break;
                        }
                    }
                }else{
                    for (int i=pos_actual; i>0 && sub.length()<5 && !sol; i--){
                        sub=num.substr(i, pos_actual-i+1);
                        if (sub[0]!=0 && (atoi(sub.c_str())+horizontal[columna])<=result[numbers.size()-1][products] && !sol){
                            result[fila][columna]=atoi(sub.c_str());
                            horizontal[columna]+=atoi(sub.c_str());
                            back (num, i-1, espacios_puestos+1, 0, sub, fila, columna-1);
                            horizontal[columna]-=atoi(sub.c_str());
                        }
                    }
                }
            }
        }
    }
}
