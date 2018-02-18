#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#define MAX_POS 200000
#define Unigram 1
#define Bigram  2
#define Trigram 3

double logprob[MAX_POS];
double probability[MAX_POS];
int Verbose = 1;
int UNK = 0;

void print_usage(){
    fprintf(stderr, "Usage: pp model [-bi w_{i-1} | -tri w_{i-2} w_{i-1}] [-unk] < test-text.num\n");
    exit (2);
}

void read_lm(char *filename){
    FILE *in;
    char buf[100000];
    int i, j;
    int num;
    double sum;
    double prob;

    if((in = fopen(filename, "r")) == NULL){
        fprintf(stderr, "can't open the file: %s\n", filename);
        exit(2);
    }
    sum = 0.0;
    if(UNK == 0) num = 1;
    else num = 0;
    while(fgets(buf, sizeof(buf), in) != NULL){
        if(sscanf(buf, "%lf", &prob) == 1){
            if(prob < 1e-300){
                probability[num] = 0.0;
                logprob[num] = -100.0;
            } else {
                probability[num] = prob;
                logprob[num] = log(prob);
            }
            sum += probability[num];
            num++;
        }
    }
    if(Verbose == 1){
        printf("----- the model -----\n");
        fprintf(stderr, "Number of word types = %d\n", num);
        fprintf(stderr, "Sum(p) = %15.13e\n", sum);
    }
    if(-1.0e-12 > 1.0 - sum || 1.0e-12 < 1.0 - sum) {
        fprintf(stderr, "The sum is not 1.0\n");
        exit(2);
    }
}

void print_inf(){
    if(Verbose == 1) printf("PP = Inf\n");
    else printf("PP=Inf ");
}


void perp(int *sen, int wnum, int model, int pi_2, int pi_1, double *logsum, int *twnum){
    int i;
    double logsum_t = 0.0;
    int twnum_t = 0;
    for(i = 0; i < wnum; i++){
        if(UNK == 0 && sen[i]==0) continue;
        if(model == Unigram){
            if(logprob[sen[i]] == -100.0){
                print_inf();
                exit(0);
            } else {
                logsum_t += logprob[sen[i]];
                twnum_t++;
            }
        } else if(model == Bigram){
            if(i >= 1){
                if(pi_1 == sen[i-1]){
                    if(logprob[sen[i]] == -100.0){
                        print_inf();
                        exit(0);
                    } else {
                        logsum_t += logprob[sen[i]];
                        twnum_t++;
                    }
                }
            }
        } else {
            if(i >= 2){
                if(pi_1 == sen[i-1] && pi_2 == sen[i-2]){
                    if(logprob[sen[i]] == -100.0){
                        print_inf();
                        exit(0);
                    } else {
                        logsum_t += logprob[sen[i]];
                        twnum_t++;
                    }
                }
            }
        }
    }
    *logsum = logsum_t;
    *twnum = twnum_t;
}
   
int main(int ac, char **av){
    char buf[1000000];
    char num[100];
    int len, i;
    char *p;
    int nump;
    int sen[100000];
    int model = Unigram;
    int pi_1, pi_2;
    double sen_logsum, logsum = 0.0, perplexity;
    int wnum, totalwnum = 0, sen_wnum;
    if(ac < 2) print_usage();
    for(i = 2; i < ac; i++){
        if(!strcmp(av[i], "-bi")){
            model = Bigram;
            pi_1 = atoi(av[++i]);
	    } else if(!strcmp(av[i], "-tri")){
            model = Trigram;
            pi_2 = atoi(av[++i]);
            pi_1 = atoi(av[++i]);
        } else if(!strcmp(av[i], "-n")){
            Verbose = 0;
        } else if(!strcmp(av[i], "-unk")){
            UNK = 1;
        } else print_usage();
    }
    read_lm(av[1]);
    while(fgets(buf, sizeof(buf), stdin) != NULL){
        len = strlen(buf);
        if(buf[len-1]=='\n') buf[len-1] = '\0';
        p = buf;
        nump = 0;
        wnum = 0;
        for(p = buf; *p != '\0'; p++){
            if(*p != ' '){
                num[nump++] = *p;
            } else {
                num[nump] = '\0';
                nump = 0;
                sen[wnum++] = atoi(num);
            }
        }
        if(nump > 0){
            num[nump] = '\0';
            sen[wnum++] = atoi(num);
        }
        perp(sen, wnum, model, pi_2, pi_1, &sen_logsum, &sen_wnum);
	logsum += sen_logsum;
	totalwnum += sen_wnum;
    }
    perplexity = exp(-logsum/totalwnum);
    if(Verbose == 1) {
        printf("----- evaluation result -----\n");
        printf("#target_word = %d\n", totalwnum);
	printf("The sum of logprobs = %10.5f\n", logsum);
        printf("PP = %7.3f\n", perplexity);
    } else printf("%7.3f ", perplexity);
}
