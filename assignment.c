#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int leaf_node()
{
    char file_name[20];
    sprintf(file_name, "%d.txt", getpid());
    FILE *fp = fopen(file_name, "w");
    srand(getpid());
    fprintf(fp, "%d", (rand() % 100));
    fclose(fp);
}

int parent(int pid1, int pid2)
{ // parent childlarının dosyasını açacak
    wait(NULL); //Waiting for child processes to finish

    char file_name1[20];
    sprintf(file_name1, "%d.txt", pid1);
    char file_name2[20];
    sprintf(file_name2, "%d.txt", pid2);
    char file_name3[20];
    sprintf(file_name3, "%d.txt", getpid());
    FILE *fp1, *fp2, *fp3;
    fp1 = fopen(file_name1, "r");
    fp2 = fopen(file_name2, "r");
    int left, right;
    fscanf(fp1, "%d", &left);
    fscanf(fp2, "%d", &right);
    fclose(fp1);
    fclose(fp2);
    fp3 = fopen(file_name3, "w");
    fprintf(fp3, "%d", left + right);
    fclose(fp3);
}

void createTree(int tree_height)
{
    if (tree_height == 0)
    {
        leaf_node();
        return;
    }

    int pid = fork();
    if (pid > 0)
    {
        int pid2 = fork();
        if (pid2 > 0)
        {
            // parent process
            wait(NULL);
            printf("parent:%d, c1:%d,c22:%d, tree_height:%d\n", getpid(), pid, pid2,tree_height);
            fflush(stdout);
            parent(pid, pid2);
        }
        else if (pid2 == 0)
        {
            // child1
            createTree(--tree_height);
        }
    }
    else if (pid == 0)
    {
        // child2
        createTree(--tree_height);
    }
}

int main(int argc,char *argv[])
{
    int treeHeight = atoi(argv[1]);
    createTree(treeHeight);
}