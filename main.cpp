#include <bits/stdc++.h>
using namespace std;
const int MAXL = 100000;
const char* cf = "/config";
const char* tf = "template.tex";
const char* head = "head";
const char* tail = "tail";
int secn;
char sec[2000][MAXL];
FILE* tex = NULL;
char temp[MAXL],temp2[MAXL];
struct LineBreaker {
    char name[MAXL], file[MAXL], Texfile[MAXL], Subsubsec[MAXL];
    // the four array mean that:
    // 1: the name of the current Section.
    // 2: the cpp/java/etc file int the current Section.
    // 3: the tex file in the current Section.
    // 4: weather there exists a subsubsection.
    int nl, fl, tex1, subsub;
    void solve(const char s[]) {
        nl = fl = tex1 = subsub=0;
        int i = 0;
        while (s[i] && s[i] != '<') i ++;
        if (s[i]) i ++;
        while (s[i] && s[i] != '>') name[nl++] = s[i++];

        while (s[i] && s[i] != '<') i ++;
        if (s[i]) i ++;
        while (s[i] && s[i] != '>') file[fl++] = s[i++];

        while (s[i] && s[i] != '<') i ++;
        if (s[i]) i ++;
        while (s[i] && s[i] != '>') Texfile[tex1++] = s[i++];

        while (s[i] && s[i] != '<') i ++;
        if (s[i]) i++;
        while (s[i] && s[i] != '>') Subsubsec[subsub++] = s[i++];

        name[nl] = file[fl] = Texfile[tex1] = Subsubsec[subsub] = 0;
    }
};

// Find how many Sections the main tex have.
void read_dir() {
    FILE* dir = fopen(cf+1, "r");
    secn = 0;
    while (fgets(sec[secn++], MAXL, dir) != NULL) {}
    fclose(dir);
    while (sec[secn-1][0] == 0 && secn > 0) secn --;
    //update bug : original : (i<secn)
    for (int i = 0; i < secn-1; ++ i) {
        int Len_For_sec=strlen(sec[i]);
        if (sec[i][Len_For_sec-1] != 0) {
            sec[i][Len_For_sec-1] = 0;
        }
    }
}

// print the content int the file 'filename'.
void file(const char* filename) {
    FILE* fp = fopen(filename, "r");
    while (fgets(temp, MAXL, fp) != NULL) fprintf(tex, temp);
    memset(temp,0,sizeof(temp));
    fclose(fp);
}

// create the subsubsection
void Subsubsection(LineBreaker LB1,int curpos){
    puts("GG");
    memcpy(temp2,sec[curpos],sizeof(temp2));
    strcat(temp2,"/");
    strcat(temp2,LB1.name);
    strcat(temp2,cf);

    FILE* fp2 = fopen(temp2,"r");
    while(fgets(temp2,MAXL,fp2)!=NULL){
        if (temp2[0]!= '<') break;
        LineBreaker lb2;
        lb2.solve(temp2);
        printf("\\subsubsection %s with %s\n",lb2.name,LB1.file);
        fprintf(tex, "\\subsubsection{%s}\n",lb2.name);

        strcpy(temp2,sec[curpos]);
        temp2[strlen(temp2)+1]='\0';
        temp2[strlen(temp2)]='/';
        strcat(temp2,LB1.name);

        if(lb2.tex1>0){
            printf("\\begin{spacing}{1.5}\n\\input{%s/%s}\n\\end{spacing}\n",temp2,lb2.Texfile);
            fprintf(tex,"\\begin{spacing}{1.5}\n\\input{%s/%s}\n\\end{spacing}\n",temp2,lb2.Texfile);
        }
        if(lb2.fl==0) continue;
        fprintf(tex, "\\lstinputlisting{%s/%s}\n", temp2,lb2.file);
    }
    fclose(fp2);
}

int main() {
    tex = fopen(tf, "w");
    file(head);
    read_dir();
    for (int i = 0; i < secn; ++ i) {
        fprintf(tex, "\\section{%s}\n", sec[i]);
        memcpy(temp, sec[i], sizeof (temp) );
        strcat(temp, cf);
        printf("section: %s\n", sec[i]);
        FILE* fp = fopen(temp, "r");
        while(fgets(temp, MAXL, fp) != NULL) {

            // if the first letter in the line is not '<', then continue.
            if (temp[0] != '<') break;
            LineBreaker lb;
            lb.solve(temp);
            printf("subsection %s with %s\n", lb.name, lb.file);
            fprintf(tex, "\\subsection{%s}\n", lb.name);

            //check if there has a tex file
            if(lb.tex1>0){
                printf("\\begin{spacing}{1.5}\n\\input{%s/%s}\n\\end{spacing}\n",sec[i],lb.Texfile);
                fprintf(tex,"\\begin{spacing}{1.5}\n\\input{%s/%s}\n\\end{spacing}\n",sec[i],lb.Texfile);
            }

            // if the second <> is empty, then continue.
            if(lb.subsub>0){
               Subsubsection(lb,i);
            }

            //check if there has a cpp file
            if(lb.fl==0) continue;

            //gain the path for the cpp file
            memcpy(temp, sec[i], sizeof(temp) );
            temp[strlen(temp)+1] = 0;
            temp[strlen(temp)] = '/';

            strcat(temp, lb.file);
            fprintf(tex, "\\lstinputlisting{%s}\n", temp);
        }
        fclose(fp);
    }
    file(tail);
    fclose(tex);
    return 0;
}
